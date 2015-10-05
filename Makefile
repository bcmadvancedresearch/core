ARCH := arm
CROSS_COMPILE := $(shell pwd)/fsl/bin/arm-fsl-linux-gnueabi-

############
# MAINCAR  #
############
all: rev-sa01
rev-sa01: uboot kernel
uboot: uboot.bin
kernel: kernel.bin

##########
# Kernel #
##########
kernel.bin: cleankernel
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C kernel/ imx_v7_defconfig
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C kernel/
	mkdir -p out
	install kernel/arch/arm/boot/zImage out/zImage
	install kernel/arch/arm/boot/dts/imx6q-rev-sa01-pfuze100.dtb out/imx6q-rev-sa01-pfuze100.dtb
	install kernel/arch/arm/boot/dts/imx6q-rev-sa01-wm8326.dtb out/imx6q-rev-sa01-wm8326.dtb
	install kernel/arch/arm/boot/dts/imx6solo-rev-sa01-pfuze100.dtb out/imx6solo-rev-sa01-pfuze100.dtb
	install kernel/arch/arm/boot/dts/imx6solo-rev-sa01-wm8326.dtb out/imx6solo-rev-sa01-wm8326.dtb

##########
# U-Boot #
##########
uboot.bin: cleanuboot
	mkdir -p out
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6qsmarc-p_config
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6q-p.imx
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6qsmarc_config
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6q.imx
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6solosmarc-p_config
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6solo-p.imx
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6solosmarc_config
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6solo.imx
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6dlsmarc-p_config
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6dl-p.imx
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6dlsmarc_config
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6dl.imx

clean:
	$(MAKE) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) CROSS_COMPILE=$(CROSS_COMPILE) -C kernel/ distclean
	rm -rf out \
		kernel/arch/arm/boot/compressed/lib1funcs.S \
		kernel/arch/arm/boot/compressed/piggy.gzip \
		kernel/arch/arm/boot/compressed/vmlinux \
		kernel/arch/arm/boot/compressed/vmlinux.lds \
		kernel/arch/arm/boot/dts/*.dtb \
		kernel/arch/arm/kernel/vmlinux.lds \
		u-boot/imxcfg.imx

cleankernel:
	rm -f out/zImage
	rm -f out/*.dtb kernel/arch/arm/boot/dts/*.dtb

cleanuboot:
	rm -f out/*.imx

