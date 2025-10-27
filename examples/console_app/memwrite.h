#ifndef MEMWRITE_H
#define MEMWRITE_H

#include <stdint.h>

#include "stdlib.h"
#include "string.h"

static inline int cmd_memwrite(char *str, uint32_t count) {
  bool is_space = false;
  char *value = NULL;
  char *addr = NULL;

  for (uint32_t i = 0; i < count; i++) {
    if (!addr && isdigit(str[i])) {
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

  if (!addr || !value) {
    puts("You have to provide a memory address and it's value.");
    puts("For example: memwrite 0xC0300000 0x20");
    return ERROR_INVALID_INPUT;
  }

  uint32_t mem_addr;
  uint32_t mem_value;

  mem_addr = hex_to_number(addr, count);
  mem_value = hex_to_number(value, count);

  *((uint32_t *)mem_addr) = mem_value;

  print("*(uint32_t *)");
  print(addr);
  print(" = ");
  puts(value);

  return 0;
};

#endif
