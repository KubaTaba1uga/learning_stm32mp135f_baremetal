#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stdint.h>

struct uart {
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t BRR;
  volatile uint32_t GTPR;
  volatile uint32_t RTOR;  
  volatile uint32_t RQR;
  volatile uint32_t ISR;
  volatile uint32_t ICR;
  volatile uint32_t RDR;
  volatile uint32_t TDR;
  volatile uint32_t PRESC;
  volatile uint8_t _reserved[954];
  volatile uint32_t HWCFGR2;
  volatile uint32_t HWCFGR1;
  volatile uint32_t VERR;
  volatile uint32_t IPIDR;  
  volatile uint32_t SIDR;
};

#define USART1 ((struct uart *)0x4C000000U)
#define USART2 ((struct uart *)0x4C001000U)
#define USART3 ((struct uart *)0x4000F000U)
#define UART4  ((struct uart *)0x40010000U)
#define UART5  ((struct uart *)0x40011000U)
#define USART6 ((struct uart *)0x44003000U)
#define UART7  ((struct uart *)0x40018000U)
#define UART8  ((struct uart *)0x40019000U)


#endif
