#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)

export CROSS_COMPILE="$SCRIPT_DIR/../third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-"
export BUILD_DIR="$SCRIPT_DIR/../build/"


cd third_party/tf-a

make ARCH=aarch32 DEBUG=1 AARCH32_SP=optee \
     BL33_CFG=$BUILD_DIR/u-boot.dtb \
     BL33=$BUILD_DIR/u-boot-nodtb.bin \
     BL32=$BUILD_DIR/tee-header_v2.bin \
     BL32_EXTRA1=$BUILD_DIR/tee-pager_v2.bin \
     BL32_EXTRA2=$BUILD_DIR/tee-pageable_v2.bin \
     PLAT=stm32mp1 STM32MP13=1 DTB_FILE_NAME=stm32mp135f-dk.dtb \
     STM32MP_SDMMC=1 STM32IMAGE=/tools/stm32image/stm32image all fip

