#ifndef RCC_H
#define RCC_H

#include <stdint.h>

#include "common.h"

struct rcc {
  volatile uint32_t SECCFGR;
  volatile uint8_t _reserved[252]; // Checked
  volatile uint32_t MP_SREQSETR;
  volatile uint32_t MP_SREQCLRR;
  volatile uint32_t MP_APRSTCR;
  volatile uint32_t MP_APRSTSR;
  volatile uint32_t PWRLPDLYCR;
  volatile uint32_t MP_GRSTCSETR;
  volatile uint32_t BR_RSTSCLRR;
  volatile uint32_t MP_RSTSSETR;
  volatile uint32_t MP_RSTSCLRR;
  volatile uint32_t MP_IWDGFZSETR;
  volatile uint32_t MP_IWDGFZCLRR;
  volatile uint8_t _reserved0[212]; // Checked
  volatile uint32_t MP_CIER;
  volatile uint32_t MP_CIFR;
  volatile uint8_t _reserved1[504]; // Checked
  volatile uint32_t BDCR;
  volatile uint32_t RDLSICR;
  volatile uint8_t _reserved2[24]; // Checked
  volatile uint32_t OCENSETR;
  volatile uint32_t OCENCLRR;
  volatile uint32_t OCRDYR;
  volatile uint8_t _reserved3[20]; // Checked
  volatile uint32_t HSICFGR;
  volatile uint32_t CSICFGR;
  volatile uint8_t _reserved4[24]; // Checked
  volatile uint32_t MCO1CFGR;
  volatile uint32_t MCO2CFGR;
  volatile uint32_t DBGCFGR;
  volatile uint8_t _reserved5[20]; // Checked
  volatile uint32_t RCK12SELR;
  volatile uint32_t RCK3SELR;
  volatile uint32_t RCK4SELR;
  volatile uint8_t _reserved6[20]; // Checked
  volatile uint32_t PLL1CR;
  volatile uint32_t PLL1CFGR1;
  volatile uint32_t PLL1CFGR2;
  volatile uint32_t PLL1FRACR;
  volatile uint32_t PLL1CSGR;
  volatile uint8_t _reserved7[28];
  volatile uint32_t PLL2CR;
  volatile uint32_t PLL2CFGR1;
  volatile uint32_t PLL2CFGR2;
  volatile uint32_t PLL2FRACR;
  volatile uint32_t PLL2CSGR;
  volatile uint8_t _reserved8[28];
  volatile uint32_t PLL3CR;
  volatile uint32_t PLL3CFGR1;
  volatile uint32_t PLL3CFGR2;
  volatile uint32_t PLL3FRACR;
  volatile uint32_t PLL3CSGR;
  volatile uint8_t _reserved9[12];
  volatile uint32_t PLL4CR;
  volatile uint32_t PLL4CFGR1;
  volatile uint32_t PLL4CFGR2;
  volatile uint32_t PLL4FRACR;
  volatile uint32_t PLL4CSGR;
  volatile uint8_t _reserved10[11]; // Checked
  volatile uint32_t MPCKSELR;
  volatile uint32_t ASSCKSELR;
  volatile uint32_t MSSCKSELR;
  volatile uint32_t CPERCKSELR;
  volatile uint8_t _reserved11[13]; // Checked
  volatile uint32_t RTCDIVR;
  volatile uint32_t MPCKDIVR;
  volatile uint32_t AXIDIVIR;
  volatile uint32_t MLAHBDIVR;
  volatile uint32_t APB1DIVR;
  volatile uint32_t APB2DIVR;
  volatile uint32_t APB3DIVR;
  volatile uint32_t APB4DIVR;
  volatile uint32_t APB5DIVR;
  volatile uint32_t APB6DIVR;
  volatile uint8_t _reserved12[21];
  volatile uint32_t TIMG1PRER;
  volatile uint32_t TIMG2PRER;
  volatile uint32_t TIMG3PRER;
  volatile uint8_t _reserved13[17];
  volatile uint32_t DDRITFCR;
  volatile uint8_t _reserved14[57];
  volatile uint32_t I2C12CKSELR;
  volatile uint32_t I2C345CKSELR;
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
  volatile uint32_t SAI1CKSELR;
  volatile uint32_t SAI2CKSELR;
  volatile uint32_t FDCANCKSELR;
  volatile uint32_t SPDIFCKSELR;
  volatile uint32_t ADC12CKSELR;
  volatile uint32_t SDMMC12CKSELR;
  volatile uint32_t ETH12CKSELR;
  volatile uint32_t USBCKSELR;
  volatile uint32_t QSPICKSELR;
  volatile uint32_t FMCCKSELR;
  volatile uint32_t RNG1CKSELR;
  volatile uint32_t STGENCKSELR;
  volatile uint32_t DCMIPPCKSELR;
  volatile uint32_t SAESSCKSELR;
  volatile uint8_t _reserved15[49];
  volatile uint32_t APB1RSTSETR;
  volatile uint32_t APB1RSTCLRR;
  volatile uint32_t APB2RSTSETR;
  volatile uint32_t APB2RSTCLRR;
  volatile uint32_t APB3RSTSETR;
  volatile uint32_t APB3RSTCLRR;
  volatile uint32_t APB4RSTSETR;
  volatile uint32_t APB4RSTCLRR;
  volatile uint32_t APB5RSTSETR;
  volatile uint32_t APB5RSTCLRR;
  volatile uint32_t APB6RSTSETR;
  volatile uint32_t APB6RSTCLRR;
  volatile uint32_t AHB2RSTSETR;
  volatile uint32_t AHB2RSTCLRR;
  volatile uint8_t _reserved16[5];
  volatile uint32_t AHB4RSTSETR;
  volatile uint32_t AHB4RSTCLRR;
  volatile uint32_t AHB5RSTSETR;
  volatile uint32_t AHB5RSTCLRR;
  volatile uint32_t AHB6RSTSETR;
  volatile uint32_t AHB6RSTCLRR;
  volatile uint8_t _reserved17[5];
  volatile uint32_t MP_APB1ENSETR;
  volatile uint32_t MP_APB1ENCLRR;
  volatile uint32_t MP_APB2ENSETR;
  volatile uint32_t MP_APB2ENCLRR;
  volatile uint32_t MP_APB3ENSETR;
  volatile uint32_t MP_APB3ENCLRR;
  volatile uint32_t MP_S_APB3ENSETR;
  volatile uint32_t MP_S_APB3ENCLRR;
  volatile uint32_t MP_NS_APB3ENSETR;
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
  volatile uint8_t _reserved18[13];
  volatile uint32_t MP_S_AHB4ENSETR;
  volatile uint32_t MP_S_AHB4ENCLRR;
  volatile uint32_t MP_NS_AHB4ENSETR;
  volatile uint32_t MP_NS_AHB4ENCLRR;
  volatile uint32_t MP_AHB5ENSETR;
  volatile uint32_t MP_AHB5ENCLRR;
  volatile uint32_t MP_AHB6ENSETR;
  volatile uint32_t MP_AHB6ENCLRR;
  volatile uint32_t MP_S_AHB6ENSETR;
  volatile uint32_t MP_S_AHB6ENCLRR;
  volatile uint32_t MP_NS_AHB6ENSETR;
  volatile uint32_t MP_NS_AHB6ENCLRR;
  volatile uint8_t _reserved19[101];
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
  volatile uint32_t MP_APB5LPENSETR;
  volatile uint32_t MP_APB5LPENCLRR;
  volatile uint32_t MP_APB6LPENSETR;
  volatile uint32_t MP_APB6LPENCLRR;
  volatile uint32_t MP_AHB2LPENSETR;
  volatile uint32_t MP_AHB2LPENCLRR;
  volatile uint8_t _reserved20[16];
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
  volatile uint32_t MP_NS_AXIMLPENCLRR;
  volatile uint32_t MP_MLAHBLPENSETR;
  volatile uint32_t MP_MLAHBLPENCLRR;
  volatile uint8_t _reserved21[13];
  volatile uint32_t APB3SECSR;
  volatile uint32_t APB4SECSR;
  volatile uint32_t APB5SECSR;
  volatile uint32_t APB6SECSR;
  volatile uint32_t AHB2SECSR;
  volatile uint32_t _reserved22;
  volatile uint32_t AHB5SECSR;
  volatile uint32_t AHB6SECSR;
  volatile uint32_t _reserved23[453];
  volatile uint32_t VERR;
  volatile uint32_t IDR;
  volatile uint32_t SIDR;
};

