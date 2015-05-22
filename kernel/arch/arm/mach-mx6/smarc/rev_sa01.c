#include <asm/setup.h>
#include <mach/common.h>
#include <linux/memblock.h>
#include <linux/clk.h>
#include <linux/regulator/anatop-regulator.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/fixed.h>
#include <linux/mfd/wm8994/pdata.h>
#include <linux/mfd/wm8994/gpio.h>
#include <sound/wm8962.h>
#include <linux/power/gpio-charger.h>
#include "rev_sa01.h"

static struct clk *clko;

static const struct imxuart_platform_data mx6_uart0_data __initconst = {
	.flags = IMXUART_HAVE_RTSCTS | IMXUART_SDMA,
	.dma_req_rx = MX6Q_DMA_REQ_UART1_RX,
	.dma_req_tx = MX6Q_DMA_REQ_UART1_TX,
};

static const struct imxuart_platform_data mx6_uart3_data __initconst = {
	.flags = IMXUART_HAVE_RTSCTS | IMXUART_SDMA,
	.dma_req_rx = MX6Q_DMA_REQ_UART3_RX,
	.dma_req_tx = MX6Q_DMA_REQ_UART3_TX,
};

void mx6q_smarc_init_uart(void)
{
	if (cpu_is_mx6q()) {
		mxc_iomux_v3_setup_multiple_pads(mx6q_smarc_uart_pads, ARRAY_SIZE(mx6q_smarc_uart_pads));
	} else {
		mxc_iomux_v3_setup_multiple_pads(mx6solo_smarc_uart_pads, ARRAY_SIZE(mx6solo_smarc_uart_pads));
	}

	imx6q_add_imx_uart(0, NULL);
	imx6q_add_imx_uart(1, NULL);
	imx6q_add_imx_uart(2, &mx6_uart3_data);
	imx6q_add_imx_uart(3, NULL);
}

extern void __iomem *twd_base;
void set_console_timer(void)
{
	struct clk *uart_clk;

	#ifdef CONFIG_LOCAL_TIMERS
	twd_base = ioremap(LOCAL_TWD_ADDR, SZ_256);
	BUG_ON(!twd_base);
	#endif
	mx6_clocks_init(32768, 24000000, 0, 0);

	uart_clk = clk_get_sys("imx-uart.0", NULL);
	early_console_setup(UART1_BASE_ADDR, uart_clk);
}

void i2c_device_register_init(void )
{
	i2c_register_board_info(0, mxc_i2c0_board_info, ARRAY_SIZE(mxc_i2c0_board_info));
	i2c_register_board_info(1, mxc_i2c1_board_info, ARRAY_SIZE(mxc_i2c1_board_info));
	i2c_register_board_info(2, mxc_i2c2_board_info, ARRAY_SIZE(mxc_i2c2_board_info));
}

