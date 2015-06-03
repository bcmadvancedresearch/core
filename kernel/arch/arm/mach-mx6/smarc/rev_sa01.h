#ifndef	REV_SA01_H
#define	REV_SA01_H
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/i2c/at24.h>
#include <linux/gpio.h>
#include <mach/iomux-mx6dl.h>
#include <mach/iomux-mx6q.h>
#include <linux/i2c/pca953x.h>
#include <linux/mfd/mxc-hdmi-core.h>
#include "../devices-imx6q.h"

/* -- GPIO Setting -- */
#define	SMARC_GPIO0			IMX_GPIO_NR(1, 16)

#define	SMARC_GPIO1			IMX_GPIO_NR(1, 17)
#define	SMARC_CODEC_PWR_EN		IMX_GPIO_NR(1, 17)

#ifdef  CONFIG_MACH_MX6_SMARC_P
#define	SMARC_GPIO2			IMX_GPIO_NR(2, 3)
#define	SMARC_GPIO3			IMX_GPIO_NR(2, 4)
#else
#define	SMARC_GPIO2			IMX_GPIO_NR(6, 2)
#define	SMARC_GPIO3			IMX_GPIO_NR(6, 3)
#endif

#define	SMARC_GPIO4			IMX_GPIO_NR(2, 0)

#define	SMARC_ACCL_INT_IN		IMX_GPIO_NR(1, 18)
#define	SMARC_GPIO5			IMX_GPIO_NR(1, 18)

#define	SMARC_CAN_STBY			IMX_GPIO_NR(6, 31)
#define	SMARC_GPIO6			IMX_GPIO_NR(6, 31)

#define	SMARC_CAN_EN			IMX_GPIO_NR(2, 1)
#define	SMARC_GPIO7			IMX_GPIO_NR(2, 1)

#define	SMARC_GPIO8			IMX_GPIO_NR(2, 2)
#define	SMARC_GPIO9			IMX_GPIO_NR(3, 16)

#define	SMARC_GPIO10			IMX_GPIO_NR(3, 28)
#define	SMARC_GPIO11			IMX_GPIO_NR(3, 29)

#define	SMARC_SD2_WP			IMX_GPIO_NR(3, 13)
#define	SMARC_SD2_CD			IMX_GPIO_NR(3, 14)
#define	SMARC_SD2_PWR_EN		IMX_GPIO_NR(1, 25)

static iomux_v3_cfg_t mx6q_smarc_gpio_pads[] = {
	MX6Q_PAD_SD1_DAT0__GPIO_1_16,		// GPIO 0
	MX6Q_PAD_SD1_DAT1__GPIO_1_17,		// GPIO 1
	#ifdef	CONFIG_MACH_MX6_SMARC_P
	MX6Q_PAD_NANDF_D3__GPIO_2_3,		// GPIO 2
	MX6Q_PAD_NANDF_D4__GPIO_2_4,		// GPIO 3
	#else
	MX6Q_PAD_CSI0_DAT16__GPIO_6_2,          // GPIO 2
	MX6Q_PAD_CSI0_DAT17__GPIO_6_3,		// GPIO 3
	#endif
	MX6Q_PAD_NANDF_D0__GPIO_2_0,		// GPIO 4
	MX6Q_PAD_SD1_CMD__GPIO_1_18,		// GPIO 5
	MX6Q_PAD_EIM_BCLK__GPIO_6_31,		// GPIO 6
	MX6Q_PAD_NANDF_D1__GPIO_2_1,		// GPIO 7
	MX6Q_PAD_NANDF_D2__GPIO_2_2,		// GPIO 8
	MX6Q_PAD_EIM_D16__GPIO_3_16,		// GPIO 9
	MX6Q_PAD_EIM_D28__GPIO_3_28,		// GPIO 10
	MX6Q_PAD_EIM_D29__GPIO_3_29,		// GPIO 11
};

