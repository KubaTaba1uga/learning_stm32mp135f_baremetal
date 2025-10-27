#include "stdlib.h"
#include "uart.h"

struct uart *stdout = NULL;

int main(void) {
  stdout = UART4;

  puts("Hello world");
  
  return 0;  
}
