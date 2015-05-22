/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the MX6Q Sabre Lite2 Freescale board.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/arch/mx6.h>

 /* High Level Configuration Options */
#define CONFIG_ARMV7	/* This is armv7 Cortex-A9 CPU core */
#define CONFIG_MXC
#define CONFIG_FLASH_HEADER
#define CONFIG_FLASH_HEADER_OFFSET 0x400
#define CONFIG_MX6_CLK32	   32768

#define CONFIG_SKIP_RELOCATE_UBOOT

#define CONFIG_ARCH_CPU_INIT
#undef CONFIG_ARCH_MMU /* disable MMU first */
#define CONFIG_L2_OFF  /* disable L2 cache first*/

#define CONFIG_MX6_HCLK_FREQ	24000000

#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#define CONFIG_SYS_64BIT_VSPRINTF

#define BOARD_LATE_INIT

#define CONFIG_CMDLINE_TAG	/* enable passing of ATAGs */
#define CONFIG_SERIAL_TAG
#define CONFIG_REVISION_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_MXC_GPIO
#define	CONFIG_SPLASH_SCREEN

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(2 * 1024 * 1024)
/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_SIZE	128

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX		1
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{9600, 19200, 38400, 57600, 115200}

/***********************************************************
 * Command definition
 ***********************************************************/

#include <config_cmd_default.h>

#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_CMD_NET
#define CONFIG_NET_RETRY_COUNT  100
#define CONFIG_NET_MULTI 1
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_DNS

//#define CONFIG_CMD_SPI
#define CONFIG_CMD_I2C
#define CONFIG_CMD_IMXOTP

/* Enable below configure when supporting nand */
//#define CONFIG_CMD_SF
#define CONFIG_CMD_MMC
#define CONFIG_CMD_ENV
#define CONFIG_CMD_REGUL

#define CONFIG_CMD_CLOCK
#define CONFIG_REF_CLK_FREQ CONFIG_MX6_HCLK_FREQ

/* #define CONFIG_CMD_SATA */
#undef CONFIG_CMD_IMLS

#define CONFIG_CMD_IMX_DOWNLOAD_MODE

#define CONFIG_BOOTDELAY 3

#define CONFIG_PRIME	"FEC0"

#define CONFIG_LOADADDR		0x10800000	/* loadaddr env var */
#define CONFIG_RD_LOADADDR	(0x1100000)

#define	CONFIG_EXTRA_ENV_SETTINGS									\
		"netdev=eth0\0"												\
		"ethprime=FEC0\0"											\
		"ethaddr=00:04:9f:00:ea:d3\0"								\
		"fec_addr=00:04:9f:00:ea:d3\0"								\
		"uboot=u-boot.bin\0"										\
		"kernel=uImage\0"											\
		"nfsroot=/opt/eldk/arm\0"									\
		"network=ip=dhcp\0"											\
		"bootargs_base=setenv bootargs console=ttymxc0,115200\0"	\
		"bootargs_nfs=setenv bootargs ${bootargs} root=/dev/nfs "	\
			"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0"		\
		"bootcmd_net=run bootargs_base bootargs_nfs; "				\
			"tftpboot ${loadaddr} ${kernel}; bootm\0"				\
		"bootargs_mmc=setenv bootargs ${bootargs} ${network} "		\
			"root=/dev/mmcblk0p1 rootwait\0"						\
		"bootcmd_mmc=run bootargs_base bootargs_mmc; "				\
			"mmc dev 3; "											\
			"mmc read ${loadaddr} 0x800 0x3000; bootm\0"			\
		"linux_bootargs=console=tty0 console=ttymxc0,115200 "		\
			"root=/dev/mmcblk0p1 "									\
			"rootwait rw fbmem=10M\0"								\
		"linux_cmd=setenv bootargs ${linux_bootargs};"				\
            "mmc dev 3;"											\
			"mmc read ${loadaddr} 0x800 0x3000;"					\
			"bootm\0"												\
		"bootcmd=run linux_cmd\0"


