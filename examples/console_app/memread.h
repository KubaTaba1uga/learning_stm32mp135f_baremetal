#ifndef MEMREAD_H
#define MEMREAD_H

#include <stdint.h>

#include "stdlib.h"
#include "string.h"

static inline bool __cmd_memread_is_valid_hex(char *str);

static inline int cmd_memread(char *str, uint32_t count) {
  char *(*func[])(uint32_t value, char *str, uint32_t count) = {number_to_str};
  char *flags[sizeof(func) / sizeof(void *)] = {"-d"};
  bool is_flag[sizeof(func) / sizeof(void *)] = {false};
  char *digits = NULL;

  { // Populate data
    for (uint32_t i = 0; i < count; i++) {
      if (i >= 2 && str[i - 2] == '0' && str[i - 1] == 'x') {
        digits = str + i - 2;
      }

      if (str[i] == '\r' || str[i] == '\n') {
        str[i] = 0;
      }

      for (uint32_t flag = 0; flag < sizeof(flags) / sizeof(void *); flag++) {
        if (i >= 1 && str[i] == flags[flag][1] &&
            str[i - 1] == flags[flag][0]) {
          is_flag[flag] = true;
        }
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
    addr_val = hex_to_number(str, count);
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
  if (!str || strlen(str)<=2) {
    puts("You have to provide a memory address and it's value.");
    puts("For example: memread 0xC0300000");
    return false;
  }

  for (char *digits_cp = str + 2; *digits_cp != 0; digits_cp++) {
    if (islower(*digits_cp)) {
      puts("You have to use uppercase letters in memory address.");
      puts("For example: memread 0xC0300000");
      return false;
    }

    if (!isdigit(*digits_cp) && (*digits_cp < 'A' || *digits_cp > 'F')) {
      puts("You have to use uppercase alphanumeric letters in memory "
           "address.");
      puts("For example: memread 0xC0300000");
      return false;
    }
  }

  return true;
}

#endif
