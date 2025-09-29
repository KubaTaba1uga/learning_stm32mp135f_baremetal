## Build u-boot

Prepare sdcard:
```
sudo parted /dev/sda mklabel gpt
sudo parted -a optimal /dev/sda -- mkpart fsbl1 256KiB 512KiB
sudo parted -a optimal /dev/sda -- mkpart fsbl2 512KiB 768KiB
sudo parted -a optimal /dev/sda -- mkpart fip 768KiB 4864KiB
```

build uboot:
```
cd third_party/u-boot
make stm32mp13_defconfig
make -j 8 all
```

build optee:
```
make PLATFORM=stm32mp1-135F_DK -j 8 tfa optee-os u-boot
```

