#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "uart.h"
#include "unity.h"

void test_uart_regs_mapping() {
  printf("offsetof USART_PRESC: %lx\n", offsetof(struct uart, PRESC));
  TEST_ASSERT_EQUAL_HEX(0x2C, offsetof(struct uart, PRESC));

  printf("offsetof SIDR: %lx\n", offsetof(struct uart, SIDR));
  TEST_ASSERT_EQUAL_HEX(0x3FC, offsetof(struct uart, SIDR));
}
