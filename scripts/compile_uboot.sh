#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)



cd third_party/u-boot
# export CROSS_COMPILE="$SCRIPT_DIR/../third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-"
# make stm32mp13_defconfig 
# make DEVICE_TREE=stm32mp135f-dk all
CROSS_COMPILE="/usr/bin/ccache /home/taba1uga/Github/learning_stm32mp135f_baremetal/third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-" make stm32mp13_defconfig 
CROSS_COMPILE="/usr/bin/ccache /home/taba1uga/Github/learning_stm32mp135f_baremetal/third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-" make DEVICE_TREE=stm32mp135f-dk all -j 2


mkdir -p ../../build
cp u-boot-nodtb.bin ../../build/
cp u-boot.bin ../../build/
cp u-boot.dtb ../../build/

# cd /home/taba1uga/Github/optee_bundle/build/../u-boot && scripts/kconfig/merge_config.sh configs/stm32mp13_defconfig

