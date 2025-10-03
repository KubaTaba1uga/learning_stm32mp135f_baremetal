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
bash scripts/compile_uboot.sh
```

build optee:
```
bash scripts/compile_optee.sh
```

build tf-a:
```
bash scripts/compile_tfa.sh
```

flash to sdcard:
```
sudo dd if=build/tf-a-stm32mp135f-dk.stm32 of=/dev/disk/by-partlabel/fsbl1 bs=1K
sudo dd if=build/tf-a-stm32mp135f-dk.stm32 of=/dev/disk/by-partlabel/fsbl2 bs=1K
sudo dd if=build/fip.bin of=/dev/disk/by-partlabel/fip bs=1K
```


## Flash to memory 

Add dfu to uboot:
```
CONFIG_CMD_DFU=y
CONFIG_USB_FUNCTION_DFU=y
```
flash to memory:
```

```
