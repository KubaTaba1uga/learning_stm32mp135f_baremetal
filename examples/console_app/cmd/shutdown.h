#ifndef SHUTDOWN_H
#define SHUTDOWN_H

#include <stdint.h>

#include "common.h"
#include "stdlib.h"
#include "rcc.h"

static inline int __cmd_shutdown(int argc, char *argv[]) {
  // To shutdown CPU we need to put it in standby mode.
  // Bit 31 of RCC_BDCR is responsible for activating a restart.
  // To detect whether reset is secure only check out bit 25 of
  //   RCC_SECCFGR.
  // If reset is secure use SMC to perform shutdown.
  //   More info in optee-os/core/arch/arm/include/sm/psci.h.

  if (RCC->SECCFGR & (1U << 31)) {
    asm volatile("ldr r0, =0x84000008");
    asm volatile("smc #0");
  } else {
    puts("Shutdown is available only in secure world");
    return ERROR_INVALID_INPUT;
  }

  return 0;
}

#endif
