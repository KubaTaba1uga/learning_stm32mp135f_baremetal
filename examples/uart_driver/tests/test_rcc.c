#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include "unity.h"

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
  volatile uint8_t _reserved0[212];  // Checked
  volatile uint32_t MP_CIER;
  volatile uint32_t MP_CIFR;
  volatile uint8_t _reserved1[504];   // Checked
  volatile uint32_t BDCR;
  volatile uint32_t RDLSICR;
  volatile uint8_t _reserved2[24];  // Checked
  volatile uint32_t OCENSETR;  
  volatile uint32_t OCENCLRR;
  volatile uint32_t OCRDYR;
  volatile uint8_t _reserved3[20];  // Checked
  volatile uint32_t HSICFGR;
  volatile uint32_t CSICFGR;
  volatile uint8_t _reserved4[24]; // Checked
  volatile uint32_t MCO1CFGR;
  volatile uint32_t MCO2CFGR;
  volatile uint32_t DBGCFGR;
  volatile uint8_t _reserved5[20];      // Checked
  volatile uint32_t RCK12SELR;
  volatile uint32_t RCK3SELR;
  volatile uint32_t RCK4SELR;
  volatile uint8_t _reserved6[20];        // Checked
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
  volatile uint8_t _reserved11[13];  // Checked
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




void test_rcc_regs_mapping() {
  printf("offsetof MP_SREQSETR: %lx\n", offsetof(struct rcc, MP_SREQSETR));
  TEST_ASSERT_EQUAL_HEX(0x100,  offsetof(struct rcc, MP_SREQSETR));
  
  printf("offsetof MP_CIER: %lx\n", offsetof(struct rcc, MP_CIER));
  TEST_ASSERT_EQUAL_HEX(0x200, offsetof(struct rcc, MP_CIER));

  printf("offsetof BDCR: %lx\n", offsetof(struct rcc, BDCR));
  TEST_ASSERT_EQUAL_HEX(0x400, offsetof(struct rcc, BDCR));

  printf("offsetof OCENSETR: %lx\n", offsetof(struct rcc, OCENSETR));
  TEST_ASSERT_EQUAL_HEX(0x420, offsetof(struct rcc, OCENSETR));

  printf("offsetof HSICFGR: %lx\n", offsetof(struct rcc, HSICFGR));
  TEST_ASSERT_EQUAL_HEX(0x440, offsetof(struct rcc, HSICFGR));

  printf("offsetof MCO1CFGR: %lx\n", offsetof(struct rcc, MCO1CFGR));
  TEST_ASSERT_EQUAL_HEX(0x460, offsetof(struct rcc, MCO1CFGR));
  
  printf("offsetof RCK12SELR: %lx\n", offsetof(struct rcc, RCK12SELR));
  TEST_ASSERT_EQUAL_HEX(0x480, offsetof(struct rcc, RCK12SELR));

  printf("offsetof PLL1CR: %lx\n", offsetof(struct rcc, PLL1CR));
  TEST_ASSERT_EQUAL_HEX(0x4A0, offsetof(struct rcc, PLL1CR));
  
  printf("offsetof PLL2CR: %lx\n", offsetof(struct rcc, PLL2CR));
  TEST_ASSERT_EQUAL_HEX(0x4D0, offsetof(struct rcc, PLL2CR));

  printf("offsetof PLL3CR: %lx\n", offsetof(struct rcc, PLL3CR));
  TEST_ASSERT_EQUAL_HEX(0x500, offsetof(struct rcc, PLL3CR));

  printf("offsetof PLL4CR: %lx\n", offsetof(struct rcc, PLL4CR));
  TEST_ASSERT_EQUAL_HEX(0x520, offsetof(struct rcc, PLL4CR));
  
  printf("offsetof MPCKSELR: %lx\n", offsetof(struct rcc, MPCKSELR));
  TEST_ASSERT_EQUAL_HEX(0x540, offsetof(struct rcc, MPCKSELR));
  
  printf("offsetof RTCDIVR: %lx\n", offsetof(struct rcc, RTCDIVR));
  TEST_ASSERT_EQUAL_HEX(0x560, offsetof(struct rcc, RTCDIVR));

  printf("offsetof TIMG1PRER: %lx\n", offsetof(struct rcc, TIMG1PRER));
  TEST_ASSERT_EQUAL_HEX(0x5A0, offsetof(struct rcc, TIMG1PRER));
  
  printf("offsetof DDRITFCR: %lx\n", offsetof(struct rcc, DDRITFCR));
  TEST_ASSERT_EQUAL_HEX(0x5C0, offsetof(struct rcc, DDRITFCR));

  printf("offsetof I2C12CKSELR: %lx\n", offsetof(struct rcc, I2C12CKSELR));
  TEST_ASSERT_EQUAL_HEX(0x600, offsetof(struct rcc, I2C12CKSELR));

  printf("offsetof APB1RSTSETR: %lx\n", offsetof(struct rcc, APB1RSTSETR));
  TEST_ASSERT_EQUAL_HEX(0x6A0, offsetof(struct rcc, APB1RSTSETR));

  printf("offsetof AHB4RSTSETR: %lx\n", offsetof(struct rcc, AHB4RSTSETR));
  TEST_ASSERT_EQUAL_HEX(0x6E0, offsetof(struct rcc, AHB4RSTSETR));

  printf("offsetof MP_APB1ENSETR: %lx\n", offsetof(struct rcc, MP_APB1ENSETR));
  TEST_ASSERT_EQUAL_HEX(0x700, offsetof(struct rcc, MP_APB1ENSETR));
  
  printf("offsetof MP_S_AHB4ENSETR: %lx\n", offsetof(struct rcc, MP_S_AHB4ENSETR));
  TEST_ASSERT_EQUAL_HEX(0x768, offsetof(struct rcc, MP_S_AHB4ENSETR));
  
  printf("offsetof MP_APB1LPENSETR: %lx\n", offsetof(struct rcc, MP_APB1LPENSETR));
  TEST_ASSERT_EQUAL_HEX(0x800, offsetof(struct rcc, MP_APB1LPENSETR));

  printf("offsetof MP_S_AHB4LPENSETR: %lx\n", offsetof(struct rcc, MP_S_AHB4LPENSETR));
  TEST_ASSERT_EQUAL_HEX(0x868, offsetof(struct rcc, MP_S_AHB4LPENSETR));
  
  printf("offsetof APB3SECSR: %lx\n", offsetof(struct rcc, APB3SECSR));
  TEST_ASSERT_EQUAL_HEX(0x8C0, offsetof(struct rcc, APB3SECSR));
  
  printf("offsetof AHB5SECSR: %lx\n", offsetof(struct rcc, AHB5SECSR));
  TEST_ASSERT_EQUAL_HEX(0x8D8, offsetof(struct rcc, AHB5SECSR));
  
  printf("offsetof VERR: %lx\n", offsetof(struct rcc, VERR));
  TEST_ASSERT_EQUAL_HEX(0xFF4, offsetof(struct rcc, VERR));
  
  printf("offsetof SIDR: %lx\n", offsetof(struct rcc, SIDR));
  TEST_ASSERT_EQUAL_HEX(0xFFC, offsetof(struct rcc, SIDR));
}


