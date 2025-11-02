#include <stdint.h>
#include <stdbool.h>

#include "unity.h"

void cli_prepare_args(char *str, uint32_t count, int *argc, char *argv[255]);

void test_cli() {
  char args[] = "console_app add_sth -d";
  char *argv[255];
  int argc = 0;

  cli_prepare_args(args, sizeof(args), &argc, argv);
  TEST_ASSERT_EQUAL(argc, 3);
  TEST_ASSERT_EQUAL_STRING("console_app", argv[0]);
  TEST_ASSERT_EQUAL_STRING("add_sth", argv[1]);
  TEST_ASSERT_EQUAL_STRING("-d", argv[2]);
};

