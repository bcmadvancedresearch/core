ARCH := arm
CROSS_COMPILE := $(shell pwd)/fsl/bin/arm-fsl-linux-gnueabi-
MAKEJOBS := 2

# When building against a Yocto SDK an environment is provided and in the 
# case of building U-boot the definition for "CC" must be forwarded into the 
# make command. If this isn't done you'll get an error from bfd missing a gcc lib.
ifdef OECORE_SDK_VERSION
CC_FEEDFORWARD := CC="$(CC)"
endif

############
# MAINCAR  #
############

all: rev-sa01
rev-sa01: uboot kernel
uboot: uboot.bin
kernel: kernel.bin
cleanall: clean cleankernel cleanuboot

##########
# Kernel #
##########

kernel.bin: cleankernel
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C kernel/ imx_v7_defconfig
	$(MAKE) -j $(MAKEJOBS) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C kernel/
	mkdir -p out/kernel-modules
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) INSTALL_MOD_PATH=$(shell pwd)/out/kernel-modules -C kernel/ modules_install 
	tar czf out/kernel-modules.tar.gz -C out/kernel-modules/ .
	install kernel/arch/$(ARCH)/boot/zImage out/zImage
	install kernel/arch/$(ARCH)/boot/dts/imx6q-rev-sa01-pfuze100.dtb out/imx6q-rev-sa01-pfuze100.dtb
	install kernel/arch/$(ARCH)/boot/dts/imx6q-rev-sa01-wm8326.dtb out/imx6q-rev-sa01-wm8326.dtb
	install kernel/arch/$(ARCH)/boot/dts/imx6solo-rev-sa01-pfuze100.dtb out/imx6solo-rev-sa01-pfuze100.dtb
	install kernel/arch/$(ARCH)/boot/dts/imx6solo-rev-sa01-wm8326.dtb out/imx6solo-rev-sa01-wm8326.dtb

##########
# U-Boot #
##########

uboot.bin: cleanuboot
	mkdir -p out
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6qsmarc-p_config
	$(MAKE) -j $(MAKEJOBS) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(CC_FEEDFORWARD) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6q-p.imx
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6qsmarc_config
	$(MAKE) -j $(MAKEJOBS) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(CC_FEEDFORWARD) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6q.imx
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6solosmarc-p_config
	$(MAKE) -j $(MAKEJOBS) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(CC_FEEDFORWARD) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6solo-p.imx
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6solosmarc_config
	$(MAKE) -j $(MAKEJOBS) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(CC_FEEDFORWARD) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6solo.imx
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6dlsmarc-p_config
	$(MAKE) -j $(MAKEJOBS) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(CC_FEEDFORWARD) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6dl-p.imx
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ mx6dlsmarc_config
	$(MAKE) -j $(MAKEJOBS) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(CC_FEEDFORWARD) -C u-boot/
	install u-boot/u-boot.imx out/u-boot-6dl.imx

##############
# Janitorial #
##############

clean:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C u-boot/ distclean
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C kernel/ distclean
	rm -rf out \
		kernel/arch/$(ARCH)/boot/compressed/lib1funcs.S \
		kernel/arch/$(ARCH)/boot/compressed/piggy.gzip \
		kernel/arch/$(ARCH)/boot/compressed/vmlinux \
		kernel/arch/$(ARCH)/boot/compressed/vmlinux.lds \
		kernel/arch/$(ARCH)/boot/dts/*.dtb \
		kernel/arch/$(ARCH)/kernel/vmlinux.lds \
		u-boot/imxcfg.imx

cleankernel:
	rm -f out/zImage
	rm -f out/*.dtb kernel/arch/$(ARCH)/boot/dts/*.dtb

cleanuboot:
	rm -f out/*.imx

