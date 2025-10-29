//
///
////
/////
/**************************************************************************

                                CONSOLE APP

  This example show how to implement simple console app.

  We are using UART4 because this is the uart used by tf-a/optee/uboot by
  default.

  Implemented commands are:
  - help
    Show info how to use the console.

**************************************************************************/
///
//

#include "cli.h"
#include "uart.h"

struct uart *stdout;

int main(void) {
  stdout = UART4;
  
  cli_run();

  return 0;
}
