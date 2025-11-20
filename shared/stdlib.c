#include "stdlib.h"
#include "uart.h"

int getchar(void) { return uart_read_char(mystdout); }

int putchar(int c) {
  uart_write_char(mystdout, c);
  return 0;

  }

int puts(const char *str) {
  uint32_t i = 0;
  while (*str) {
    uart_write_char(mystdout, *str++);
    i++;
  }

  uart_write_str(mystdout, "\r\n");
  i += 2;

  return i;
};

void print(char *str) { uart_write_str(mystdout, str); };

char *gets(char *str, uint32_t count, bool echo) {
  uint32_t max = count - 1;
  for (uint32_t i = 0; i < max; i++) {
    str[i] = uart_read_char(mystdout);
    if (str[i] == '\r' || str[i] == '\n') {
      str[i] = 0;
      break;
    }
    if (echo) {
      uart_write_char(mystdout, str[i]);
    }
  }

  str[max] = 0; // In case there is no newline

  return str;
};

int strncmp(const char *lhs, const char *rhs,long unsigned int count) {
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

long unsigned int strlen(const char *str) {
  uint32_t i = 0;
  for (; *str; str++) {
    i++;
  }

  return i;
};

int isdigit(int c) { return (c >= '0') && (c <= '9'); }
int islower(int c) { return (c >= 'a') && (c <= 'z'); }
int isupper(int c) { return (c >= 'A') && (c <= 'Z'); }