static iomux_v3_cfg_t mx6q_smarc_sdio2_pads[] = {
	MX6Q_PAD_SD2_CLK__USDHC2_CLK,
	MX6Q_PAD_SD2_CMD__USDHC2_CMD,
	MX6Q_PAD_SD2_DAT0__USDHC2_DAT0,
	MX6Q_PAD_SD2_DAT1__USDHC2_DAT1,
	MX6Q_PAD_SD2_DAT2__USDHC2_DAT2,
	MX6Q_PAD_SD2_DAT3__USDHC2_DAT3,
	MX6Q_PAD_EIM_DA13__GPIO_3_13,
	MX6Q_PAD_EIM_DA14__GPIO_3_14,
	MX6Q_PAD_ENET_CRS_DV__GPIO_1_25,
};

static iomux_v3_cfg_t mx6dl_smarc_sdio2_pads[] = {
	MX6DL_PAD_SD2_CLK__USDHC2_CLK,
	MX6DL_PAD_SD2_CMD__USDHC2_CMD,
	MX6DL_PAD_SD2_DAT0__USDHC2_DAT0,
	MX6DL_PAD_SD2_DAT1__USDHC2_DAT1,
	MX6DL_PAD_SD2_DAT2__USDHC2_DAT2,
	MX6DL_PAD_SD2_DAT3__USDHC2_DAT3,
	MX6DL_PAD_EIM_DA13__GPIO_3_13,
	MX6DL_PAD_EIM_DA14__GPIO_3_14,
	MX6DL_PAD_ENET_CRS_DV__GPIO_1_25,
};

static const struct esdhc_platform_data mx6q_smarc_sdio2_data __initconst = {
	.cd_gpio = SMARC_SD2_CD,
	.wp_gpio = SMARC_SD2_WP,
	.keep_power_at_suspend = 1,
	.support_8bit = 1,
	.delay_line = 0,
	#ifdef  CONFIG_ION
	.runtime_pm = 1,
	#endif
	.cd_type = ESDHC_CD_CONTROLLER,
};

static const struct esdhc_platform_data mx6q_smarc_sdio3_data __initconst = {
	.keep_power_at_suspend = 1,
	.support_8bit = 1,
	.delay_line = 0,
	.cd_type = ESDHC_CD_CONTROLLER,
};


static iomux_v3_cfg_t mx6solo_smarc_gpio_pads[] = {
	MX6DL_PAD_SD1_DAT0__GPIO_1_16,		// GPIO 0
	MX6DL_PAD_SD1_DAT1__GPIO_1_17,		// GPIO 1
	#ifdef  CONFIG_MACH_MX6_SMARC_P
	MX6DL_PAD_NANDF_D3__GPIO_2_3,		// GPIO 2
	MX6DL_PAD_NANDF_D4__GPIO_2_4,		// GPIO 3
	#else
	MX6DL_PAD_CSI0_DAT16__GPIO_6_2,         // GPIO 2
	MX6DL_PAD_CSI0_DAT17__GPIO_6_3,		// GPIO 3
	#endif
	MX6DL_PAD_NANDF_D0__GPIO_2_0,		// GPIO 4
	MX6DL_PAD_SD1_CMD__GPIO_1_18,		// GPIO 5
	MX6DL_PAD_EIM_BCLK__GPIO_6_31,		// GPIO 6
	MX6DL_PAD_NANDF_D1__GPIO_2_1,		// GPIO 7
	MX6DL_PAD_NANDF_D2__GPIO_2_2,		// GPIO 8
	MX6DL_PAD_EIM_D16__GPIO_3_16,		// GPIO 9
	MX6DL_PAD_EIM_D28__GPIO_3_28,		// GPIO 10
	MX6DL_PAD_EIM_D29__GPIO_3_29,		// GPIO 11
};

/* -- I2C Config -- */
static struct wm8962_pdata wm8962_config_data;
static int mma8451_position;

static struct pca953x_platform_data my_pca953x_pdata = {
	.gpio_base = (unsigned)MX6Q_PAD_CSI0_DAT9__I2C1_SCL,
};

