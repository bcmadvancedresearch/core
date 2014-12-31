#ifndef	REV_SA01_H
#define	REV_SA01_H
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/i2c/at24.h>
#include <linux/gpio.h>
#include <mach/iomux-mx6dl.h>
#include <mach/iomux-mx6q.h>
#include <linux/mfd/mxc-hdmi-core.h>
#include "../devices-imx6q.h"

static struct i2c_board_info mxc_i2c0_board_info[] __initdata = {
};

static struct i2c_board_info mxc_i2c1_board_info[] __initdata = {
};

static struct i2c_board_info mxc_i2c2_board_info[] __initdata = {
};

static iomux_v3_cfg_t mx6q_smarc_uart_pads[] = {
	/* -- UART 1 -- */
	MX6Q_PAD_CSI0_DAT10__UART1_TXD,
	MX6Q_PAD_CSI0_DAT11__UART1_RXD,

	/* -- UART 2 -- */
	MX6Q_PAD_EIM_D26__UART2_TXD,
	MX6Q_PAD_EIM_D27__UART2_RXD,

	/* -- UART 3 -- */
	MX6Q_PAD_EIM_D24__UART3_TXD,
	MX6Q_PAD_EIM_D25__UART3_RXD,

	/* -- UART4 -- */
	MX6Q_PAD_CSI0_DAT12__UART4_TXD,
	MX6Q_PAD_CSI0_DAT13__UART4_RXD,
};

static iomux_v3_cfg_t mx6solo_smarc_uart_pads[] = {
	/* -- UART 1 -- */
	MX6DL_PAD_CSI0_DAT10__UART1_TXD,
	MX6DL_PAD_CSI0_DAT11__UART1_RXD,

	/* -- UART 2 -- */
	MX6DL_PAD_EIM_D26__UART2_TXD,
	MX6DL_PAD_EIM_D27__UART2_RXD,

	/* -- UART 3 -- */
	MX6DL_PAD_EIM_D24__UART3_TXD,
	MX6DL_PAD_EIM_D25__UART3_RXD,

	/* -- UART4 -- */
	MX6DL_PAD_CSI0_DAT12__UART4_TXD,
	MX6DL_PAD_CSI0_DAT13__UART4_RXD,
};

#endif