#define CONFIG_ARP_TIMEOUT	200UL
#define	CONFIG_MX6_SMARC	"SMA-IMX6_A0_0423"

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size */
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS	16	/* max number of command args */
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE /* Boot Argument Buffer Size */

#define CONFIG_SYS_MEMTEST_START	0x10000000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x10010000

#undef	CONFIG_SYS_CLKS_IN_HZ		/* everything, incl board info, in Hz */

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR

#define CONFIG_SYS_HZ			1000

#define CONFIG_CMDLINE_EDITING

#define CONFIG_FEC0_IOBASE	ENET_BASE_ADDR
#define CONFIG_FEC0_PINMUX	-1
#define CONFIG_FEC0_MIIBASE	-1
#define CONFIG_GET_FEC_MAC_ADDR_FROM_IIM
#define CONFIG_MXC_FEC
#define CONFIG_FEC0_PHY_ADDR		0xFF
#define CONFIG_DISCOVER_PHY
#define CONFIG_ETH_PRIME
#define CONFIG_RMII
#define CONFIG_CMD_MII
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_IPADDR			192.168.1.103
#define CONFIG_SERVERIP			192.168.1.101
#define CONFIG_NETMASK			255.255.255.0

/*
 * OCOTP Configs
 */
#ifdef CONFIG_CMD_IMXOTP
	#define CONFIG_IMX_OTP
	#define IMX_OTP_BASE			OCOTP_BASE_ADDR
	#define IMX_OTP_ADDR_MAX		0x7F
	#define IMX_OTP_DATA_ERROR_VAL	0xBADABADA
#endif

/*
 * I2C Configs
 */
#ifdef CONFIG_CMD_I2C
	#define CONFIG_HARD_I2C         1
	#define CONFIG_I2C_MXC          1
	#define CONFIG_SYS_I2C_PORT             I2C1_BASE_ADDR
	#define CONFIG_SYS_I2C_SPEED            100000
	#define CONFIG_SYS_I2C_SLAVE            0x8
	#define CONFIG_MX6_INTER_LDO_BYPASS		0
#endif

/*
 * SPI Configs
 */
#ifdef CONFIG_CMD_SF
	#define CONFIG_FSL_SF		1
	#define CONFIG_SPI_FLASH_IMX_M25PXX	1
	#define CONFIG_SPI_FLASH_CS	0
	#define CONFIG_IMX_ECSPI
	#define IMX_CSPI_VER_2_3	1
	#define MAX_SPI_BYTES		(64 * 4)
#endif

/* Regulator Configs */
#ifdef CONFIG_CMD_REGUL
	#define CONFIG_ANATOP_REGULATOR
	#define CONFIG_CORE_REGULATOR_NAME "vdd1p1"
	#define CONFIG_PERIPH_REGULATOR_NAME "vdd1p1"
#endif

/*
 * MMC Configs
 */
#ifdef CONFIG_CMD_MMC
	#define CONFIG_MMC
	#define CONFIG_GENERIC_MMC
	#define CONFIG_IMX_MMC
	#define CONFIG_SYS_FSL_USDHC_NUM        4
	#define CONFIG_SYS_FSL_ESDHC_ADDR       0
	#define CONFIG_SYS_MMC_ENV_DEV  2
	#define CONFIG_DOS_PARTITION	1
	#define CONFIG_CMD_FAT		1
	#define CONFIG_CMD_EXT2		1

	/* detect whether SD1, 2, 3, or 4 is boot device */
	#define CONFIG_DYNAMIC_MMC_DEVNO

	/* SD3 and SD4 are 8 bit */
	#define CONFIG_MMC_8BIT_PORTS   0xC
	/* Setup target delay in DDR mode for each SD port */
	#define CONFIG_GET_DDR_TARGET_DELAY
#endif

