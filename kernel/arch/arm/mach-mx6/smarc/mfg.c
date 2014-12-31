#include <asm/setup.h>
#include <mach/common.h>
#include <linux/memblock.h>
#include <linux/clk.h>
#include <linux/regulator/anatop-regulator.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/fixed.h>
#include <linux/power/gpio-charger.h>
#include "mfg.h"

void mx6q_smarc_init_uart(void)
{
	if (cpu_is_mx6q()) {
		mxc_iomux_v3_setup_multiple_pads(mx6q_smarc_uart_pads, ARRAY_SIZE(mx6q_smarc_uart_pads));
	} else {
		mxc_iomux_v3_setup_multiple_pads(mx6solo_smarc_uart_pads, ARRAY_SIZE(mx6solo_smarc_uart_pads));
	}

	imx6q_add_imx_uart(0, NULL);
	imx6q_add_imx_uart(1, NULL);
	imx6q_add_imx_uart(2, NULL);
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

void __init smarc_board_init(void)
{
	mx6q_smarc_init_uart();
	i2c_device_register_init();
}

void fixup_board(struct machine_desc *desc, struct tag *tags, char **cmdline, struct meminfo *mi)
{
}

void reserve(void)
{
}

