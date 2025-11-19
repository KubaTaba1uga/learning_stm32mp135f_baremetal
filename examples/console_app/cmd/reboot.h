#ifndef REBOOT_H
#define REBOOT_H

#include <stdint.h>

#include "rcc.h"

static inline int __cmd_reboot(int argc, char *argv[]) {
  // Bit 31 of RCC_BDCR is responsible for activating a restart.
  // To detect whether reset is secure only check out bit 25 of
  //   RCC_SECCFGR.
  // If reset is secure use SMC call to perform reboot.
  //   More info in optee-os/core/arch/arm/include/sm/psci.h.

  if (RCC->SECCFGR & (1U << 25)){
    asm volatile ("ldr r0, =0x84000009");
    asm volatile("smc #0");
  } else {
    RCC->BDCR |= (1U << 31);
  }
    
  return 0;
}

#endif
