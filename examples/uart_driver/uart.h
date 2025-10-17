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
#define UART4 ((struct uart *)0x40010000U)
#define UART5 ((struct uart *)0x40011000U)
#define USART6 ((struct uart *)0x44003000U)
#define UART7 ((struct uart *)0x40018000U)
#define UART8 ((struct uart *)0x40019000U)

enum {
  UART_CR1_UE,
  UART_CR1_UESM,
  UART_CR1_RE,
  UART_CR1_TE,
  UART_CR1_IDLEIE,
  UART_CR1_RXFNEIE,
  UART_CR1_TCIE,
  UART_CR1_TXFNFIE,
  UART_CR1_PEIE,
  UART_CR1_PS,
  UART_CR1_PCE,
  UART_CR1_WAKE,
  UART_CR1_M0,
  UART_CR1_MME,
  UART_CR1_CMIE,
  UART_CR1_OVER8,
  UART_CR1_DEDT,
  UART_CR1_DEAT,
  UART_CR1_RTOIE,
  UART_CR1_EOBIE,
  UART_CR1_M1,
  UART_CR1_FIFOEN,
  UART_CR1_TXFEIE,
  UART_CR1_RXFFIE,
};

static inline void uart_init(struct uart *uart) {
  { // Reset UART
    uart->CR1 = 0;
    uart->CR2 = 0;
    uart->CR3 = 0;
    uart->BRR = 0;
    uart->GTPR = 0;
    uart->RTOR = 0;
    uart->RQR = 0;
    uart->ISR = 0x000000C0;
    uart->ICR = 0;
    uart->RDR = 0;
    uart->TDR = 0;
    uart->PRESC = 0;
    uart->HWCFGR2 = 0x00000014;

    if ((uart >= USART1 && uart <= USART3) || (uart == USART6)) {
      uart->HWCFGR1 = 0x40111111;
    } else {
      uart->HWCFGR1 = 0x40110111;
    }

    uart->VERR = 0x00000024;
    uart->IPIDR = 0x00130003;
    uart->SIDR = 0xA3C5DD01;
  }
}

static inline void uart_set_baud_rate(struct uart *uart, uint32_t clk_freq,
                                      uint32_t baud_rate) {
  uart->BRR = clk_freq / baud_rate;
}

static inline void uart_set_tx(struct uart *uart, bool enable) {
  if (enable) {
    uart->CR1 |= (1U << 3); // Enable transmiter
  } else {
    uart->CR1 &= ~(1U << 3); // Disable transmiter
  }
}

static inline void uart_set_rx(struct uart *uart, bool enable) {
  if (enable) {
    uart->CR1 |= (1U << 2); // Enable receiver
  } else {
    uart->CR1 &= ~(1U << 2); // Disable receiver
  }
}

static inline void uart_set_enable(struct uart *uart, bool enable) {
  if (enable) {
    uart->CR1 |= (1U); // Enable uart
  } else {
    uart->CR1 &= ~(1U); // Disable uart
  }
}

static inline void uart_write_char(struct uart *uart, char c) {
  /* According to manual:
      This register must be written only when TXE / TXFNF = 1.
     TXE is 7th bit.
  */
  while (!(uart->ISR & (1U << 7))) {
    (void)uart;
  }

  uart->TDR = c;
}

static inline void uart_write_str(struct uart *uart, const char *str) {
  while (*str) {
    while (!(uart->ISR & (1U << 7))) {
      (void)uart;
    }

    uart->TDR = (*str++);
  }
}

static inline char uart_read_char(struct uart *uart) {
  /* According to manual:
       RXNE bit is set by hardware when the content of the USART_RDR shift
       register has been transferred to the USART_RDR register. It is cleared by
       reading from the USART_RDR register.

     RXNE is 5th bit.
  */

  while (!(uart->ISR & (1U << 5))) {
  }

  return uart->RDR;
};

#endif
