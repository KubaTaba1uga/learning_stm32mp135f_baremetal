#ifndef MEMWRITE_H
#define MEMWRITE_H

#include <stdint.h>

#include "stdlib.h"
#include "string.h"

static inline bool __cmd_memwrite_is_valid_hex(char *str);

static inline int cmd_memwrite(int argc, char *argv[]) {
  char *value = NULL;
  char *addr = NULL;

  { // Populate data
    for (uint32_t i = 0; i < argc; i++) {
      if (strlen(argv[i]) >= 2 && argv[i][0] == '0' && argv[i][1] == 'x') {
        if (!addr) {
          addr = argv[i];
        } else if (!value) {
          value = argv[i];
        }

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
    mem_addr = hex_to_number(addr, strlen(addr));
    mem_value = hex_to_number(value, strlen(value));
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

  puts(str);
  
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
