#ifndef MEMREAD_H
#define MEMREAD_H

#include "stdlib.h"
#include <stdint.h>

static inline void _cmd_memread_dump_number(uint32_t number) {
  char buffer[255];  
  char *start = buffer + (sizeof(buffer) / sizeof(char)) - 1;

  *start = 0;
  start--;
  for (uint32_t i = 1; start != buffer; i *= 10) {
    uint32_t div = number % i;
    *start = div + 30;
    start--;
  }

  puts(start);
}

static inline int cmd_memread(char *str, uint32_t count) {
  char *addr_str_start = NULL;
  char *addr_str_end = NULL;
  uint32_t addr_val = 0;

  _cmd_memread_dump_number(10);
  puts(str);

  for (uint32_t i = 0; i < count; i++) {
      puts("checking Number...");    
    if (str[i] >= 30 && str[i] <= 39) {
      puts("Number start");
      if (!addr_str_start) {
        
        addr_str_start = str + i;
      }
    }

    if (addr_str_start) {
      puts("Number end");      
      addr_str_end = str + i;
      break;
    }
  }

  if (!addr_str_start || !addr_str_end) {
    puts("No number");
    return -1;
  }

  for (uint32_t i = 1; addr_str_start != addr_str_end--; i *= 10) {
    uint32_t val = *addr_str_end - 30;
    if (i > 1) {
      addr_val += val * i;
    } else {
      addr_val += val;
    }
  }

  print("Your number is: ");
  _cmd_memread_dump_number(addr_val);
  puts("\r\n");

  return 0;
};

#endif