void set_smarc_gpio(void)
{
	if (cpu_is_mx6q()) {
		mxc_iomux_v3_setup_multiple_pads(mx6q_smarc_gpio_pads, ARRAY_SIZE(mx6q_smarc_gpio_pads));
	} else {
		mxc_iomux_v3_setup_multiple_pads(mx6solo_smarc_gpio_pads, ARRAY_SIZE(mx6solo_smarc_gpio_pads));
	}

	gpio_request(SMARC_GPIO0, "smarc-gpio0");
	gpio_direction_output(SMARC_GPIO0, 1);
	gpio_set_value(SMARC_GPIO0, 0);
	gpio_export(SMARC_GPIO0, 1);

	/* --> Codec power enable
	gpio_request(SMARC_GPIO1, "smarc-gpio1");
	gpio_direction_output(SMARC_GPIO1, 1);
	gpio_set_value(SMARC_GPIO1, 0);
	gpio_export(SMARC_GPIO1, 1);
	*/

	gpio_request(SMARC_GPIO2, "smarc-gpio2");
	gpio_direction_output(SMARC_GPIO2, 1);
	gpio_set_value(SMARC_GPIO2, 0);
	gpio_export(SMARC_GPIO2, 1);


	gpio_request(SMARC_GPIO3, "smarc-gpio3");
	gpio_direction_output(SMARC_GPIO3, 1);
	gpio_set_value(SMARC_GPIO3, 0);
	gpio_export(SMARC_GPIO3, 1);

	gpio_request(SMARC_GPIO4, "smarc-gpio4");
	gpio_direction_output(SMARC_GPIO4, 1);
	gpio_set_value(SMARC_GPIO4, 0);
	gpio_export(SMARC_GPIO4, 1);

	/* --> ACCL int input
	gpio_request(SMARC_GPIO5, "smarc-gpio5");
	gpio_direction_output(SMARC_GPIO5, 1);
	gpio_set_value(SMARC_GPIO5, 0);
	gpio_export(SMARC_GPIO5, 1);
	*/

	/* CAN STBY */
	gpio_request(SMARC_GPIO6, "smarc-can-stby");
	gpio_direction_output(SMARC_CAN_STBY, 1);
	gpio_set_value(SMARC_CAN_STBY, 0);
	gpio_export(SMARC_GPIO6, 1);

	gpio_request(SMARC_CAN_EN, "smarc-gpio7");
	gpio_direction_output(SMARC_CAN_EN, 1);
	gpio_set_value(SMARC_CAN_EN, 1);
	gpio_export(SMARC_CAN_EN, 1);

	gpio_request(SMARC_GPIO8, "smarc-gpio8");
	gpio_direction_output(SMARC_GPIO8, 1);
	gpio_set_value(SMARC_GPIO8, 0);
	gpio_export(SMARC_GPIO8, 1);

	/* --> MIC detect pin
	gpio_request(SMARC_GPIO9, "smarc-gpio9");
	gpio_direction_output(SMARC_GPIO9, 1);
	gpio_set_value(SMARC_GPIO9, 0);
	gpio_export(SMARC_GPIO9, 1);
	*/

	gpio_request(SMARC_GPIO10, "smarc-gpio10");
	gpio_direction_output(SMARC_GPIO10, 1);
	gpio_set_value(SMARC_GPIO10, 0);
	gpio_export(SMARC_GPIO10, 1);

	gpio_request(SMARC_GPIO11, "smarc-gpio11");
	gpio_direction_output(SMARC_GPIO11, 1);
	gpio_set_value(SMARC_GPIO11, 0);
	gpio_export(SMARC_GPIO11, 1);
}

void hdmi_init(int ipu_id, int disp_id)
{
    int hdmi_mux_setting;

    if ((ipu_id > 1) || (ipu_id < 0)) {
        pr_err("Invalid IPU select for HDMI: %d. Set to 0\n", ipu_id);
        ipu_id = 0;
    }

    if ((disp_id > 1) || (disp_id < 0)) {
        pr_err("Invalid DI select for HDMI: %d. Set to 0\n", disp_id);
        disp_id = 0;
    }

    /* Configure the connection between IPU1/2 and HDMI */
    hdmi_mux_setting = 2*ipu_id + disp_id;

    /* GPR3, bits 2-3 = HDMI_MUX_CTL */
    mxc_iomux_set_gpr_register(3, 2, 2, hdmi_mux_setting);

    /* Set HDMI event as SDMA event2 while Chip version later than TO1.2 */
    if (hdmi_SDMA_check())
        mxc_iomux_set_gpr_register(0, 0, 1, 1);
}

void hdmi_enable_ddc_pin(void)
{
	if (cpu_is_mx6q()) {
		mxc_iomux_v3_setup_multiple_pads(mx6q_smarc_hdmi_ddc_pads, ARRAY_SIZE(mx6q_smarc_hdmi_ddc_pads));
	} else {
		mxc_iomux_v3_setup_multiple_pads(mx6solo_smarc_hdmi_ddc_pads, ARRAY_SIZE(mx6solo_smarc_hdmi_ddc_pads));
	}
}

