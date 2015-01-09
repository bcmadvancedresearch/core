/*
 * Copyright (C) 2012-2013 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/types.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/nodemask.h>
#include <linux/clk.h>
#include <linux/platform_device.h>
#include <linux/fsl_devices.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>
#include <linux/i2c.h>
#include <linux/i2c/pca953x.h>
#include <linux/ata.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/map.h>
#include <linux/mtd/partitions.h>
#include <linux/regulator/consumer.h>
#include <linux/pmic_external.h>
#include <linux/pmic_status.h>
#include <linux/ipu.h>
#include <linux/mxcfb.h>
#include <linux/pwm_backlight.h>
#include <linux/fec.h>
#include <linux/memblock.h>
#include <linux/gpio.h>
#include <linux/etherdevice.h>
#include <linux/power/sabresd_battery.h>
#include <linux/regulator/anatop-regulator.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/fixed.h>
#include <linux/mfd/max17135.h>
#include <linux/mfd/wm8994/pdata.h>
#include <linux/mfd/wm8994/gpio.h>
#include <sound/wm8962.h>
#include <linux/mfd/mxc-hdmi-core.h>

#include <mach/common.h>
#include <mach/hardware.h>
#include <mach/mxc_dvfs.h>
#include <mach/memory.h>
#include <mach/iomux-mx6q.h>
#include <mach/imx-uart.h>
#include <mach/viv_gpu.h>
#include <mach/ahci_sata.h>
#include <mach/ipu-v3.h>
#include <mach/mxc_hdmi.h>
#include <mach/mxc_asrc.h>
#include <mach/mipi_dsi.h>
#include <asm/irq.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>

#include "usb.h"
#include "devices-imx6q.h"
#include "crm_regs.h"
#include "cpu_op-mx6.h"
#include <mach/imx_rfkill.h>
#include "board-mx6_smarc.h"

#ifdef CONFIG_MX6_ENET_IRQ_TO_GPIO
#define MX6_ENET_IRQ		IMX_GPIO_NR(1, 6)
#define IOMUX_OBSRV_MUX1_OFFSET	0x3c
#define OBSRV_MUX1_MASK			0x3f
#define OBSRV_MUX1_ENET_IRQ		0x9
#endif

/* -- USB OC Pin -- */
#define SMARC_USB_OTG_OC  IMX_GPIO_NR(3, 21)
#define SMARC_USB_HOST1_OC  IMX_GPIO_NR(3, 30)

static int caam_enabled;
static struct clk *sata_clk;
extern char *gp_reg_id;
extern char *soc_reg_id;
extern char *pu_reg_id;
extern int epdc_enabled;

void smarc_board_init(void);
void reserve(void);
void set_console_timer(void);
void fixup_board(struct machine_desc *, struct tag *, char **, struct meminfo *);

static const struct esdhc_platform_data mx6q_smarc_sd4_data __initconst = {
	.always_present = 1,
	.keep_power_at_suspend = 1,
	.support_8bit = 1,
	.delay_line = 0,
	.cd_type = ESDHC_CD_PERMANENT,
};

static int smarc_fec_phy_init(struct phy_device *phydev)
{
	unsigned short val;

	/*check phy power*/
	val = phy_read(phydev, 0x0);

	if (val & BMCR_PDOWN)
		phy_write(phydev, 0x0, (val & ~BMCR_PDOWN));

	return 0;
}

static struct fec_platform_data fec_data __initdata = {
	.init = smarc_fec_phy_init,
	.phy = PHY_INTERFACE_MODE_RGMII,
#ifdef CONFIG_MX6_ENET_IRQ_TO_GPIO
	.gpio_irq = MX6_ENET_IRQ,
#endif
};

static struct imxi2c_platform_data mx6q_smarc_i2c_data = {
	.bitrate = 100000,
};

static const struct anatop_thermal_platform_data mx6_smarc_anatop_thermal_data __initconst = {
	.name = "anatop_thermal",
};

static void smarc_suspend_enter(void)
{
}

static void smarc_suspend_exit(void)
{
}

static const struct pm_platform_data imx6_smarc_pm_data __initconst = {
	.name = "imx_pm",
	.suspend_enter = smarc_suspend_enter,
	.suspend_exit = smarc_suspend_exit,
};

static void imx6q_sabresd_usbotg_vbus(bool on)
{
	if (on)
		gpio_set_value(SMARC_USB_OTG_PWR, 1);
	else
		gpio_set_value(SMARC_USB_OTG_PWR, 0);
}

static void imx6q_sabresd_host1_vbus(bool on)
{
	msleep(0);
}

