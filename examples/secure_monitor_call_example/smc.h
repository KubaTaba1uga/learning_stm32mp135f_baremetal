#ifndef SCM_H
#define SCM_H

#include <stdint.h>

static inline const char *smc_get_psci_version(void) {
  unsigned int version;

  asm volatile("ldr     r0, =0x84000000");
  asm volatile("smc #0");
  asm volatile("mov %0, r0" : "=r"(version));

  switch (version) {
  case 0x00000002:
    return "0.2"    ;
  case 0x00010000:
    return "1.0";
  case 0x00010001:
    return "1.1";
  default:
    return 0;
  }
};

#endif