/*
 * FUSE Configs
 * */
//#define	CONFIG_CMD_IIM
#ifdef CONFIG_CMD_IIM
    #define CONFIG_IMX_IIM
    #define IMX_IIM_BASE    IIM_BASE_ADDR
    #define CONFIG_IIM_MAC_BANK 1
    #define CONFIG_IIM_MAC_ROW  9
#endif


/*
 * SATA Configs
 */
#ifdef CONFIG_CMD_SATA
	#define CONFIG_DWC_AHSATA
	#define CONFIG_SYS_SATA_MAX_DEVICE	1
	#define CONFIG_DWC_AHSATA_PORT_ID	0
	#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR
	#define CONFIG_LBA48
	#define CONFIG_LIBATA

	#define CONFIG_DOS_PARTITION	1
	#define CONFIG_CMD_FAT		1
	#define CONFIG_CMD_EXT2		1
#endif

/*
 * GPMI Nand Configs
 */
/* #define CONFIG_CMD_NAND */

#ifdef CONFIG_CMD_NAND
	#define CONFIG_NAND_GPMI
	#define CONFIG_GPMI_NFC_SWAP_BLOCK_MARK
	#define CONFIG_GPMI_NFC_V2

	#define CONFIG_GPMI_REG_BASE	GPMI_BASE_ADDR
	#define CONFIG_BCH_REG_BASE	BCH_BASE_ADDR

	#define NAND_MAX_CHIPS		8
	#define CONFIG_SYS_NAND_BASE		0x40000000
	#define CONFIG_SYS_MAX_NAND_DEVICE	1

	/* NAND is the unique module invoke APBH-DMA */
	#define CONFIG_APBH_DMA
	#define CONFIG_APBH_DMA_V2
	#define CONFIG_MXS_DMA_REG_BASE	ABPHDMA_BASE_ADDR
#endif

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	(128 * 1024)	/* regular stack */

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	1
#define PHYS_SDRAM_1		CSD0_DDR_BASE_ADDR
#define iomem_valid_addr(addr, size) \
	(addr >= PHYS_SDRAM_1 && addr <= (PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE))

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CONFIG_SYS_NO_FLASH

/* Monitor at beginning of flash */
#define CONFIG_FSL_ENV_IN_MMC
/* #define CONFIG_FSL_ENV_IN_NAND */
/* #define CONFIG_FSL_ENV_IN_SATA */

#define CONFIG_ENV_SECT_SIZE    (8 * 1024)
#define CONFIG_ENV_SIZE         CONFIG_ENV_SECT_SIZE

#if defined(CONFIG_FSL_ENV_IN_NAND)
	#define CONFIG_ENV_IS_IN_NAND 1
	#define CONFIG_ENV_OFFSET	0x100000
#elif defined(CONFIG_FSL_ENV_IN_MMC)
	#define CONFIG_ENV_IS_IN_MMC	1
	#define CONFIG_ENV_OFFSET	(768 * 1024)
#elif defined(CONFIG_FSL_ENV_IN_SATA)
	#define CONFIG_ENV_IS_IN_SATA   1
	#define CONFIG_SATA_ENV_DEV     0
	#define CONFIG_ENV_OFFSET       (768 * 1024)
#elif defined(CONFIG_FSL_ENV_IN_SF)
	#define CONFIG_ENV_IS_IN_SPI_FLASH	1
	#define CONFIG_ENV_SPI_CS		1
	#define CONFIG_ENV_OFFSET       (768 * 1024)
#else
	#define CONFIG_ENV_IS_NOWHERE	1
#endif

