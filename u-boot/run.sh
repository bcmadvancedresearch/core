#!/bin/bash

LOCAL_PATH=`pwd`
ARCH=arm
CROSS_COMPILE=$LOCAL_PATH/../fsl/bin/arm-fsl-linux-gnueabi-
JOBS=$1

if [ $1 == "distclean" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE distclean
	exit;
fi

if [ $1 == "rev-sa01" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE mx6q_rev_sa01_config
	JOBS=$2
fi

if [ $1 == "rev-sa01-2g" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE mx6q_rev_sa01_2g_config
	JOBS=$2
fi

if [ $1 == "smarc-mfg" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE mx6q_smarc_mfg_config
	JOBS=$2
fi

if [ $1 == "smarc-2g-mfg" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE mx6q_smarc_2g_mfg_config
	JOBS=$2
fi

if [ $1 == "smarc-solo-mfg" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE mx6solo_smarc_mfg_config
	JOBS=$2
fi

if [ $1 == "smarc-solo-512-mfg" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE mx6solo_smarc_512_mfg_config
	JOBS=$2
fi

if [ $1 == "smarc-dl-mfg" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE mx6dl_smarc_mfg_config
	JOBS=$2
fi

if [ $1 == "rev-sa01-solo" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE mx6solo_rev_sa01_config
	JOBS=$2
fi

if [ $1 == "rev-sa01-solo-512" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE mx6solo_rev_sa01_512_config
	JOBS=$2
fi

if [ $1 == "rev-sa01-dl" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE mx6dl_rev_sa01_config
	JOBS=$2
fi

make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE $JOBS

