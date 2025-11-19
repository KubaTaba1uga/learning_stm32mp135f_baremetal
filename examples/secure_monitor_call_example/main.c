//
///
////
/////
/**************************************************************************

                             SECURE MONITOR CALL

Example demonstrates how one can isee SCM call fron non secure world to access
secure world functionalities on STM32MP135.

SMC call has a structure. `r0` register is used to input function id that will
be executed, registers `r1-r7` are used to handle function args, one function is
over it return value is stored in r0.

Secure monitor role is handled by optee so to find what SMCs are available one
have to browse optee src tree. One of examples lays in
optee-os/core/arch/arm/include/sm/psci.h.

In this example we are fetching version of psci using function id 0x84000000.
The return value of the function will be one of the versions:
 - version 0.2: 0x00000002
 - version 1.0: 0x00010000
 - version 1.1: 0x00010001


**************************************************************************/
///
//
#include <stdint.h>

#include "smc.h"
#include "stdlib.h"
#include "string.h"
#include "uart.h"

struct uart *stdout = NULL;

int main(void) {
  stdout = UART4;

  print("PSCI version: ");

  const char *psci_version = smc_get_psci_version();
  if (psci_version) {
    puts(psci_version);
  } else {
    puts("Unkown");
  }

  return 0;
}
