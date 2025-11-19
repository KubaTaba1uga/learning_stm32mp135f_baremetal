# learning_stm32mp135f_baremetal

This repository is a playground for learning **bare-metal development on the STM32MP135F-DK**.  

## `examples/console_app`

A minimal UART4-based console that runs directly on the MPU without Linux.  
It provides a tiny shell with simple commands (`help`, `echo`, `memread`, `memwrite`, `sleep`, `reboot`, `shutdown`) and is useful for testing memory access, timing, and basic hardware bring-up.

Boot flow used for this example:
```txt
TF-A -> OP-TEE -> U-Boot -> console_app (loaded via TFTP)
````

The project includes build automation for this boot chain and the console itself.

```bash
# 1) Fast edit -> build loop (no boot chain, no tests)
inv build -x=console_app --no-boot --no-tests

# 2) Run only console_app tests
inv test -t test_console_app

# 3) Full build: boot chain + console_app + tests
inv build -x=console_app

# 4) Flash boot chain to SD card
inv deploy-to-sdcard
```
