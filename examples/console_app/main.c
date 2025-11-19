//
///
////
/////
/**************************************************************************

                                CONSOLE APP

  This example show how to implement simple console app.

  We are using UART4 because this is the uart used by tf-a/optee/uboot by
  default.

  To show implemented commands run `help`.

**************************************************************************/
///
//

#include "cli.h"
#include "uart.h"

struct uart *mystdout;

int main(void) {
  mystdout = UART4;
  
  cli_run();

  return 0;
}
