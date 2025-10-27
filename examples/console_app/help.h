#ifndef HELP_H
#define HELP_H

#include "stdlib.h"
#include <stdint.h>

static inline int cmd_help(char *str, uint32_t count) {
  char *help_string =
      "Welcome in console app example :)\r\n"
      "\r\n"
      "Available commands are:\r\n"
      " - help\r\n"
      "   Display all available commands and their usage descriptions.\r\n"
      " - memread [-d] <addr>\r\n"
      "   Show value under the memory address. The memory addres hass to be\r\n"
      "   represented as hex value using only uppercase letters.\r\n"
      "   Flags are meant to control how output is presented, by default\r\n"
      "   hex is used, by passing `-d` flag one can output value\r\n"
      "   as decimal.\r\n";

  puts(help_string);

  return 0;
};

#endif
