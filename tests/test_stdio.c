#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mystdio.h"
#include "unity.h"

size_t gbuffer_len = 0;
char *gbuffer = NULL;

size_t mystrlen(const char *str);
int myputchar(int ch);

void setUp(void) {
  gbuffer = malloc(2048);
  memset(gbuffer, 0, 2048);
  gbuffer_len = 0;
}

void tearDown() { free(gbuffer); }

void test_myprintf_simple_string() {
  myprintf("TEST");
  TEST_ASSERT_EQUAL_STRING_LEN("TEST", gbuffer, strlen("TEST"));
}

void test_myprintf_char() {
  myprintf("C:%c", 'a');
  TEST_ASSERT_EQUAL_STRING_LEN("C:a", gbuffer, strlen("C:a"));
}

void test_myprintf_str() {
  myprintf("String : %s", "TEST");
  TEST_ASSERT_EQUAL_STRING_LEN("String : TEST", gbuffer, strlen("String : TEST"));
}

void test_myprintf_number() {
  myprintf("D:%d", 1);
  TEST_ASSERT_EQUAL_STRING_LEN("D:1", gbuffer, strlen("D:1"));

  gbuffer_len = 0;
  myprintf("D:%d", 10);
  TEST_ASSERT_EQUAL_STRING_LEN("D:10", gbuffer, strlen("D:10"));

  gbuffer_len = 0;
  myprintf("Digits : %d", 999);
  TEST_ASSERT_EQUAL_STRING_LEN("Digits : 999", gbuffer, strlen("Digits : 999"));
}

void test_myprintf_hex() {
  myprintf("X:%x", 0x1);
  TEST_ASSERT_EQUAL_STRING_LEN("X:1", gbuffer, strlen("X:1"));

  gbuffer_len = 0;
  myprintf("X:%x", 0x10);
  TEST_ASSERT_EQUAL_STRING_LEN("X:10", gbuffer, strlen("X:10"));

  gbuffer_len = 0;
  myprintf("Hex : %x", 0xFFF);
  TEST_ASSERT_EQUAL_STRING_LEN("Hex : FFF", gbuffer, strlen("Hex : 999"));
}

size_t mystrlen(const char *str) {
  return strlen(str);
};

int myputchar(int ch) {
  gbuffer[gbuffer_len++] = ch;
  return ch;
};