static struct i2c_board_info mxc_i2c0_board_info[] __initdata = {
	{
		I2C_BOARD_INFO("rx8010", 0x32),
	},
	{
		I2C_BOARD_INFO("mma8451", 0x1c),
		.irq  = gpio_to_irq(SMARC_ACCL_INT_IN),
		.platform_data = (void *)&mma8451_position,
	},
	{
		I2C_BOARD_INFO("wm8962", 0x1a),
		.platform_data = &wm8962_config_data
	},
	{
		I2C_BOARD_INFO("tca9555", 0x20),
		.irq = -1,
		.platform_data = (void *)&my_pca953x_pdata,
	},
};

static struct i2c_board_info mxc_i2c1_board_info[] __initdata = {
	{
		I2C_BOARD_INFO("mxc_hdmi_i2c", 0x50),
	},
};

static struct i2c_board_info mxc_i2c2_board_info[] __initdata = {
};

static iomux_v3_cfg_t mx6q_smarc_uart_pads[] = {
    /* -- UART 1 -- */
    MX6Q_PAD_CSI0_DAT10__UART1_TXD,
    MX6Q_PAD_CSI0_DAT11__UART1_RXD,
    MX6Q_PAD_EIM_D20__UART1_RTS,
    MX6Q_PAD_EIM_D19__UART1_CTS,

    /* -- UART 2 -- */
    MX6Q_PAD_EIM_D26__UART2_TXD,
    MX6Q_PAD_EIM_D27__UART2_RXD,

    /* -- UART 3 -- */
    MX6Q_PAD_EIM_D24__UART3_TXD,
    MX6Q_PAD_EIM_D25__UART3_RXD,
    MX6Q_PAD_EIM_D31__UART3_RTS,
    MX6Q_PAD_EIM_D23__UART3_CTS,

    /* -- UART4 -- */
    MX6Q_PAD_CSI0_DAT12__UART4_TXD,
    MX6Q_PAD_CSI0_DAT13__UART4_RXD,
};

static iomux_v3_cfg_t mx6solo_smarc_uart_pads[] = {
	/* -- UART 1 -- */
	MX6DL_PAD_CSI0_DAT10__UART1_TXD,
	MX6DL_PAD_CSI0_DAT11__UART1_RXD,
	MX6DL_PAD_EIM_D20__UART1_RTS,
	MX6DL_PAD_EIM_D19__UART1_CTS,

	/* -- UART 2 -- */
	MX6DL_PAD_EIM_D26__UART2_TXD,
	MX6DL_PAD_EIM_D27__UART2_RXD,

	/* -- UART 3 -- */
	MX6DL_PAD_EIM_D24__UART3_TXD,
	MX6DL_PAD_EIM_D25__UART3_RXD,
	MX6DL_PAD_EIM_D31__UART3_RTS,
	MX6DL_PAD_EIM_D23__UART3_CTS,

	/* -- UART4 -- */
	MX6DL_PAD_CSI0_DAT12__UART4_TXD,
	MX6DL_PAD_CSI0_DAT13__UART4_RXD,
};

static iomux_v3_cfg_t mx6q_smarc_other_pads[] = {
	MX6Q_PAD_SD1_CMD__GPIO_1_18,
	MX6Q_PAD_SD1_CLK__GPIO_1_20,
	MX6Q_PAD_SD1_DAT2__GPIO_1_19,
};

static iomux_v3_cfg_t mx6solo_smarc_other_pads[] = {
    MX6DL_PAD_SD1_CMD__GPIO_1_18,
    MX6DL_PAD_SD1_CLK__GPIO_1_20,
    MX6DL_PAD_SD1_DAT2__GPIO_1_19,
};

static iomux_v3_cfg_t mx6q_smarc_hdmi_ddc_pads[] = {
    MX6Q_PAD_KEY_COL3__HDMI_TX_DDC_SCL, /* HDMI DDC SCL */
    MX6Q_PAD_KEY_ROW3__HDMI_TX_DDC_SDA, /* HDMI DDC SDA */
};

