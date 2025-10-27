#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

#include "uart.h"

extern struct uart *stdout;

static inline char getchar(void) { return uart_read_char(stdout); }
static inline void putchar(char c) { uart_write_char(stdout, c); }

static inline int puts(const char *str) {
  uint32_t i = 0;
  while (*str) {
    uart_write_char(stdout, *str++);
    i++;
  }

  uart_write_str(stdout, "\r\n");
  i += 2;

  return i;
};

static inline void print(char *str) { uart_write_str(stdout, str); };

static inline char *gets(char *str, uint32_t count, bool echo) {
  uint32_t max = count - 1;
  for (uint32_t i = 0; i < max; i++) {
    str[i] = uart_read_char(stdout);
    if (str[i] == '\r' ||str[i] == '\n' ) {
      str[i] = 0;
      break;
    }
    if (echo) {
      uart_write_char(stdout, str[i]);
    }
  }

  str[max] = 0; // In case there is no newline

  return str;
};

int strncmp(const char *lhs, const char *rhs, uint32_t count) {
  for (uint32_t i = 0; i < count; i++) {
    if (lhs[i] == 0 || rhs[i] == 0) {
      break;
    }

    if (lhs[i] != rhs[i]) {
      return 1;
    }
  }

  return 0;
};

uint32_t strlen(const char *str) {
  uint32_t i = 0;
  while (*str++) {
    i++;
  }

  return i;
};

bool isdigit(char c) { return (c >= '0') && (c <= '9'); }
bool islower(char c) { return (c >= 'a') && (c <= 'z'); }
bool isupper(char c) { return (c >= 'A') && (c <= 'Z'); }

#endif
