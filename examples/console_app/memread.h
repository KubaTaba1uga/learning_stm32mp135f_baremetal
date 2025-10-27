/*
  TO-DO:
     1. Add hexadecimal input.
*/

#ifndef MEMREAD_H
#define MEMREAD_H

#include "string.h"
#include "stdlib.h"
#include <stdint.h>

static inline int cmd_memread(char *str, uint32_t count) {
  char *digits = NULL;
  bool is_hex = false;
  for (uint32_t i = 0; i < count; i++) {
    if (isdigit(str[i]) && !digits) {
      digits = str + i;
    }

    if (i >= 1 && str[i] == 'x' && str[i - 1] == '-') {
      is_hex = true;
    }
  }

  if (!digits) {
    puts("You have to provide a memory address.");
    return ERROR_INVALID_INPUT;
  }

  uint32_t addr_val;
  char buffer[255];
  char *result;

  if (!is_hex) {
    addr_val = str_to_number(str, count);
  } else {
    addr_val = hex_to_number(str, count);
  }

  uint32_t mem_val = *((uint32_t *)addr_val);

  print("Your number is: ");

  if (!is_hex) {
    result = number_to_str(mem_val, buffer, sizeof(buffer));
  } else {
    result = hex_to_str(mem_val, buffer, sizeof(buffer));
  }

  print(result);
  puts("\r\n");

  return 0;
};

#endif
