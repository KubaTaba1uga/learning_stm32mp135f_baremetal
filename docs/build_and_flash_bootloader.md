## Build u-boot

Prepare sdcard:
```
sudo sgdisk -o /dev/sdb
sudo sgdisk --resize-table=128        \
            -a 1 -n 1:34:545          \
			-c 1:fsbl1 -n 2:546:1057  \
            -c 2:fsbl2 -n 3:1058:9249 \
            -c 3:fip   -n 4:9250:     \
			-c 4:rootfs -A 4:set:2    \
			-p /dev/sdb
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
sudo dd if=build/tf-a-stm32mp135f-dk.stm32 of=/dev/disk/by-partlabel/fsbl1 bs=1K conv=fsync
sudo dd if=build/tf-a-stm32mp135f-dk.stm32 of=/dev/disk/by-partlabel/fsbl2 bs=1K conv=fsync
sudo dd if=build/fip.bin of=/dev/disk/by-partlabel/fip bs=1K conv=fsync
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
