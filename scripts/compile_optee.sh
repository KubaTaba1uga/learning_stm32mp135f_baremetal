#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)


cd third_party/optee-os/

# OPTEE_OS_COMMON_FLAGS="PLATFORM=stm32mp1-135F_DK CFG_USER_TA_TARGETS=ta_arm32 ARCH=arm CFG_ARM32_core=y CROSS_COMPILE=$SCRIPT_DIR/../third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf- CFG_SCP_FIRMWARE=$SCRIPT_DIR/../third_party/scp-firmware CFG_TEE_CORE_LOG_LEVEL=3 CFG_UNWIND=y DEBUG=1 CFG_EMBED_DTB_SOURCE_FILE=stm32mp135f-dk.dts"
# make $OPTEE_OS_COMMON_FLAGS

make CFG_USER_TA_TARGETS=ta_arm32 CFG_ARM64_core=n PLATFORM=stm32mp1-135F_DK CROSS_COMPILE="/usr/bin/ccache /home/taba1uga/Github/learning_stm32mp135f_baremetal/third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-" CROSS_COMPILE_core="/usr/bin/ccache /home/taba1uga/Github/learning_stm32mp135f_baremetal/third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-" CROSS_COMPILE_ta_arm32="/usr/bin/ccache /home/taba1uga/Github/learning_stm32mp135f_baremetal/third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-" CFG_TEE_CORE_LOG_LEVEL=3 DEBUG=0 CFG_IN_TREE_EARLY_TAS="trusted_keys/f04a0fe7-1f5d-4b9b-abf7-619b85b4ce8c" CFG_SCP_FIRMWARE=/home/taba1uga/Github/learning_stm32mp135f_baremetal/third-party/scp-firmware -j 2


mkdir -p ../../build
cp ./out/arm-plat-stm32mp1/core/tee.bin ../../build/
cp ./out/arm-plat-stm32mp1/core/tee-raw.bin ../../build/
cp ./out/arm-plat-stm32mp1/core/tee-*_v2.bin ../../build/


# make -C /home/taba1uga/Github/optee_bundle/build/../optee_os O=out/arm CFG_USER_TA_TARGETS=ta_arm32 CFG_ARM64_core=n PLATFORM=stm32mp1-135F_DK CROSS_COMPILE="/usr/bin/ccache /home/taba1uga/Github/optee_bundle/build/../toolchains/aarch32/bin/arm-linux-gnueabihf-" CROSS_COMPILE_core="/usr/bin/ccache /home/taba1uga/Github/optee_bundle/build/../toolchains/aarch32/bin/arm-linux-gnueabihf-" CROSS_COMPILE_ta_arm64="/usr/bin/ccache /home/taba1uga/Github/optee_bundle/build/../toolchains/aarch64/bin/aarch64-linux-gnu-" CROSS_COMPILE_ta_arm32="/usr/bin/ccache /home/taba1uga/Github/optee_bundle/build/../toolchains/aarch32/bin/arm-linux-gnueabihf-" CFG_TEE_CORE_LOG_LEVEL=3 DEBUG=0 CFG_IN_TREE_EARLY_TAS="trusted_keys/f04a0fe7-1f5d-4b9b-abf7-619b85b4ce8c" CFG_SCP_FIRMWARE=/home/taba1uga/Github/optee_bundle/build/../scp-firmware
