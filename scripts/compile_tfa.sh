#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)

export CROSS_COMPILE="$SCRIPT_DIR/../third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-"
export BUILD_DIR="$SCRIPT_DIR/../build"


cd third_party/tf-a

# make ARCH=aarch32 DEBUG=1 AARCH32_SP=optee \
#      BL33_CFG=$BUILD_DIR/u-boot.dtb \
#      BL33=$BUILD_DIR/u-boot-nodtb.bin \
#      BL32=$BUILD_DIR/tee-header_v2.bin \
#      BL32_EXTRA1=$BUILD_DIR/tee-pager_v2.bin \
#      BL32_EXTRA2=$BUILD_DIR/tee-pageable_v2.bin \
#      LOG_LEVEL=50 \
#      PLAT=stm32mp1 STM32MP13=1 DTB_FILE_NAME=stm32mp135f-dk.dtb \
#      STM32MP_SDMMC=1 STM32IMAGE=/tools/stm32image/stm32image ARM_ARCH_MAJOR=7 all fip

     # PLAT=stm32mp1 STM32MP13=1 DTB_FILE_NAME=stm32mp135f-dk.dtb \

CROSS_COMPILE="/usr/bin/ccache /home/taba1uga/Github/learning_stm32mp135f_baremetal/third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-" CC="/usr/bin/ccache /home/taba1uga/Github/learning_stm32mp135f_baremetal/third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-gcc" LD="/usr/bin/ccache /home/taba1uga/Github/learning_stm32mp135f_baremetal/third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-ld" make BL32=$BUILD_DIR/tee-header_v2.bin BL32_EXTRA1=$BUILD_DIR/tee-pager_v2.bin BL32_EXTRA2=$BUILD_DIR/tee-pageable_v2.bin BL33=$BUILD_DIR/u-boot.bin BL33_CFG=$BUILD_DIR/u-boot.dtb ARM_ARCH_MAJOR=7 ARCH=aarch32 PLAT=stm32mp1 DTB_FILE_NAME=stm32mp135f-dk.dtb AARCH32_SP=optee DEBUG=0 LOG_LEVEL=30 STM32MP15_OPTEE_RSV_SHM=0 STM32MP_EMMC=1 STM32MP_SDMMC=1 STM32MP_RAW_NAND=0 STM32MP_SPI_NAND=0 STM32MP_SPI_NOR=0 all fip -j 2


cp build/stm32mp1/*/fip.bin $BUILD_DIR/fip.bin
cp build/stm32mp1/*/tf-a-stm32mp135f-dk.stm32 $BUILD_DIR/tf-a-stm32mp135f-dk.stm32



