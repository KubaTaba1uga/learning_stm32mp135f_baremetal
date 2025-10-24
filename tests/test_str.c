#include "common.h"
#include "unity.h"
#include <stdint.h>

void mystrcpy(char *dst, const char *src) {
  while (*src) {
    *dst = *src;
    dst++;
    src++;
  }
}

void test_str() {
  char buffer[255];
  char *result = strdump_number(10, buffer, 255);

  TEST_ASSERT_EQUAL_STRING_LEN("10", result, 2);

  result = strdump_number(20, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("20", result, 2);
  result = strdump_number(299, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("299", result, 3);
  result = strdump_number(787878, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("787878", result, 6);

  mystrcpy(buffer, "10");
  uint32_t number = numdump_str(buffer, 255);
  TEST_ASSERT_EQUAL(10, number);

  mystrcpy(buffer, "20");
   number = numdump_str(buffer, 255);
  TEST_ASSERT_EQUAL(20,number);

  mystrcpy(buffer, "200");
   number = numdump_str(buffer, 255);
  TEST_ASSERT_EQUAL(200,number);  
  mystrcpy(buffer, "999");
   number = numdump_str(buffer, 255);
  TEST_ASSERT_EQUAL(999,number);  
  
}
