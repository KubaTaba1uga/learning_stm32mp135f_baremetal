#ifndef MEMWRITE_H
#define MEMWRITE_H

#include <stdint.h>

#include "stdlib.h"
#include "string.h"

static inline bool __cmd_memwrite_is_valid_hex(char *str);

static inline int cmd_memwrite(char *str, uint32_t count) {
  bool is_space = false;
  char *value = NULL;
  char *addr = NULL;

  { // Populate data
    for (uint32_t i = 0; i < count; i++) {
      if (!addr && i >= 2 && str[i - 2] == '0' && str[i - 1] == 'x') {
        addr = str + i;
      } else if (addr && str[i] == ' ') {
        is_space = true;
        str[i] = 0;
      } else if (addr && !value && is_space && isdigit(str[i])) {
        value = str + i;
      } else if (str[i] == '\r' || str[i] == '\n') {
        str[i] = 0;
      }
    }
  }

  { // Validate data
    if (!__cmd_memwrite_is_valid_hex(addr) ||
        !__cmd_memwrite_is_valid_hex(value)) {
      return ERROR_INVALID_INPUT;
    }
  }

  uint32_t mem_addr;
  uint32_t mem_value;

  { // Convert numbers
    mem_addr = hex_to_number(addr, count);
    mem_value = hex_to_number(value, count);
  }

  { // Write value to memory
    *((uint32_t *)mem_addr) = mem_value;
  }

  { // Print results
    print("*(uint32_t *)");
    print(addr);
    print(" = ");
    puts(value);
  }

  return 0;
};

static inline bool __cmd_memwrite_is_valid_hex(char *str) {
  if (!str || strlen(str) <= 2) {
    puts("You have to provide a memory address and it's value.");
    puts("For example: memwrite 0xC0300000 0x20");
    return false;
  }

  for (char *digits_cp = str + 2; *digits_cp != 0; digits_cp++) {
    if (islower(*digits_cp)) {
      puts("You have to use uppercase letters in memory address.");
      puts("For example: memwrite 0xC0300000 0x20");
      return false;
    }

    if (!isdigit(*digits_cp) && (*digits_cp < 'A' || *digits_cp > 'F')) {
      puts("You have to use uppercase alphanumeric letters in memory "
           "address.");
      puts("For example: memwrite 0xC0300000 0x20");
      return false;
    }
  }

  return true;
}

#endif
