#!/bin/bash

LOCAL_PATH=`pwd`
ARCH=arm
CROSS_COMPILE=$LOCAL_PATH/../fsl/bin/arm-fsl-linux-gnueabi-
JOBS=$1

if [ $1 == "distclean" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE distclean
	exit;
fi

if [ $1 == "clean" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE clean
	exit;
fi

if [ $1 == "mfg" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE imx6_smarc_mfg_defconfig
	JOBS=$2
fi

if [ $1 == "rev-sa01" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE imx6_rev_sa01_defconfig
	JOBS=$2
fi

if [ $1 == "rev-sa01-p" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE imx6_rev_sa01_p_defconfig
	JOBS=$2
fi

if [ $1 == "menuconfig" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE menuconfig
	exit;
fi

if [ $1 == "modules" ]; then
	JOBS=$2
fi

make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE KERNELRELEASE=3.0.35 uImage $JOBS

if [ $1 == "modules" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE modules $JOBS
fi
