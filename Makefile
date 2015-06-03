ARCH := arm
CROSS_COMPILE := $(shell pwd)/fsl/bin/arm-fsl-linux-gnueabi-

############
# REV-SA01 #
############
rev-sa01: u-boot kernel
u-boot: rev-sa01-uboot.bin
kernel: rev-sa01-kernel.bin

##########
# Kernel #
##########
rev-sa01-kernel.bin: cleankernel
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C kernel/ imx6_rev_sa01_defconfig
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C kernel/ uImage
	install kernel/arch/arm/boot/uImage uImage

##########
# U-Boot #
##########
rev-sa01-uboot.bin: cleanuboot
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6q_rev_sa01_2g_config
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/
	install u-boot/u-boot.bin u-boot-quad-2g.bin
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6q_rev_sa01_config
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/
	install u-boot/u-boot.bin u-boot-quad.bin
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6solo_rev_sa01_config
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/
	install u-boot/u-boot.bin u-boot-solo.bin

clean:
	$(MAKE) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) CROSS_COMPILE=$(CROSS_COMPILE) -C kernel/ distclean
	rm -f u-boot-solo.bin u-boot-quad.bin uImage u-boot-quad-2g.bin \
		kernel/arch/arm/boot/Image \
		kernel/arch/arm/boot/compressed/lib1funcs.S \
		kernel/arch/arm/boot/compressed/piggy.gzip \
		kernel/arch/arm/boot/compressed/vmlinux \
		kernel/arch/arm/boot/compressed/vmlinux.lds \
		kernel/arch/arm/boot/uImage \
		kernel/arch/arm/boot/zImage \
		kernel/arch/arm/kernel/vmlinux.lds

cleankernel:
	rm -f uImage

cleanuboot:
	rm -f u-boot-solo.bin u-boot-quad.bin u-boot-quad-2g.bin

