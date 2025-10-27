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
    if (isdigit(str[i]) && !digits) {
      digits = str + i;
    }

    if (str[i]=='\r'||str[i]=='\n') {
      str[i] = 0;
    }

    for (uint32_t flag = 0; flag < sizeof(flags) / sizeof(void *); flag++) {
      if (i >= 1 && str[i] == flags[flag][1] && str[i - 1] == flags[flag][0]) {
        is_flag[flag] = true;
      }
    }
  }

  if (!digits) {
    puts("You have to provide a memory address.");
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
  print(result);
  puts("\r\n");

  return 0;
};

#endif
