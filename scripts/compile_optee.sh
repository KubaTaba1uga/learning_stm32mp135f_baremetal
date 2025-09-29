#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)

OPTEE_OS_COMMON_FLAGS="PLATFORM=stm32mp1-135F_DK CFG_USER_TA_TARGETS=ta_arm32 ARCH=arm CFG_ARM32_core=y CROSS_COMPILE=$SCRIPT_DIR/../third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf- CFG_SCP_FIRMWARE=$SCRIPT_DIR/../third_party/scp-firmware CFG_TEE_CORE_LOG_LEVEL=3 CFG_UNWIND=y DEBUG=1 CFG_EMBED_DTB_SOURCE_FILE=stm32mp135f-dk.dts"

cd third_party/optee-os/

make $OPTEE_OS_COMMON_FLAGS

mkdir -p ../../build
cp ./out/arm-plat-stm32mp1/core/tee.bin ../../build/
cp ./out/arm-plat-stm32mp1/core/tee-raw.bin ../../build/
cp ./out/arm-plat-stm32mp1/core/tee-*_v2.bin ../../build/

