#ifndef ECHO_H
#define ECHO_H

#include <stdint.h>

#include "stdlib.h"

static inline int cmd_echo(int argc, char *argv[]) {
  for (uint32_t i = 1; i < argc; i++) {
    print(argv[i]);
    putchar(' ');
  }

  puts("");
  
  return 0;
}

#endif