void hdmi_disable_ddc_pin(void)
{
	if (cpu_is_mx6q()) {
		mxc_iomux_v3_setup_multiple_pads(mx6q_smarc_i2c2_pads, ARRAY_SIZE(mx6q_smarc_i2c2_pads));
	} else {
		mxc_iomux_v3_setup_multiple_pads(mx6solo_smarc_i2c2_pads, ARRAY_SIZE(mx6solo_smarc_i2c2_pads));
	}
}

static struct fsl_mxc_hdmi_platform_data hdmi_data = {
    .init = hdmi_init,
    .enable_pins = hdmi_enable_ddc_pin,
    .disable_pins = hdmi_disable_ddc_pin,
};

static struct fsl_mxc_hdmi_core_platform_data hdmi_core_data = {
    .ipu_id = 0,
    .disp_id = 1,
};


void set_smarc_hdmi(void)
{
	imx6q_add_mxc_hdmi_core(&hdmi_core_data);
	imx6q_add_mxc_hdmi(&hdmi_data);
	imx6q_add_hdmi_soc();
	imx6q_add_hdmi_soc_dai();
}

void set_smarc_lvds(void)
{
	if(cpu_is_mx6q()) {
		mxc_iomux_v3_setup_multiple_pads(mx6q_smarc_lvds_ctr_pads, ARRAY_SIZE(mx6q_smarc_lvds_ctr_pads));
	} else {
		mxc_iomux_v3_setup_multiple_pads(mx6solo_smarc_lvds_ctr_pads, ARRAY_SIZE(mx6solo_smarc_lvds_ctr_pads));
	}

	gpio_request(SMARC_LVDS_BKLT_EN, "lvds-bklt-en");
	gpio_direction_output(SMARC_LVDS_BKLT_EN, 1);
	gpio_set_value(SMARC_LVDS_BKLT_EN, 1);

	gpio_request(SMARC_LCD_VDD_EN, "lcd-vdd-en");
	gpio_direction_output(SMARC_LCD_VDD_EN, 1);
	gpio_set_value(SMARC_LCD_VDD_EN, 1);
}

static struct ipuv3_fb_platform_data smarc_fb_data[] = {
	{
	.disp_dev = "hdmi",
	.interface_pix_fmt = IPU_PIX_FMT_RGB24,
	.mode_str = "1920x1080M@60",
	.default_bpp = 32,
	.int_clk = false,
	.late_init = false,
	},
	/*
	{
	.disp_dev = "lcd",
	.interface_pix_fmt = IPU_PIX_FMT_RGB24,
	.mode_str = "LCD_WVGA",
	.default_bpp = 32,
	.int_clk = true,
	},
	*/
	/*
	{
	.disp_dev = "ldb",
	.interface_pix_fmt = IPU_PIX_FMT_RGB666,
	.mode_str = "SVGA",
	.default_bpp = 32,
	.int_clk = false,
	.late_init = false,
	},
	*/
	/*
	{
	.disp_dev = "lcd",
	.interface_pix_fmt = IPU_PIX_FMT_BGR24,
	.mode_str = "LCD_XGA",
	.default_bpp = 16,
	.int_clk = false,
	},
	*/
	/*
	{
	.disp_dev = "hdmi",
	.interface_pix_fmt = IPU_PIX_FMT_RGB24,
	.mode_str = "1920x1080M@60",
	.default_bpp = 32,
	.int_clk = false,
	.late_init = false,
	},
	*/
};

static struct fsl_mxc_lcd_platform_data lcdif_data = {
	.ipu_id = 0,
	.disp_id = 0,
	.default_ifmt = IPU_PIX_FMT_BGR24,
};

static struct viv_gpu_platform_data imx6q_gpu_pdata __initdata = {
	.reserved_mem_size = SZ_128M + SZ_64M - SZ_16M,
};

static struct fsl_mxc_ldb_platform_data ldb_data = {
	.ipu_id			= 0,
	.disp_id		= 1,
	.ext_ref		= 1,
	.mode			= LDB_SEP0,
	.sec_ipu_id		= 0,
	.sec_disp_id	= 0,
};

