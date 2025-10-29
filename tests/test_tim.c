#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "tim.h"
#include "unity.h"

void test_uart_regs_mapping() {
  printf("offsetof TIM_DIER: %lx\n", offsetof(struct tim, DIER));
  TEST_ASSERT_EQUAL_HEX(0x0C, offsetof(struct tim, DIER));

  printf("offsetof TIM_CNT: %lx\n", offsetof(struct tim, CNT));
  TEST_ASSERT_EQUAL_HEX(0x24, offsetof(struct tim, CNT));
}