static iomux_v3_cfg_t mx6solo_smarc_hdmi_ddc_pads[] = {
    MX6DL_PAD_KEY_COL3__HDMI_TX_DDC_SCL, /* HDMI DDC SCL */
    MX6DL_PAD_KEY_ROW3__HDMI_TX_DDC_SDA, /* HDMI DDC SDA */
};


static iomux_v3_cfg_t mx6q_smarc_i2c2_pads[] = {
    MX6Q_PAD_KEY_COL3__I2C2_SCL,    /* I2C2 SCL */
    MX6Q_PAD_KEY_ROW3__I2C2_SDA,    /* I2C2 SDA */
};

static iomux_v3_cfg_t mx6solo_smarc_i2c2_pads[] = {
    MX6DL_PAD_KEY_COL3__I2C2_SCL,    /* I2C2 SCL */
    MX6DL_PAD_KEY_ROW3__I2C2_SDA,    /* I2C2 SDA */
};

#ifdef	CONFIG_SMARC_DISPLAY_LVDS
/* -- Panel -- */
#define SMARC_LVDS_BKLT_EN  IMX_GPIO_NR(3, 0)
#define SMARC_LCD_VDD_EN    IMX_GPIO_NR(2, 22)
static iomux_v3_cfg_t mx6q_smarc_lvds_ctr_pads[] = {
	MX6Q_PAD_SD1_DAT3__PWM1_PWMO,
	MX6Q_PAD_EIM_DA0__GPIO_3_0,
	MX6Q_PAD_EIM_A16__GPIO_2_22,
};

static iomux_v3_cfg_t mx6solo_smarc_lvds_ctr_pads[] = {
	MX6DL_PAD_SD1_DAT3__PWM1_PWMO,
	MX6DL_PAD_EIM_DA0__GPIO_3_0,
	MX6DL_PAD_EIM_A16__GPIO_2_22,
};
#endif

static iomux_v3_cfg_t mx6q_smarc_can_pad[] = {
	MX6Q_PAD_GPIO_7__CAN1_TXCAN,
	MX6Q_PAD_GPIO_8__CAN1_RXCAN,
	MX6Q_PAD_KEY_ROW4__CAN2_RXCAN,
	MX6Q_PAD_KEY_COL4__CAN2_TXCAN,
};

static iomux_v3_cfg_t mx6solo_smarc_can_pad[] = {
	MX6DL_PAD_GPIO_7__CAN1_TXCAN,
	MX6DL_PAD_GPIO_8__CAN1_RXCAN,
	MX6DL_PAD_KEY_ROW4__CAN2_RXCAN,
	MX6DL_PAD_KEY_COL4__CAN2_TXCAN,
};

#ifdef	CONFIG_SMARC_DISPLAY_VGA
static iomux_v3_cfg_t mx6q_smarc_ttl_pad[] = {
	MX6Q_PAD_DI0_DISP_CLK__IPU1_DI0_DISP_CLK,
	MX6Q_PAD_DI0_PIN2__IPU1_DI0_PIN2,
	MX6Q_PAD_DI0_PIN3__IPU1_DI0_PIN3,
	MX6Q_PAD_DI0_PIN15__IPU1_DI0_PIN15,
	MX6Q_PAD_DISP0_DAT0__IPU1_DISP0_DAT_0,
	MX6Q_PAD_DISP0_DAT1__IPU1_DISP0_DAT_1,
	MX6Q_PAD_DISP0_DAT2__IPU1_DISP0_DAT_2,
	MX6Q_PAD_DISP0_DAT3__IPU1_DISP0_DAT_3,
	MX6Q_PAD_DISP0_DAT4__IPU1_DISP0_DAT_4,
	MX6Q_PAD_DISP0_DAT5__IPU1_DISP0_DAT_5,
	MX6Q_PAD_DISP0_DAT6__IPU1_DISP0_DAT_6,
	MX6Q_PAD_DISP0_DAT7__IPU1_DISP0_DAT_7,
	MX6Q_PAD_DISP0_DAT8__IPU1_DISP0_DAT_8,
	MX6Q_PAD_DISP0_DAT9__IPU1_DISP0_DAT_9,
	MX6Q_PAD_DISP0_DAT10__IPU1_DISP0_DAT_10,
	MX6Q_PAD_DISP0_DAT11__IPU1_DISP0_DAT_11,
	MX6Q_PAD_DISP0_DAT12__IPU1_DISP0_DAT_12,
	MX6Q_PAD_DISP0_DAT13__IPU1_DISP0_DAT_13,
	MX6Q_PAD_DISP0_DAT14__IPU1_DISP0_DAT_14,
	MX6Q_PAD_DISP0_DAT15__IPU1_DISP0_DAT_15,
	MX6Q_PAD_DISP0_DAT16__IPU1_DISP0_DAT_16,
	MX6Q_PAD_DISP0_DAT17__IPU1_DISP0_DAT_17,
	MX6Q_PAD_DISP0_DAT18__IPU1_DISP0_DAT_18,
	MX6Q_PAD_DISP0_DAT19__IPU1_DISP0_DAT_19,
	MX6Q_PAD_DISP0_DAT20__IPU1_DISP0_DAT_20,
	MX6Q_PAD_DISP0_DAT21__IPU1_DISP0_DAT_21,
	MX6Q_PAD_DISP0_DAT22__IPU1_DISP0_DAT_22,
	MX6Q_PAD_DISP0_DAT23__IPU1_DISP0_DAT_23,
};