#ifdef CONFIG_SPLASH_SCREEN
	/*
	 * Framebuffer and LCD
	 */
	#define	SMARC_SCREEN_OFF
	#define	SMARC_LVDS_BKLT_EN	IMX_GPIO_NR(3, 0)
	#define	SMARC_LCD_VDD_EN	IMX_GPIO_NR(2, 22)
	#define CONFIG_LCD
	#define CONFIG_IPU_V3H
	#define CONFIG_VIDEO_MX5
	#define CONFIG_IPU_CLKRATE	260000000
	#define CONFIG_SYS_CONSOLE_ENV_OVERWRITE
	#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
	#define CONFIG_SYS_CONSOLE_IS_IN_ENV
	#define LCD_BPP		LCD_COLOR16
	#define CONFIG_CMD_BMP
	#define CONFIG_BMP_8BPP
	#define CONFIG_FB_BASE	(TEXT_BASE + 0x300000)
	#define CONFIG_SPLASH_SCREEN_ALIGN
	#define CONFIG_SYS_WHITE_ON_BLACK

	#define CONFIG_IMX_PWM
	#define IMX_PWM1_BASE    PWM1_BASE_ADDR
	#define IMX_PWM2_BASE    PWM2_BASE_ADDR
#endif

#ifdef	CONFIG_USING_ANDROID

#define CONFIG_USB_DEVICE
#define CONFIG_IMX_UDC             1
#define CONFIG_FASTBOOT            1
#define CONFIG_FASTBOOT_STORAGE_EMMC_SATA
#define CONFIG_FASTBOOT_VENDOR_ID      0x18d1
#define CONFIG_FASTBOOT_PRODUCT_ID     0x0d02
#define CONFIG_FASTBOOT_BCD_DEVICE     0x311
#define CONFIG_FASTBOOT_MANUFACTURER_STR  "Freescale"
#define CONFIG_FASTBOOT_PRODUCT_NAME_STR "i.mx6q Sabre Smart Device"
#define CONFIG_FASTBOOT_INTERFACE_STR    "Android fastboot"
#define CONFIG_FASTBOOT_CONFIGURATION_STR  "Android fastboot"
#define CONFIG_FASTBOOT_SERIAL_NUM  "12345"
#define CONFIG_FASTBOOT_SATA_NO      0

/*  For system.img growing up more than 256MB, more buffer needs
*   to receive the system.img*/
#define CONFIG_FASTBOOT_TRANSFER_BUF    0x2c000000
#define CONFIG_FASTBOOT_TRANSFER_BUF_SIZE 0x14000000 /* 320M byte */

#define CONFIG_CMD_BOOTI
#define CONFIG_ANDROID_RECOVERY
/* which mmc bus is your main storage ? */
#define CONFIG_ANDROID_MAIN_MMC_BUS 3
#define CONFIG_ANDROID_BOOT_PARTITION_MMC 1
#define CONFIG_ANDROID_SYSTEM_PARTITION_MMC 5
#define CONFIG_ANDROID_RECOVERY_PARTITION_MMC 2
#define CONFIG_ANDROID_CACHE_PARTITION_MMC 6


#define CONFIG_ANDROID_RECOVERY_BOOTARGS_MMC NULL
#define CONFIG_ANDROID_RECOVERY_BOOTCMD_MMC  \
    "booti mmc3 recovery"
#define CONFIG_ANDROID_RECOVERY_CMD_FILE "/recovery/command"
#define CONFIG_INITRD_TAG

/*
#undef CONFIG_LOADADDR
#undef CONFIG_RD_LOADADDR
#undef CONFIG_EXTRA_ENV_SETTINGS

#define CONFIG_LOADADDR     0x10800000
#define CONFIG_RD_LOADADDR      0x11000000
*/

#define CONFIG_INITRD_TAG

/*
#define CONFIG_EXTRA_ENV_SETTINGS                   \
        "netdev=eth0\0"                     \
        "ethprime=FEC0\0"                   \
        "fastboot_dev=mmc3\0"                   \
        "bootcmd=booti mmc3\0"                  \
        "splashimage=0x30000000\0"              \
        "splashpos=m,m\0"                   \
        "lvds_num=0\0"
*/
#endif
#endif				/* __CONFIG_H */