static void __init imx6q_smarc_init_usb(void)
{
	int ret = 0;

	imx_otg_base = MX6_IO_ADDRESS(MX6Q_USB_OTG_BASE_ADDR);
	/* disable external charger detect,
	 * or it will affect signal quality at dp .
	 */
	ret = gpio_request(SMARC_USB_OTG_OC, "usb-oc");
	if (ret) {
		pr_err("failed to get GPIO SABRESD_USB_OTG_OC: %d\n", ret);
		return;
	}
	gpio_direction_input(SMARC_USB_OTG_OC);

	ret = gpio_request(SMARC_USB_HOST1_OC, "usb1-oc");
	if (ret) {
		pr_err("failed to get GPIO SABRESD_USB_HOST1_OC: %d\n", ret);
		return;
	}
	gpio_direction_input(SMARC_USB_HOST1_OC);

	mxc_iomux_set_gpr_register(1, 13, 1, 0);

	mx6_set_otghost_vbus_func(imx6q_sabresd_usbotg_vbus);
	mx6_set_host1_vbus_func(imx6q_sabresd_host1_vbus);
}

/* -- PCIE -- */
static const struct imx_pcie_platform_data mx6_smarc_pcie_data __initconst = {
	.pcie_rst				= SMARC_PCIE_RESET,
	.pcie_wake_up			= SMARC_PCIE_WAKE,
	#ifdef  CONFIG_ION
	.pcie_power_always_on	= 1,
	#endif
};

static struct imx_asrc_platform_data imx_asrc_data = {
	.channel_bits = 4,
	.clk_map_ver = 2,
};

static struct platform_pwm_backlight_data mx6_sabresd_pwm_backlight_data = {
	.pwm_id = 0,
	.max_brightness = 248,
	.dft_brightness = 128,
	.pwm_period_ns = 50000,
};

static struct regulator_consumer_supply smarc_vmmc_consumers[] = {
	REGULATOR_SUPPLY("vmmc", "sdhci-esdhc-imx.1"),
	REGULATOR_SUPPLY("vmmc", "sdhci-esdhc-imx.2"),
	REGULATOR_SUPPLY("vmmc", "sdhci-esdhc-imx.3"),
};

static struct regulator_init_data smarc_vmmc_init = {
	.num_consumer_supplies = ARRAY_SIZE(smarc_vmmc_consumers),
	.consumer_supplies = smarc_vmmc_consumers,
};

static struct fixed_voltage_config smarc_vmmc_reg_config = {
	.supply_name		= "vmmc",
	.microvolts		= 3300000,
	.gpio			= -1,
	.init_data		= &smarc_vmmc_init,
};

static struct platform_device smarc_vmmc_reg_devices = {
	.name	= "reg-fixed-voltage",
	.id	= 3,
	.dev	= {
		.platform_data = &smarc_vmmc_reg_config,
	},
};



static struct mxc_dvfs_platform_data smarc_dvfscore_data = {
	.reg_id = "VDDCORE",
	.soc_id	= "VDDSOC",
	.clk1_id = "cpu_clk",
	.clk2_id = "gpc_dvfs_clk",
	.gpc_cntr_offset = MXC_GPC_CNTR_OFFSET,
	.ccm_cdcr_offset = MXC_CCM_CDCR_OFFSET,
	.ccm_cacrr_offset = MXC_CCM_CACRR_OFFSET,
	.ccm_cdhipr_offset = MXC_CCM_CDHIPR_OFFSET,
	.prediv_mask = 0x1F800,
	.prediv_offset = 11,
	.prediv_val = 3,
	.div3ck_mask = 0xE0000000,
	.div3ck_offset = 29,
	.div3ck_val = 2,
	.emac_val = 0x08,
	.upthr_val = 25,
	.dnthr_val = 9,
	.pncthr_val = 33,
	.upcnt_val = 10,
	.dncnt_val = 10,
	.delay_time = 80,
};

