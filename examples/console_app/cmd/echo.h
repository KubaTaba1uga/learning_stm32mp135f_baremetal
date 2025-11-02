#ifndef ECHO_H
#define ECHO_H

#include <stdint.h>

#include "stdlib.h"

static inline int cmd_echo(char *str, uint32_t count) {
  for (uint32_t i = 0; i < count && str[i]; i++) {
    putchar(str[i]);
  }
  
  return 0;
}

#endif
