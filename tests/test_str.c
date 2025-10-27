#include <stdint.h>
#include <string.h>

#include "string.h"
#include "unity.h"


void mystrcpy(char *dst, const char *src) {
  while (*src != 0) {
    *dst = *src;
    dst++;
    src++;
  }

  *dst = *src;
}

void test_decimal_str() {
  char buffer[255];
  char *result = number_to_str(10, buffer, 255);

  TEST_ASSERT_EQUAL_STRING_LEN("10", result, 2);

  result = number_to_str(20, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("20", result, 2);
  result = number_to_str(299, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("299", result, 3);
  result = number_to_str(787878, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("787878", result, 6);

  mystrcpy(buffer, "10");
  uint32_t number = str_to_number(buffer, 255);
  TEST_ASSERT_EQUAL(10, number);

  mystrcpy(buffer, "20");
  number = str_to_number(buffer, 255);
  TEST_ASSERT_EQUAL(20, number);

  mystrcpy(buffer, "200");
  number = str_to_number(buffer, 255);
  TEST_ASSERT_EQUAL(200, number);
  mystrcpy(buffer, "999");
  number = str_to_number(buffer, 255);
  TEST_ASSERT_EQUAL(999, number);
}

void test_hex_str() {
  char buffer[255];

  char *result = hex_to_str(0x10, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("0x10", result, 2+2);

  result = hex_to_str(0x20, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("0x20", result, 2+2);

  result = hex_to_str(0x12, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("0x12", result, 2+2);

  result = hex_to_str(0x100000, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("0x100000", result, 2+5);

  result = hex_to_str(0xA, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("0xA", result, 2+1);

  result = hex_to_str(0xBB, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("0xBB", result, 2+2);

  result = hex_to_str(0xFFF, buffer, 255);
  TEST_ASSERT_EQUAL_STRING_LEN("0xFFF", result, 2+3);

  mystrcpy(buffer, "0x10");
  uint32_t number = hex_to_number(buffer, 255);
  TEST_ASSERT_EQUAL(0x10, number);

  mystrcpy(buffer, "0x20");
  number = hex_to_number(buffer, 255);
  TEST_ASSERT_EQUAL(0x20, number);

  mystrcpy(buffer, "0x200");
  number = hex_to_number(buffer, 255);
  TEST_ASSERT_EQUAL(0x200, number);

  mystrcpy(buffer, "0x999");
  number = hex_to_number(buffer, 255);
  TEST_ASSERT_EQUAL(0x999, number);

  mystrcpy(buffer, "0xAA");
  number = hex_to_number(buffer, 255);
  TEST_ASSERT_EQUAL(0xAA, number);

  mystrcpy(buffer, "0xFFF");
  number = hex_to_number(buffer, 255);
  TEST_ASSERT_EQUAL(0xFFF, number);
}