/* HW Initialization, if return 0, initialization is successful. */
static int mx6q_smarc_sata_init(struct device *dev, void __iomem *addr)
{
	u32 tmpdata;
	int ret = 0;
	struct clk *clk;

	sata_clk = clk_get(dev, "imx_sata_clk");
	if (IS_ERR(sata_clk)) {
		dev_err(dev, "no sata clock.\n");
		return PTR_ERR(sata_clk);
	}

	ret = clk_enable(sata_clk);
	if (ret) {
		dev_err(dev, "can't enable sata clock.\n");
		goto put_sata_clk;
	}

	/* Set PHY Paremeters, two steps to configure the GPR13,
	 * one write for rest of parameters, mask of first write is 0x07FFFFFD,
	 * and the other one write for setting the mpll_clk_off_b
	 *.rx_eq_val_0(iomuxc_gpr13[26:24]),
	 *.los_lvl(iomuxc_gpr13[23:19]),
	 *.rx_dpll_mode_0(iomuxc_gpr13[18:16]),
	 *.sata_speed(iomuxc_gpr13[15]),
	 *.mpll_ss_en(iomuxc_gpr13[14]),
	 *.tx_atten_0(iomuxc_gpr13[13:11]),
	 *.tx_boost_0(iomuxc_gpr13[10:7]),
	 *.tx_lvl(iomuxc_gpr13[6:2]),
	 *.mpll_ck_off(iomuxc_gpr13[1]),
	 *.tx_edgerate_0(iomuxc_gpr13[0]),
	 */
	tmpdata = readl(IOMUXC_GPR13);
	writel(((tmpdata & ~0x07FFFFFD) | 0x0593A044), IOMUXC_GPR13);

	/* enable SATA_PHY PLL */
	tmpdata = readl(IOMUXC_GPR13);
	writel(((tmpdata & ~0x2) | 0x2), IOMUXC_GPR13);

	/* Get the AHB clock rate, and configure the TIMER1MS reg later */
	clk = clk_get(NULL, "ahb");
	if (IS_ERR(clk)) {
		dev_err(dev, "no ahb clock.\n");
		ret = PTR_ERR(clk);
		goto release_sata_clk;
	}
	tmpdata = clk_get_rate(clk) / 1000;
	clk_put(clk);

	#ifdef CONFIG_SATA_AHCI_PLATFORM
	ret = sata_init(addr, tmpdata);
	if (ret == 0) {
		return ret;
	}
	#else
	usleep_range(1000, 2000);
	/* AHCI PHY enter into PDDQ mode if the AHCI module is not enabled */
	tmpdata = readl(addr + PORT_PHY_CTL);
	writel(tmpdata | PORT_PHY_CTL_PDDQ_LOC, addr + PORT_PHY_CTL);
	pr_info("No AHCI save PWR: PDDQ %s\n", ((readl(addr + PORT_PHY_CTL)
				>> 20) & 1) ? "enabled" : "disabled");
	#endif

release_sata_clk:
	/* disable SATA_PHY PLL */
	writel((readl(IOMUXC_GPR13) & ~0x2), IOMUXC_GPR13);
	clk_disable(sata_clk);
put_sata_clk:
	clk_put(sata_clk);

	return ret;
}

#ifdef CONFIG_SATA_AHCI_PLATFORM
static void mx6q_smarc_sata_exit(struct device *dev)
{
	clk_disable(sata_clk);
	clk_put(sata_clk);
}

static struct ahci_platform_data mx6q_sabresd_sata_data = {
	.init = mx6q_smarc_sata_init,
	.exit = mx6q_smarc_sata_exit,
};
#endif

static int __init caam_setup(char *__unused)
{
	caam_enabled = 1;
	return 1;
}
early_param("caam", caam_setup);

#ifdef CONFIG_ANDROID_RAM_CONSOLE
static struct resource ram_console_resource = {
	.name = "android ram console",
	.flags = IORESOURCE_MEM,
};

static struct platform_device android_ram_console = {
	.name = "ram_console",
	.num_resources = 1,
	.resource = &ram_console_resource,
};

static int __init imx6x_add_ram_console(void)
{
	return platform_device_register(&android_ram_console);
}
#else
#define imx6x_add_ram_console() do {} while (0)
#endif

#define SNVS_LPCR 0x38
static void mx6_snvs_poweroff(void)
{
	void __iomem *mx6_snvs_base =  MX6_IO_ADDRESS(MX6Q_SNVS_BASE_ADDR);
	u32 value;
	value = readl(mx6_snvs_base + SNVS_LPCR);
	/*set TOP and DP_EN bit*/
	writel(value | 0x60, mx6_snvs_base + SNVS_LPCR);
}

/*!
 * Board specific initialization.
 */
