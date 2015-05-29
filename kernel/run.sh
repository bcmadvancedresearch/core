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

if [ $1 == "menuconfig" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE $1
	exit;
fi

make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE imx_v7_defconfig
make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE $1

