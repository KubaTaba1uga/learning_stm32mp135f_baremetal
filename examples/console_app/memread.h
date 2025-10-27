#ifndef MEMREAD_H
#define MEMREAD_H

#include "stdlib.h"
#include "string.h"
#include <stdint.h>

static inline int cmd_memread(char *str, uint32_t count) {
  char *(*func[])(uint32_t value, char *str, uint32_t count) = {number_to_str};
  char *flags[sizeof(func) / sizeof(void *)] = {"-d"};
  bool is_flag[sizeof(func) / sizeof(void *)] = {false};
  char *digits = NULL;

  for (uint32_t i = 0; i < count; i++) {
    if (i >= 2 && str[i - 2] == '0' && str[i - 1] == 'x') {
      digits = str + i - 2;
    }

    if (str[i] == '\r' || str[i] == '\n') {
      str[i] = 0;
    }

    for (uint32_t flag = 0; flag < sizeof(flags) / sizeof(void *); flag++) {
      if (i >= 1 && str[i] == flags[flag][1] && str[i - 1] == flags[flag][0]) {
        is_flag[flag] = true;
      }
    }
  }

  // Detect lowercase letters
  /* for (char *digits_cp = digits; *digits_cp != 0; digits_cp++) { */
  /*   if (*digits_cp >= 97 && *digits_cp <= 122) { */
  /*     puts("You have to use uppercase letters in memory address."); */
  /*     puts("For example: memread 0xC0300000"); */
  /*     return ERROR_INVALID_INPUT; */
  /*   } */
  /* } */

  if (!digits) {
    puts("You have to provide a memory address.");
    puts("For example: memread 0xC0300000");
    return ERROR_INVALID_INPUT;
  }

  char *result = NULL;
  uint32_t addr_val;
  char buffer[255];

  addr_val = hex_to_number(str, count);

  uint32_t mem_val = *((uint32_t *)addr_val);

  for (uint32_t flag = 0; flag < sizeof(flags) / sizeof(void *); flag++) {
    if (is_flag[flag]) {
      result = func[flag](mem_val, buffer, sizeof(buffer) / sizeof(char));
      break;
    }
  }

  if (!result) {
    result = hex_to_str(mem_val, buffer, sizeof(buffer) / sizeof(char));
  }

  print("*(uint32_t *)");
  print(digits);
  print(" = ");
  puts(result);

  return 0;
};

#endif