static struct imx_ipuv3_platform_data ipu_data[] = {
{
	.rev = 4,
	.csi_clk[0] = "clko_clk",
	.bypass_reset = false,
	}, {
	.rev = 4,
	.csi_clk[0] = "clko_clk",
	.bypass_reset = false,
	},
};

void smarc_fb_init(void)
{
	int i = 0;

	imx6q_add_ipuv3(0, &ipu_data[0]);

	if (cpu_is_mx6q()) {
		imx6q_add_ipuv3(1, &ipu_data[1]);
		for (i = 0; i < 4 && i < ARRAY_SIZE(smarc_fb_data); i++) {
			imx6q_add_ipuv3fb(i, &smarc_fb_data[i]);
		}
	} else {
		for (i = 0; i < 2 && i < ARRAY_SIZE(smarc_fb_data); i++) {
			imx6q_add_ipuv3fb(i, &smarc_fb_data[i]);
		}
	}
}

void set_smarc_sdio(void)
{
	if (cpu_is_mx6q()) {
		mxc_iomux_v3_setup_multiple_pads(mx6q_smarc_sdio2_pads, ARRAY_SIZE(mx6q_smarc_sdio2_pads));
	} else {
		mxc_iomux_v3_setup_multiple_pads(mx6dl_smarc_sdio2_pads, ARRAY_SIZE(mx6dl_smarc_sdio2_pads));
	}

	gpio_request(SMARC_SD2_PWR_EN, "smarc-sd2-pwr");
	gpio_direction_output(SMARC_SD2_PWR_EN, 1);
	gpio_set_value(SMARC_SD2_PWR_EN, 1);
	gpio_export(SMARC_SD2_PWR_EN, 1);

	imx6q_add_sdhci_usdhc_imx(1, &mx6q_smarc_sdio2_data);
}

/* ---- WM8962 ---- */
static struct imx_ssi_platform_data imx6_smarc_ssi_pdata = {
	.flags = IMX_SSI_DMA | IMX_SSI_SYN,
};

static struct platform_device imx6_smarc_audio_wm8962_device = {
	.name = "imx-wm8962",
};

static struct mxc_audio_platform_data wm8962_data;

static int wm8962_clk_enable(int enable)
{
	if (enable)
		clk_enable(clko);
	else
		clk_disable(clko);
	return 0;
}

static int mxc_wm8962_init(void)
{
	int rate;

	clko = clk_get(NULL, "clko_clk");
	if (IS_ERR(clko)) {
		pr_err("can't get CLKO clock.\n");
		return PTR_ERR(clko);
	}

	/* both audio codec and comera use CLKO clk*/
	rate = clk_round_rate(clko, 24000000);
	clk_set_rate(clko, rate);

	wm8962_data.sysclk = rate;
	return 0;
}

static struct mxc_audio_platform_data wm8962_data = {
	.ssi_num = 1,
	.src_port = 2,
	.ext_port = 3,
	.hp_gpio = -1,
	.hp_active_low = 0,
	.mic_gpio = SMARC_GPIO9,
	.mic_active_low = 1,
	.init = mxc_wm8962_init,
	.clock_enable = wm8962_clk_enable,
};

static struct wm8962_pdata wm8962_config_data = {
	.gpio_init = {
		[2] = WM8962_GPIO_FN_DMICCLK,
		[4] = 0x8000 | WM8962_GPIO_FN_DMICDAT,
	},
};

static struct regulator_consumer_supply smarc_vwm8962_consumers[] = {
	#ifdef	MACH_MX6_SMARC
	REGULATOR_SUPPLY("DCVDD", "0-001a"),
	REGULATOR_SUPPLY("DBVDD", "0-001a"),
	REGULATOR_SUPPLY("AVDD", "0-001a"),
	REGULATOR_SUPPLY("CPVDD", "0-001a"),
	REGULATOR_SUPPLY("MICVDD", "0-001a"),
	REGULATOR_SUPPLY("PLLVDD", "0-001a"),
	#endif
	REGULATOR_SUPPLY("SPKVDD1", "0-001a"),
	REGULATOR_SUPPLY("SPKVDD2", "0-001a"),
};

