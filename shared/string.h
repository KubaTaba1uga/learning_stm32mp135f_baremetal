#ifndef STRING_H
#define STRING_H

#include "stdlib.h"
#include <common.h>

static inline char *number_to_str(uint32_t number, char *buffer,
                                  uint32_t buffer_len) {
  char *start = buffer + (buffer_len - 1);
  *start = 0;

  for (uint32_t i = 1, j = 0; start != buffer; i *= 10) {
    uint32_t div = (number / i) % 10;

    start--;
    *start = div + 48;

    if (++j == 10) { // Break if we have 32 bits.
      break;
    }
  }

  while (*start == '0') {
    start++;
  }

  return start;
}

static inline char *hex_to_str(uint32_t number, char *buffer,
                               uint32_t buffer_len) {
  char *start = buffer + (buffer_len - 1);
  *start = 0;

  for (uint32_t i = 1, j = 0; start != buffer; i *= 16) {
    uint32_t div = (number / i) % 16;

    start--;
    if (div <= 9) {
      *start = div + 48;
    } else {
      *start = div + 65 - 10;
    }

    if (++j == 8 || !*start) { // Break if we have 32 bits.
      break;
    }
  }

  while (*start == '0') {
    start++;
  }

  start--;
  *start = 'x';
  start--;
  *start = '0';

  return start;
}

static inline uint32_t str_to_number(char *buffer, uint32_t buffer_len) {
  char *addr_str_start = NULL;
  char *addr_str_end = NULL;
  uint32_t addr_val = 0;

  for (uint32_t i = 0; i < buffer_len; i++) {
    if (buffer[i] >= 48 && buffer[i] <= 57) {
      if (!addr_str_start) {
        addr_str_start = buffer + i;
      }
      continue;
    }

    if (addr_str_start) {
      addr_str_end = buffer + i;
      break;
    }
  }

  if (!addr_str_start || !addr_str_end) {
    return -1;
  }

  for (uint32_t i = 1; addr_str_start != addr_str_end--; i *= 10) {
    uint32_t val = *addr_str_end - 48;
    if (i > 1) {
      addr_val += val * i;
    } else {
      addr_val += val;
    }
  }

  return addr_val;
}

static inline uint32_t hex_to_number(char *buffer, uint32_t buffer_len) {
  char *addr_str_start = NULL;
  char *addr_str_end = NULL;
  uint32_t addr_val = 0;

  for (uint32_t i = 0; i < buffer_len; i++) {
    if ((buffer[i] >= 48 && buffer[i] <= 57) ||
        (buffer[i] >= 65 && buffer[i] <= 70)) {
      if (buffer[i] != '0' && !addr_str_start) {
        addr_str_start = buffer + i;
      }
      
      if (addr_str_start) {
        addr_str_end = buffer + i;
      }
    }
  }


  
  if (!addr_str_start || !addr_str_end) {
    return -1;
  }

  for (uint32_t i = 1; (addr_str_start - 1) != addr_str_end; i *= 16) {
    uint32_t val;
    if (*addr_str_end >= 48 && *addr_str_end <= 57) {
      val = *addr_str_end - 48;
    } else {
      val = *addr_str_end - 65 + 10;
    }

    if (i > 1) {
      addr_val += val * i;
    } else {
      addr_val += val;
    }

    addr_str_end--;
  }

  return addr_val;
}

#endif