static void __init mx6_smarc_board_init(void)
{
	int rate = 0;
	struct clk *clko2 = NULL;
	struct clk *new_parent = NULL;

	if (cpu_is_mx6q()) {
		mxc_iomux_v3_setup_multiple_pads(mx6q_smarc_basic_pads, ARRAY_SIZE(mx6q_smarc_basic_pads));
	} else {
		mxc_iomux_v3_setup_multiple_pads(mx6solo_smarc_basic_pads, ARRAY_SIZE(mx6solo_smarc_basic_pads));
	}

	#ifdef CONFIG_ANDROID_RAM_CONSOLE
	imx6x_add_ram_console();
	#endif

	imx6q_add_vdoa();

	imx6q_add_mxc_pwm(0);
	#ifndef CONFIG_SMARC_REV_SA01
	imx6q_add_mxc_pwm(1);
	imx6q_add_mxc_pwm(2);
	imx6q_add_mxc_pwm(3);
	#endif
	imx6q_add_mxc_pwm_backlight(0, &mx6_sabresd_pwm_backlight_data);

	/* -- Initize I2C bus -- */
	imx6q_add_imx_i2c(0, &mx6q_smarc_i2c_data);
	imx6q_add_imx_i2c(1, &mx6q_smarc_i2c_data);
	imx6q_add_imx_i2c(2, &mx6q_smarc_i2c_data);

	imx6_init_fec(fec_data);
	#ifdef CONFIG_MX6_ENET_IRQ_TO_GPIO
	/* Make sure the IOMUX_OBSRV_MUX1 is set to ENET_IRQ. */
	mxc_iomux_set_specialbits_register(IOMUX_OBSRV_MUX1_OFFSET, OBSRV_MUX1_ENET_IRQ, OBSRV_MUX1_MASK);
	#endif

	/* -- Initize eMMC -- */
	imx6q_add_sdhci_usdhc_imx(3, &mx6q_smarc_sd4_data);
	//platform_device_register(&smarc_vmmc_reg_devices);

	imx6q_smarc_init_usb();

	/* SATA is not supported by MX6DL/Solo */
	if (cpu_is_mx6q()) {
		#ifdef CONFIG_SATA_AHCI_PLATFORM
		imx6q_add_ahci(0, &mx6q_sabresd_sata_data);
		#else
		mx6q_smarc_sata_init(NULL, (void __iomem *)ioremap(MX6Q_SATA_BASE_ADDR, SZ_4K));
		#endif
	}

	imx_asrc_data.asrc_core_clk = clk_get(NULL, "asrc_clk");
	imx_asrc_data.asrc_audio_clk = clk_get(NULL, "asrc_serial_clk");
	imx6q_add_asrc(&imx_asrc_data);
	
	imx6q_add_otp();
	imx6q_add_viim();
	imx6q_add_imx2_wdt(0, NULL);
	imx6q_add_dma();
	imx6q_add_pcie(&mx6_smarc_pcie_data);

	gp_reg_id = smarc_dvfscore_data.reg_id;
	soc_reg_id = smarc_dvfscore_data.soc_id;
	imx6q_add_dvfs_core(&smarc_dvfscore_data);
	pm_power_off = mx6_snvs_poweroff;
	#ifndef CONFIG_SMARC_REV_SA01
	imx6q_add_imx_snvs_rtc();

	clko2 = clk_get(NULL, "clko2_clk");
	if (IS_ERR(clko2)) {
		pr_err("can't get CLKO2 clock.\n");
	}

	new_parent = clk_get(NULL, "osc_clk");
	if (!IS_ERR(new_parent)) {
		clk_set_parent(clko2, new_parent);
		clk_put(new_parent);
	}
	rate = clk_round_rate(clko2, 24000000);
	clk_set_rate(clko2, rate);
	clk_enable(clko2);
	#endif

	imx6q_add_busfreq();
	imx6q_add_anatop_thermal_imx(1, &mx6_smarc_anatop_thermal_data);
	imx6q_add_pm_imx(0, &imx6_smarc_pm_data);
	smarc_board_init();

	imx6_add_armpmu();
	imx6q_add_perfmon(0);
	imx6q_add_perfmon(1);
	imx6q_add_perfmon(2);
	platform_device_register(&smarc_vmmc_reg_devices);
}

static void __init mx6_smarc_timer_init(void)
{
	set_console_timer();
}

static struct sys_timer mx6_smarc_timer = {
	.init   = mx6_smarc_timer_init,
};

static void __init fixup_mxc_board(struct machine_desc *param1, struct tag *param2, char **param3, struct meminfo *param4)
{
	fixup_board(param1, param2, param3, param4);
}

void __init mx6q_smarc_reserve(void)
{
	reserve();
}

/*
 * initialize __mach_desc_MX6Q_SMARC data structure.
 */
MACHINE_START(MX6_SMARC, "i.MX 6Quad/DualLite/Solo SMARC CPU Board")
	/* Maintainer: Freescale Semiconductor, Inc. */
	.boot_params = MX6_PHYS_OFFSET + 0x100,
	.fixup = fixup_mxc_board,
	.map_io = mx6_map_io,
	.init_irq = mx6_init_irq,
	.init_machine = mx6_smarc_board_init,
	.timer = &mx6_smarc_timer,
	.reserve = mx6q_smarc_reserve,
MACHINE_END
