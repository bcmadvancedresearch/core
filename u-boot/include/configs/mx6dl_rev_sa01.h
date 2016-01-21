#ifndef	SMARC_SOLO_REV_SA01_CONFIG
#define	SMARC_SOLO_REV_SA01_CONFIG
#include "mx6_rev-sa01.h"

#define CONFIG_MX6DL
#define CONFIG_MX6DL_DDR3
#define CONFIG_MX6SOLO_SMARC
#define	NEW_VERSION_SMARC

#define CONFIG_SYS_PROMPT	"MX6 Solo SMARC U-Boot > "

#ifdef	NEW_VERSION_SMARC
#define	PHYS_SDRAM_1_SIZE	(1u * 1024 * 1024 * 1024)
#else
#define	PHYS_SDRAM_1_SIZE	(1u * 512 * 1024 * 1024)
#endif
#endif
