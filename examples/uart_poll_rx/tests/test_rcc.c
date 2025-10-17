#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "rcc.h"
#include "unity.h"

void test_rcc_regs_mapping() {
  printf("offsetof MP_SREQSETR: %lx\n", offsetof(struct rcc, MP_SREQSETR));
  TEST_ASSERT_EQUAL_HEX(0x100, offsetof(struct rcc, MP_SREQSETR));

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

  printf("offsetof MP_S_AHB4ENSETR: %lx\n",
         offsetof(struct rcc, MP_S_AHB4ENSETR));
  TEST_ASSERT_EQUAL_HEX(0x768, offsetof(struct rcc, MP_S_AHB4ENSETR));

  printf("offsetof MP_APB1LPENSETR: %lx\n",
         offsetof(struct rcc, MP_APB1LPENSETR));
  TEST_ASSERT_EQUAL_HEX(0x800, offsetof(struct rcc, MP_APB1LPENSETR));

  printf("offsetof MP_S_AHB4LPENSETR: %lx\n",
         offsetof(struct rcc, MP_S_AHB4LPENSETR));
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
