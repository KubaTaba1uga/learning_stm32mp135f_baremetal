## Install deps on debian

```bash
sudo apt-get install -y build-essential device-tree-compiler

sudo apt-get update && sudo apt-get install -y \
  gcc-arm-none-eabi \
  g++ \
  clang \
  device-tree-compiler \
  make \
  libmbedtls-dev \
  nodejs \
  libssl-dev \
  python3-poetry \
  python3-sphinx \
  python3-pip
```

## Download cross compilation toolchain from arm

https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

## Build trusted firmware image

```bash
make ARCH=aarch32 DEBUG=1  PLAT=stm32mp1 STM32MP13=1 DTB_FILE_NAME=stm32mp135f-dk.dtb STM32MP_SDMMC=1 all
```

with optee enabled
```bash
make ARCH=aarch32 DEBUG=1 AARCH32_SP=optee PLAT=stm32mp1 STM32MP13=1 DTB_FILE_NAME=stm32mp135f-dk.dtb STM32MP_SDMMC=1  all
```

To produce SD card image do
```
make ARCH=aarch32 DEBUG=1  PLAT=stm32mp1 STM32MP13=1 DTB_FILE_NAME=stm32mp135f-dk.dtb STM32MP_SDMMC=1 STM32IMAGE=/tools/stm32image/stm32image all
```

Creating stm32image program can be done like this:
```
sudo make -C tools/stm32image
```

```
make ARCH=aarch32 DEBUG=1  PLAT=stm32mp1 STM32MP13=1 DTB_FILE_NAME=stm32mp135f-dk.dtb STM32MP_SDMMC=1 STM32IMAGE=/tools/stm32image/stm32image all
```

Prepare sd card:
```
sudo parted /dev/sda mklabel gpt
sudo parted -a optimal /dev/sda -- mkpart fsbl1 1MiB 5MiB
sudo parted -a optimal /dev/sda -- mkpart fsbl2 5MiB 9MiB
sudo parted -a optimal /dev/sda -- mkpart fip   9MiB 33MiB
```

Write binary:
```
sudo dd if=tf-a-stm32mp135f-dk.stm32 of=/dev/disk/by-partlabel/fsbl1 bs=1M conv=fdatasync
```
