#ifndef HELP_H
#define HELP_H

#include "stdlib.h"
#include <stdint.h>

static inline int cmd_help(char *str, uint32_t count) {
  char *help_string =
      "Welcome in console app example :)\r\n"
      "Available commands are:\r\n"
      " - help\r\n"
      "   Display all available commands and their usage descriptions.\r\n";

  puts(help_string);

  return 0;
};

#endif
