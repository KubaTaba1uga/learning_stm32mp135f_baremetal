#ifndef REBOOT_H
#define REBOOT_H

#include <stdint.h>

#include "rcc.h"
#include "stdlib.h"

static inline int cmd_reboot(int argc, char *argv[]) {
  // Bit 31 of RCC_BDCR is responsible for activating a restart.
  // To detect whether reset is secure only check out bit 25 of
  //   RCC_SECCFGR.

  if (RCC->SECCFGR & (1U << 25)){
    puts("Reset is secure");
  } else {
    puts("Reset is not secure");
  }
  
  for (uint32_t i = 1; i < argc; i++) {
    print(argv[i]);
    putchar(' ');
  }


  
    /* ldr     r0, =0x84000009     */
    /* smc     #0 */

  
  puts("");
  
  return 0;
}

#endif
