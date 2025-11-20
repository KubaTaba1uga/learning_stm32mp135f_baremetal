# learning_stm32mp135f_baremetal

This repository contains a collection of **bare‑metal examples for the STM32MP135F‑DK**, each focused on a different hardware block or CPU feature. These examples are meant to be simple, isolated learning pieces: timers, drivers, secure monitor calls, C environment, linker scripts and more.

## `examples/console_app`

The **console_app** example ties everything together. It provides a tiny command‑line interface over UART4 that lets you interact with memory, test peripherals, and run small experiments without Linux or U‑Boot shells.

A minimal UART4-based console runs directly on the MPU without Linux. It provides a tiny shell with simple commands (`help`, `echo`, `memread`, `memwrite`, `sleep`, `reboot`, `shutdown`, `version`) and is useful for testing memory access, timing, and basic hardware bring-up.

Boot flow used for this example:
```txt
TF-A -> OP-TEE -> U-Boot -> console_app (loaded via TFTP)
```

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
