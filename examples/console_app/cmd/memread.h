#ifndef MEMREAD_H
#define MEMREAD_H

#include <stdint.h>

#include "common.h"
#include "stdlib.h"
#include "string.h"

static inline bool __cmd_memread_is_valid_hex(char *str);

static inline int cmd_memread(int argc, char *argv[]) {
  char *(*func[])(uint32_t value, char *str, uint32_t count) = {number_to_str};
  char *flags[sizeof(func) / sizeof(void *)] = {"-d"};
  bool is_flag[sizeof(func) / sizeof(void *)] = {false};
  char *digits = NULL;

  if (argc < 1) {
    return ERROR_INVALID_INPUT;
  }

  { // Populate data
    for (uint32_t i = 1; i < argc; i++) {
      if (strlen(argv[i]) > 2 && argv[i][0] == '0' && argv[i][1] == 'x') {
        digits = argv[i];
      };

      for (uint32_t flag = 0; flag < sizeof(flags) / sizeof(void *); flag++) {
        if (strlen(argv[i]) > 1 && argv[i][0] == flags[flag][0] &&
            argv[i][1] == flags[flag][1]) {
          is_flag[flag] = true;
        };
      }
    }
  }

  { // Validate data
    if (!__cmd_memread_is_valid_hex(digits)) {
      return ERROR_INVALID_INPUT;
    }
  }

  char *result = NULL;
  uint32_t addr_val;
  uint32_t mem_val;
  char buffer[255];

  { // Read memory
    addr_val = hex_to_number(digits, strlen(digits));
    if (addr_val == -1) {
      return ERROR_INVALID_INPUT;
    }

    mem_val = *((uint32_t *)addr_val);

    for (uint32_t flag = 0; flag < sizeof(flags) / sizeof(void *); flag++) {
      if (is_flag[flag]) {
        result = func[flag](mem_val, buffer, sizeof(buffer) / sizeof(char));
        break;
      }
    }

    if (!result) {
      result = hex_to_str(mem_val, buffer, sizeof(buffer) / sizeof(char));
    }
  }

  { // Print results
    print("*(uint32_t *)");
    print(digits);
    print(" = ");
    puts(result);
  }

  return 0;
};

static inline bool __cmd_memread_is_valid_hex(char *str) {
  uint32_t len = strlen(str);
  if (!str || len <= 2) {
    puts("You have to provide a memory address and it's value.");
    puts("For example: memread 0xC0300000");
    return false;
  }

  for (uint32_t i = 2; i < len - 1; i++) {
    if (islower(str[i])) {
      puts("You have to use uppercase letters in memory address.");
      puts("For example: memread 0xC0300000");
      return false;
    }

    if (!isdigit(str[i]) && (str[i] < 'A' || str[i] > 'F')) {
      puts("You have to use uppercase alphanumeric letters in memory "
           "address.");
      puts("For example: memread 0xC0300000");
      return false;
    }
  }

  return true;
}

#endif
