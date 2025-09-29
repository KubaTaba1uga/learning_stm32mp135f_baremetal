#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)

export CROSS_COMPILE="$SCRIPT_DIR/../third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-"

cd third_party/u-boot
make stm32mp13_defconfig 
make DEVICE_TREE=stm32mp135f-dk -j 8 all

mkdir -p ../../build
cp u-boot-nodtb.bin ../../build/
cp u-boot.dtb ../../build/