#define RCC ((struct rcc *)0x50000000U)

static inline void rcc_enable_gpio(struct rcc *rcc, uint8_t bank) {
  BIT_SET(rcc->MP_NS_AHB4ENSETR, bank); // Enable bank
}

static inline void rcc_disable_gpio(struct rcc *rcc, uint8_t bank) {
  BIT_CLEAR(rcc->MP_NS_AHB4ENCLRR, bank); // Disable bank
}

enum {
  RCC_UART_SRC_PCLK6 = 0x0,
  RCC_UART_SRC_PLL3 = 0x1,
  RCC_UART_SRC_HSI = 0x2,
  RCC_UART_SRC_CSI = 0x3,
  RCC_UART_SRC_PLL4 = 0x4,
  RCC_UART_SRC_HSE = 0x5,
};

static inline void rcc_set_src_usart12(struct rcc *rcc, uint8_t src,
                                       bool is_usart1) {
  uint8_t shift;
  if (is_usart1) {
    shift = 0;
  } else {
    shift = 3;
  }

  BITS_SET(rcc->UART12CKSELR, src, 3U, shift);
}

static inline void rcc_enable_usart12(struct rcc *rcc, bool is_usart1) {
  uint8_t shift;
  if (is_usart1) {
    shift = 0;
  } else {
    shift = 1;
  }

  BIT_SET(rcc->MP_APB6ENSETR, shift);
}