static iomux_v3_cfg_t mx6solo_smarc_ttl_pad[] = {
	MX6DL_PAD_DI0_DISP_CLK__IPU1_DI0_DISP_CLK,
	MX6DL_PAD_DI0_PIN2__IPU1_DI0_PIN2,
	MX6DL_PAD_DI0_PIN3__IPU1_DI0_PIN3,
	MX6DL_PAD_DI0_PIN15__IPU1_DI0_PIN15,
	MX6DL_PAD_DISP0_DAT0__IPU1_DISP0_DAT_0,
	MX6DL_PAD_DISP0_DAT1__IPU1_DISP0_DAT_1,
	MX6DL_PAD_DISP0_DAT2__IPU1_DISP0_DAT_2,
	MX6DL_PAD_DISP0_DAT3__IPU1_DISP0_DAT_3,
	MX6DL_PAD_DISP0_DAT4__IPU1_DISP0_DAT_4,
	MX6DL_PAD_DISP0_DAT5__IPU1_DISP0_DAT_5,
	MX6DL_PAD_DISP0_DAT6__IPU1_DISP0_DAT_6,
	MX6DL_PAD_DISP0_DAT7__IPU1_DISP0_DAT_7,
	MX6DL_PAD_DISP0_DAT8__IPU1_DISP0_DAT_8,
	MX6DL_PAD_DISP0_DAT9__IPU1_DISP0_DAT_9,
	MX6DL_PAD_DISP0_DAT10__IPU1_DISP0_DAT_10,
	MX6DL_PAD_DISP0_DAT11__IPU1_DISP0_DAT_11,
	MX6DL_PAD_DISP0_DAT12__IPU1_DISP0_DAT_12,
	MX6DL_PAD_DISP0_DAT13__IPU1_DISP0_DAT_13,
	MX6DL_PAD_DISP0_DAT14__IPU1_DISP0_DAT_14,
	MX6DL_PAD_DISP0_DAT15__IPU1_DISP0_DAT_15,
	MX6DL_PAD_DISP0_DAT16__IPU1_DISP0_DAT_16,
	MX6DL_PAD_DISP0_DAT17__IPU1_DISP0_DAT_17,
	MX6DL_PAD_DISP0_DAT18__IPU1_DISP0_DAT_18,
	MX6DL_PAD_DISP0_DAT19__IPU1_DISP0_DAT_19,
	MX6DL_PAD_DISP0_DAT20__IPU1_DISP0_DAT_20,
	MX6DL_PAD_DISP0_DAT21__IPU1_DISP0_DAT_21,
	MX6DL_PAD_DISP0_DAT22__IPU1_DISP0_DAT_22,
	MX6DL_PAD_DISP0_DAT23__IPU1_DISP0_DAT_23,
};
#endif

#endif
