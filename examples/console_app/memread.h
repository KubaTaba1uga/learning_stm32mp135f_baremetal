#ifndef MEMREAD_H
#define MEMREAD_H

#include "common.h"
#include "stdlib.h"
#include <stdint.h>


static inline int cmd_memread(char *str, uint32_t count) {
  char buffer[255];
  uint32_t addr_val;
  
  addr_val = numdump_str(str, count);
  print("Your number is: ");
  char *res = strdump_number(addr_val, buffer, sizeof(buffer));
  print(res);
  puts("\r\n");

  return 0;
};

#endif
