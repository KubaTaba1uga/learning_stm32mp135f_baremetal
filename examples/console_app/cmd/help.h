#ifndef HELP_H
#define HELP_H

#include <stdint.h>

#include "stdlib.h"

static inline int cmd_help(int argc, char *argv[]) {
  const char *help_string =
      "Welcome to the console app example :)\r\n"
      "\r\n"
      "Available commands:\r\n"
      " - help\r\n"
      "   Display a list of available commands and their usage.\r\n"
      "\r\n"
      " - memread [-d] <addr>\r\n"
      "   Read the value at the specified memory address.\r\n"
      "   The address must be given as a hexadecimal value using only\r\n"
      "   uppercase letters.\r\n"
      "   Flags control the output format: by default, values are shown\r\n"
      "   in hexadecimal. Use the `-d` flag to display values in decimal.\r\n"
      "\r\n"
      " - memwrite <addr> <value>\r\n"
      "   Write a value to the specified memory address.\r\n"
      "   Both the address and value must be specified as hexadecimal\r\n"
      "   numbers using uppercase letters.\r\n"
      "\r\n"
      " - sleep <seconds>\r\n"
      "   Wait number of seconds.\r\n"
      "   Seconds value must be represented as decimal number.\r\n"
      "\r\n"
      " - echo\r\n"
      "   Display a line of text.\r\n"
      "\r\n"
      " - reboot\r\n"
      "   Restart a machine.\r\n"      
      "\r\n";

  puts(help_string);
  return 0;
}

#endif
