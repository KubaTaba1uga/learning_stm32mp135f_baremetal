BREXT_FLAVOR		= STM32MP135F-DK
STM32MP1_DTS_BASENAME	= stm32mp135f-dk
STM32MP1_DEFCONFIG_U_BOOT = stm32mp13_defconfig

TFA_BIN			:= tf-a-$(STM32MP1_DTS_BASENAME).stm32
TFA_FIP_BIN		:= fip.bin
OPTEE_HEADER_BIN	:= tee-header_v2.bin
OPTEE_PAGER_BIN		:= tee-pager_v2.bin
OPTEE_PAGEABLE_BIN  	:= tee-pageable_v2.bin
U_BOOT_BIN		:= u-boot.bin
U_BOOT_DTB		:= u-boot.dtb

AARCH32_GCC_VERSION 		?= arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf
SRC_AARCH32_GCC 		?= https://developer.arm.com/-/media/Files/downloads/gnu/11.3.rel1/binrel/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf.tar.xz
AARCH32_CROSS_COMPILE 		?= $(AARCH32_PATH)/bin/arm-linux-gnueabihf-

OPTEE_OS_COMMON_FLAGS ?= \
	$(OPTEE_OS_COMMON_EXTRA_FLAGS) \
	PLATFORM=stm32mp1-135F_DK \
	CROSS_COMPILE=$(CROSS_COMPILE_S_USER) \
	$(OPTEE_OS_TA_CROSS_COMPILE_FLAGS) \
	CFG_TEE_CORE_LOG_LEVEL=3 \
	DEBUG=1 