static inline void rcc_disable_usart12(struct rcc *rcc, bool is_usart1) {
  uint8_t shift;
  if (is_usart1) {
    shift = 0;
  } else {
    shift = 1;
  }

  BIT_SET(rcc->MP_APB6ENCLRR, shift);
}

static inline void rcc_enable_tim67(struct rcc *rcc, bool is_tim6) {
  uint8_t shift;
  if (is_tim6) {
    shift = 4;
  } else {
    shift = 5;
  }

  BIT_SET(rcc->MP_APB1ENSETR, shift);
}

static inline uint32_t rcc_get_mlahb_div(struct rcc *rcc) {
  switch (RCC->MLAHBDIVR & 0b1111) {
  case 0:
    return 0;
  case 0x1:
    return 2;
  case 0x2:
    return 4;
  case 0x3:
    return 8;
  case 0x4:
    return 16;
  case 0x5:
    return 32;
  case 0x6:
    return 64;
  case 0x7:
    return 128;
  case 0x8:
    return 256;
  default:
    return -1;
  }
}

static inline enum CLOCK rcc_get_mlahb_clk(struct rcc *rcc) {
  switch (RCC->MSSCKSELR & 0b11) {
  case 0:
    return CLOCK_HSI;
  case 0x1:
    return CLOCK_HSE;
  case 0x2:
    return CLOCK_CSI;
  case 0x3:
    return CLOCK_PLL3;
  default:
    return -1;
  }
}

static inline uint32_t rcc_get_hsi_frq(struct rcc *rcc) {
  switch (RCC->HSICFGR & 0b11) {
  case 0:
    return 64000000;
  case 0x1:
    return 32000000;
  case 0x2:
    return 16000000;
  case 0x3:
    return 8000000;
  default:
    return -1;
  }
}

static inline uint32_t rcc_get_apb1_div(struct rcc *rcc) {
  switch (rcc->APB1DIVR & 0b111) {
  case 0:
    return 0;
  case 0x1:
    return 2;
  case 0x2:
    return 4;
  case 0x3:
    return 8;
  case 0x4:
    return 16;
  default:
    return -1;
  }
}

#endif
