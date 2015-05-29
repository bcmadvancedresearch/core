#!/bin/bash

LOCAL_PATH=`pwd`
ARCH=arm
CROSS_COMPILE=$LOCAL_PATH/../fsl/bin/arm-fsl-linux-gnueabi-

if [ $1 == "distclean" ]; then
	make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE distclean
	rm -f imxcfg.imx
	rm -f u-boot-6*
	exit;
fi

if [ $1 == "sabresd" ]; then
	PLATFORM=mx6qsabresd_config
fi

if [ $1 == "quad-p" ]; then
	PLATFORM=mx6qsmarc-p_config
fi

if [ $1 == "solo-p" ]; then
	PLATFORM=mx6solosmarc-p_config
fi

JOBS=$2

make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE $PLATFORM
make ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE $JOBS

