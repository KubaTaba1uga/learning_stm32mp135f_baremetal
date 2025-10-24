#include "common.h"
#include "unity.h"


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
}
