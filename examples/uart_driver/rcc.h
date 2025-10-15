#ifndef RCC_H
#define RCC_H

#include "common.h"
#include <cstdint>
#include <stdbool.h>
#include <stdint.h>

struct rcc {
  volatile uint32_t SECCFGR;
  volatile uint32_t MP_SREQCLRR;
  volatile uint32_t MP_APRSTCR;
  volatile uint32_t MP_APRSTSR;
  volatile uint32_t PWRLPDLYCR;
  volatile uint32_t MP_GRSTCSETR;
  volatile uint32_t BR_RSTSCLRR;
  volatile uint32_t MP_RSTSSETR;
  volatile uint32_t MP_RSTSCLRR;
  volatile uint32_t MP_IWDGFZCLRR;
  volatile uint32_t MP_CIER;
  volatile uint32_t BDCR;
  volatile uint32_t RDLSICR;
  volatile uint32_t OCENCLRR;
  volatile uint32_t OCRDYR;
  volatile uint32_t HSICFGR;
  volatile uint32_t CSICFGR;
  volatile uint32_t MCO1CFGR;
  volatile uint32_t MCO2CFGR;
  volatile uint32_t DBGCFGR;
  volatile uint32_t RCK12SELR;
  volatile uint32_t RCK3SELR;
  volatile uint32_t RCK4SELR;
  volatile uint32_t PLL1CR;
  volatile uint32_t PLL1CFGR1;
  volatile uint32_t PLL1CFGR2;
  volatile uint32_t PLL1FRACR;
  volatile uint32_t PLL2CR;
  volatile uint32_t PLL2CFGR2;
  volatile uint32_t PLL2FRACR;
  volatile uint32_t PLL2CSGR;
  volatile uint32_t PLL3CR;
  volatile uint32_t PLL3CFGR2;
  volatile uint32_t PLL3CSGR;
  volatile uint32_t PLL4CR;
  volatile uint32_t PLL4CFGR1;
  volatile uint32_t PLL4CFGR2;
  volatile uint32_t PLL4FRACR;
  volatile uint32_t PLL4CSGR;
  volatile uint32_t ASSCKSELR;
  volatile uint32_t MSSCKSELR;
  volatile uint32_t CPERCKSELR;
  volatile uint32_t RTCDIVR;
  volatile uint32_t MPCKDIVR;
  volatile uint32_t MLAHBDIVR;
  volatile uint32_t APB1DIVR;
  volatile uint32_t APB2DIVR;
  volatile uint32_t APB3DIVR;
  volatile uint32_t APB4DIVR;
  volatile uint32_t APB5DIVR;
  volatile uint32_t APB6DIVR;
  volatile uint32_t TIMG1PRER;
  volatile uint32_t TIMG2PRER;
  volatile uint32_t TIMG3PRER;
  volatile uint32_t DDRITFCR;
  volatile uint32_t I2C12CKSELR;
  volatile uint32_t SPI2S1CKSELR;
  volatile uint32_t SPI2S23CKSELR;
  volatile uint32_t SPI45CKSELR;
  volatile uint32_t UART12CKSELR;
  volatile uint32_t UART35CKSELR;
  volatile uint32_t UART4CKSELR;
  volatile uint32_t UART6CKSELR;
  volatile uint32_t UART78CKSELR;
  volatile uint32_t LPTIM1CKSELR;
  volatile uint32_t LPTIM23CKSELR;
  volatile uint32_t LPTIM45CKSELR;
  volatile uint32_t FDCANCKSELR;
  volatile uint32_t SPDIFCKSELR;
  volatile uint32_t ADC12CKSELR;
  volatile uint32_t SDMMC12CKSELR;
  volatile uint32_t ETH12CKSELR;
  volatile uint32_t QSPICKSELR;
  volatile uint32_t FMCCKSELR;
  volatile uint32_t RNG1CKSELR;
  volatile uint32_t APB1RSTSETR;
  volatile uint32_t APB1RSTCLRR;
  volatile uint32_t APB2RSTSETR;
  volatile uint32_t APB2RSTCLRR;
  volatile uint32_t APB3RSTSETR;
  volatile uint32_t APB3RSTCLRR;
  volatile uint32_t APB4RSTSETR;
  volatile uint32_t APB4RSTCLRR;
  volatile uint32_t APB5RSTCLRR;
  volatile uint32_t APB6RSTCLRR;
  volatile uint32_t AHB2RSTSETR;
  volatile uint32_t AHB2RSTCLRR;
  volatile uint32_t AHB4RSTSETR;
  volatile uint32_t AHB4RSTCLRR;
  volatile uint32_t AHB5RSTSETR;
  volatile uint32_t AHB5RSTCLRR;
  volatile uint32_t AHB6RSTSETR;
  volatile uint32_t AHB6RSTCLRR;
  volatile uint32_t MP_APB1ENSETR;
  volatile uint32_t MP_APB1ENCLRR;
  volatile uint32_t MP_APB2ENSETR;
  volatile uint32_t MP_APB2ENCLRR;
  volatile uint32_t MP_APB3ENSETR;
  volatile uint32_t MP_APB3ENCLRR;
  volatile uint32_t MP_S_APB3ENSETR;
  volatile uint32_t MP_S_APB3ENCLRR;
  volatile uint32_t MP_NS_APB3ENCLRR;
  volatile uint32_t MP_APB4ENSETR;
  volatile uint32_t MP_APB4ENCLRR;
  volatile uint32_t MP_S_APB4ENSETR;
  volatile uint32_t MP_S_APB4ENCLRR;
  volatile uint32_t MP_NS_APB4ENSETR;
  volatile uint32_t MP_NS_APB4ENCLRR;
  volatile uint32_t MP_APB5ENSETR;
  volatile uint32_t MP_APB5ENCLRR;
  volatile uint32_t MP_APB6ENSETR;
  volatile uint32_t MP_APB6ENCLRR;
  volatile uint32_t MP_AHB2ENSETR;
  volatile uint32_t MP_AHB2ENCLRR;
  volatile uint32_t MP_S_AHB4ENSETR;
  volatile uint32_t MP_S_AHB4ENCLRR;
  volatile uint32_t MP_NS_AHB4ENSETR;
  volatile uint32_t MP_NS_AHB4ENCLRR;
  volatile uint32_t MP_AHB5ENSETR;
  volatile uint32_t MP_AHB5ENCLRR;
  volatile uint32_t MP_AHB6ENSETR;
  volatile uint32_t MP_S_AHB6ENSETR;
  volatile uint32_t MP_S_AHB6ENCLRR;
  volatile uint32_t MP_NS_AHB6ENSETR;
  volatile uint32_t MP_NS_AHB6ENCLRR;
  volatile uint32_t MP_APB1LPENSETR;
  volatile uint32_t MP_APB1LPENCLRR;
  volatile uint32_t MP_APB2LPENSETR;
  volatile uint32_t MP_APB2LPENCLRR;
  volatile uint32_t MP_APB3LPENSETR;
  volatile uint32_t MP_APB3LPENCLRR;
  volatile uint32_t MP_S_APB3LPENSETR;
  volatile uint32_t MP_S_APB3LPENCLRR;
  volatile uint32_t MP_NS_APB3LPENSETR;
  volatile uint32_t MP_NS_APB3LPENCLRR;
  volatile uint32_t MP_APB4LPENSETR;
  volatile uint32_t MP_APB4LPENCLRR;
  volatile uint32_t MP_S_APB4LPENSETR;
  volatile uint32_t MP_S_APB4LPENCLRR;
  volatile uint32_t MP_NS_APB4LPENSETR;
  volatile uint32_t MP_NS_APB4LPENCLRR;
  volatile uint32_t MP_APB5LPENCLRR;
  volatile uint32_t MP_APB6LPENSETR;
  volatile uint32_t MP_APB6LPENCLRR;
  volatile uint32_t MP_AHB2LPENSETR;
  volatile uint32_t MP_AHB2LPENCLRR;
  volatile uint32_t MP_S_AHB4LPENSETR;
  volatile uint32_t MP_S_AHB4LPENCLRR;
  volatile uint32_t MP_NS_AHB4LPENSETR;
  volatile uint32_t MP_NS_AHB4LPENCLRR;
  volatile uint32_t MP_AHB5LPENSETR;
  volatile uint32_t MP_AHB5LPENCLRR;
  volatile uint32_t MP_AHB6LPENSETR;
  volatile uint32_t MP_AHB6LPENCLRR;
  volatile uint32_t MP_S_AHB6LPENSETR;
  volatile uint32_t MP_S_AHB6LPENCLRR;
  volatile uint32_t MP_NS_AHB6LPENSETR;
  volatile uint32_t MP_NS_AHB6LPENCLRR;
  volatile uint32_t MP_S_AXIMLPENSETR;
  volatile uint32_t MP_S_AXIMLPENCLRR;
  volatile uint32_t MP_NS_AXIMLPENSETR;
  volatile uint32_t MP_MLAHBLPENSETR;
  volatile uint32_t MP_MLAHBLPENCLRR;
  volatile uint32_t APB3SECSR;
  volatile uint32_t APB4SECSR;
  volatile uint32_t APB5SECSR;
  volatile uint32_t APB6SECSR;
  volatile uint32_t AHB2SECSR;
  volatile uint32_t AHB5SECSR;
  volatile uint32_t AHB6SECSR;
  volatile uint32_t VERR;
  volatile uint32_t IDR;
  volatile uint32_t SIDR;
};

