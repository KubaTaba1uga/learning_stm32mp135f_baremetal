#ifndef UART_H
#define UART_H

#include <stdint.h>

/* Table 9. Register boundary addresses */
#define UART4_BASE (0x40010000U)
#define USART_TDR (*(volatile uint32_t *)(UART4_BASE + 0x28))
// USART interrupt and status register
#define USART_ISR (*(volatile uint32_t *)(UART4_BASE + 0x1C))

static void write_to_uart(char c) {
  while (!(USART_ISR & (1 << 7))) { // Wait until ready to write char
  }
  
  USART_TDR = c; // Write char
}



#endif
