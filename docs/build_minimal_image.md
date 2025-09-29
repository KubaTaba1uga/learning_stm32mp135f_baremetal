## Getting started

OP-TEE Os provide set of tools and libraries for board bring up, one of the boards they support is STM32MP135F-DK.

We will base our toolchain on top of op-tee repository.

Download OP-TEE OS repo:
```bash
mkdir -p third_party
cd third_party
repo init -u https://github.com/OP-TEE/manifest.git -m stm32mp1.xml -b 4.7.0
repo sync
```

Build OP-TEE OS:
```bash
cd build
make -j 8 toolchains
cd ../u-boot
make stm32mp13_defconfig
cd ../build
make -j 8 PLATFORM=stm32mp1-135F_DK tfa optee-os u-boot
```
