#ifndef UART_H
#define UART_H

#include "common.h"
#include <cstdint>
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

enum {
  UART_CR1_ALT_UE,
  UART_CR1_ALT_UESM,
  UART_CR1_ALT_RE,
  UART_CR1_ALT_TE,
  UART_CR1_ALT_IDLEIE,
  UART_CR1_ALT_RXFNEIE,
  UART_CR1_ALT_TCIE,
  UART_CR1_ALT_TXEIE,
  UART_CR1_ALT_PEIE,
  UART_CR1_ALT_PS,
  UART_CR1_ALT_PCE,
  UART_CR1_ALT_WAKE,
  UART_CR1_ALT_M0,
  UART_CR1_ALT_MME,
  UART_CR1_ALT_CMIE,
  UART_CR1_ALT_OVER8,
  UART_CR1_ALT_DEDT,
  UART_CR1_ALT_DEAT = UART_CR1_ALT_DEDT + 6,
  UART_CR1_ALT_RTOIE,
  UART_CR1_ALT_EOBIE,
  UART_CR1_ALT_M1,
  UART_CR1_ALT_FIFOEN,
  UART_CR2_SLVEN = UART_CR1_ALT_FIFOEN + 3,
  UART_CR2_NSS = UART_CR2_SLVEN + 3,
  UART_CR2_ADDM7,
  UART_CR2_LBDL,
  UART_CR2_LBDIE,
  UART_CR2_LBCL = UART_CR2_LBDIE + 2,
  UART_CR2_CPHA,
  UART_CR2_CPOL,
  UART_CR2_CLKEN,
  UART_CR2_STOP,
  UART_CR2_LINEN = UART_CR2_STOP + 2,
  UART_CR2_SWAP,
  UART_CR2_RXINV,
  UART_CR2_TXINV,
  UART_CR2_DATAINV,
  UART_CR2_MSBFIRST,
  UART_CR2_ABREN,
  UART_CR2_ABRMOD,
  UART_CR2_RTOEN,
  UART_CR2_ADD,
  UART_CR3_EIE = UART_CR2_ADD + 9,
  UART_CR3_IREN,
  UART_CR3_IRLP,
  UART_CR3_HDSEL,
  UART_CR3_NACK,
  UART_CR3_SCEN,
  UART_CR3_DMAR,
  UART_CR3_DMAT,
  UART_CR3_RTSE,
  UART_CR3_CTSE,
  UART_CR3_CTSIE,
  UART_CR3_ONEBIT,
  UART_CR3_OVRDIS,
  UART_CR3_DDRE,
  UART_CR3_DEM,
  UART_CR3_DEP,
  UART_CR3_SCARCNT = UART_CR3_DEP + 2,
  UART_CR3_WUS = UART_CR3_SCARCNT + 3,
  UART_CR3_WUFIE,
  UART_CR3_TXFTIE,
  UART_CR3_TCBGTIE,
  UART_CR3_RXTCFG,
  UART_CR3_RFXTIE = UART_CR3_RXTCFG + 3,
  UART_CR3_TXTCFG,
};

static inline void uart_set_ctrl(struct uart *uart, uint8_t setting,
                                  uint8_t value) {
  if (setting < UART_CR2_SLVEN) { // Handle CR1
    switch (setting) {
    case UART_CR1_ALT_DEAT:
      BITS_SET(uart->CR1, value, 31, setting);
      break;
    default:
      if (value) {
        BIT_SET(uart->CR1, setting);
      } else {
        BIT_CLEAR(uart->CR1, setting);
      }
    }
  } else if (setting < UART_CR3_EIE) { // Handle CR2
    uint8_t bits = setting - UART_CR2_SLVEN;
    switch (setting) {
    case UART_CR2_STOP:
    case UART_CR2_ABRMOD:
      BITS_SET(uart->CR2, value, 3U, bits);
      break;
    case UART_CR2_ADD:
      BITS_SET(uart->CR1, value, 0xFF, bits);
      break;
    default:
      if (value) {
        BIT_SET(uart->CR1, bits);
      } else {
        BIT_CLEAR(uart->CR1, bits);
      }
    }
  } else { // Handle CR3
    uint8_t bits = setting -  UART_CR3_EIE;
    switch (setting) {
    case UART_CR3_SCARCNT:
    case UART_CR3_RXTCFG: 
    case UART_CR3_TXTCFG:           
      BITS_SET(uart->CR3, value, 7U, bits);
      break;      
    case UART_CR3_WUS:
      BITS_SET(uart->CR3, value, 3U, bits);
      break;
    case UART_CR2_ADD:
      BITS_SET(uart->CR1, value, 0xFF, bits);
      break;
    default:
      if (value) {
        BIT_SET(uart->CR1, bits);
      } else {
        BIT_CLEAR(uart->CR1, bits);
      }
    }
    
  }
}

static inline void uart_set_baud_rate(struct uart *uart, uint32_t clk_freq,
                                      uint32_t baud_rate) {
  uart->BRR = clk_freq / baud_rate;
}

static inline void uart_set_tx(struct uart *uart, bool enable) {
  if (enable) {
    BIT_SET(uart->CR1, 3);
  } else {
    BIT_CLEAR(uart->CR1, 3);
  }
}

static inline void uart_set_rx(struct uart *uart, bool enable) {
  if (enable) {
    BIT_SET(uart->CR1, 2);
  } else {
    BIT_CLEAR(uart->CR1, 2);
  }
}

static inline void uart_set_enable(struct uart *uart, bool enable) {
  if (enable) {
    BIT_SET(uart->CR1, 0);
  } else {
    BIT_CLEAR(uart->CR1, 0);
  }
}

static inline void uart_write_char(struct uart *uart, char c) {
  /* According to manual:
      This register must be written only when TXE / TXFNF = 1.
     TXE is 7th bit.
  */
  while (!BIT_GET(uart->ISR, 7)) {
    (void)uart;
  }

  uart->TDR = c;
}

static inline void uart_write_str(struct uart *uart, const char *str) {
  while (*str) {
    while (!BIT_GET(uart->ISR, 7)) {
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

  while (!BIT_GET(uart->ISR, 5)) {
    (void)uart;
  }

  return uart->RDR;
};

#endif