#define RCC ((struct rcc *)0x50000000U)

static inline enum ERROR rcc_enable_gpio(struct rcc *rcc, enum GPIO_BANK bank) {
  uint8_t pin = bank;

  if (pin < GPIO_BANK_A || pin > GPIO_BANK_H) {
    return ERROR_INVALID_INPUT;
  }

  rcc->MP_NS_AHB4ENSETR = (1U << pin);

  return ERROR_NONE;
}

static inline enum ERROR rcc_disable_gpio(struct rcc *rcc,
                                          enum GPIO_BANK bank) {
  uint8_t pin = bank;

  if (pin < GPIO_BANK_A || pin > GPIO_BANK_H) {
    return ERROR_INVALID_INPUT;
  }

  rcc->MP_NS_AHB4ENCLRR = (1U << pin);

  return ERROR_NONE;
}

enum RCC_UART_SRC {
  RCC_UART_SRC_PCLK6 = 0x0,
  RCC_UART_SRC_PLL3 = 0x1,
  RCC_UART_SRC_HSI = 0x2,
  RCC_UART_SRC_CSI = 0x3,
  RCC_UART_SRC_PLL4 = 0x4,
  RCC_UART_SRC_HSE = 0x5,
};

static inline enum ERROR rcc_set_clock_src_usart12(struct rcc *rcc,
                                                   enum RCC_UART_SRC src,
                                                   bool is_usart1) {
  if (src < RCC_UART_SRC_PCLK6 || src > RCC_UART_SRC_HSE) {
    return ERROR_INVALID_INPUT;
  }

  uint8_t shift;
  if (is_usart1) {
    shift = 0;
  } else {
    shift = 3;
  }

  rcc->UART12CKSELR = ((uint32_t)src << shift);

  return ERROR_NONE;
}

static inline void rcc_enable_usart12(struct rcc *rcc, bool is_usart1) {
  uint8_t shift;
  if (is_usart1) {
    shift = 0;
  } else {
    shift = 1;
  }

  rcc->MP_APB6ENSETR = (1U << shift);
}

static inline void rcc_disable_usart12(struct rcc *rcc, bool is_usart1) {
  uint8_t shift;
  if (is_usart1) {
    shift = 0;
  } else {
    shift = 1;
  }

  rcc->MP_APB6ENCLRR = (1U << shift);
}

#endif