static struct regulator_init_data smarc_vwm8962_init = {
	.constraints = {
		.name = "SPKVDD",
		.valid_ops_mask =  REGULATOR_CHANGE_STATUS,
		.boot_on = 1,
	},
	.num_consumer_supplies = ARRAY_SIZE(smarc_vwm8962_consumers),
	.consumer_supplies = smarc_vwm8962_consumers,
};

static struct fixed_voltage_config smarc_vwm8962_reg_config = {
	.supply_name    = "SPKVDD",
	.microvolts     = 4200000,
	.gpio           = SMARC_CODEC_PWR_EN,
	.enable_high    = 1,
	.enabled_at_boot = 1,
	.init_data      = &smarc_vwm8962_init,
};

static struct platform_device smarc_vwm8962_reg_devices = {
	.name   = "reg-fixed-voltage",
	.id     = 4,
	.dev    = {
		.platform_data = &smarc_vwm8962_reg_config,
	},
};

static int __init mx6q_init_audio(void)
{
	platform_device_register(&smarc_vwm8962_reg_devices);
	mxc_register_device(&imx6_smarc_audio_wm8962_device, &wm8962_data);
	imx6q_add_imx_ssi(1, &imx6_smarc_ssi_pdata);
	return 0;
}
/* --------------------------- */

/* ---- CAN Bus ---- */
static void mx6_smarc_flexcan0_switch(int enable)
{
	if (enable) {
		 gpio_set_value(SMARC_CAN_STBY, 1);
	} else {
		gpio_set_value(SMARC_CAN_STBY, 0);
	}
}

static void mx6_smarc_flexcan1_switch(int enable)
{
	if (enable) {
		gpio_set_value(SMARC_CAN_STBY, 1);
	} else {
		gpio_set_value(SMARC_CAN_STBY, 0);
	}
}

static const struct flexcan_platform_data mx6_smarc_flexcan0_pdata __initconst = {
	.transceiver_switch = mx6_smarc_flexcan0_switch,
};

static const struct flexcan_platform_data mx6_smarc_flexcan1_pdata __initconst = {
	.transceiver_switch = mx6_smarc_flexcan1_switch,
};

void smarc_can_init(void)
{
	if (cpu_is_mx6q()) {
		mxc_iomux_v3_setup_multiple_pads(mx6q_smarc_can_pad, ARRAY_SIZE(mx6q_smarc_can_pad));
	} else {
		mxc_iomux_v3_setup_multiple_pads(mx6solo_smarc_can_pad, ARRAY_SIZE(mx6solo_smarc_can_pad));
	}

	imx6q_add_flexcan0(&mx6_smarc_flexcan0_pdata);
	imx6q_add_flexcan1(&mx6_smarc_flexcan1_pdata);
}

void __init smarc_board_init(void)
{
	mx6q_init_audio();
	smarc_fb_init();
	set_smarc_lvds();
	imx6q_add_lcdif(&lcdif_data);
	//imx6q_add_ldb(&ldb_data);
	set_smarc_hdmi();
	imx6q_add_vpu();
	imx_add_viv_gpu(&imx6_gpu_data, &imx6q_gpu_pdata);
	imx6q_add_v4l2_output(0);

	set_smarc_gpio();
	mx6q_smarc_init_uart();
	set_smarc_sdio();
	smarc_can_init();

	/* -- I2C register -- */
	i2c_device_register_init();

	if (cpu_is_mx6q()) {
		mxc_iomux_v3_setup_multiple_pads(mx6q_smarc_other_pads, ARRAY_SIZE(mx6q_smarc_other_pads));
	} else {
		mxc_iomux_v3_setup_multiple_pads(mx6solo_smarc_other_pads, ARRAY_SIZE(mx6solo_smarc_other_pads));
	}
}

void fixup_board(struct machine_desc *desc, struct tag *tags, char **cmdline, struct meminfo *mi)
{
}

void reserve(void)
{
}

