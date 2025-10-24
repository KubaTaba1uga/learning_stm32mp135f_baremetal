#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "unity.h"

static inline char * _cmd_memread_dump_number(uint32_t number,   char buffer[255]) {
  char *start = buffer + (255-1);

  *start = 0;
  start--;
  for (uint32_t i = 1; start != buffer; i *= 10) {
    uint32_t div = number % i;
    *start = div + 30;
    start--;
  }

  return start;
}

void test_str() {
  char buffer[255];
  _cmd_memread_dump_number(10, buffer);

  TEST_ASSERT_EQUAL_STR("10", buffer);
  
  }
