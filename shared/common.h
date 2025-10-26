#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdio.h>

enum ERROR {
  ERROR_NONE = 0,
  ERROR_NO_ENTRY,
  ERROR_INVALID_INPUT,
};

enum GPIO_BANK {
  GPIO_BANK_A = 0,
  GPIO_BANK_B,
  GPIO_BANK_C,
  GPIO_BANK_D,
  GPIO_BANK_E,
  GPIO_BANK_F,
  GPIO_BANK_G,
  GPIO_BANK_H,
  GPIO_BANK_I,
};

#define BITS_CLEAR(reg, max, bits) ((reg) &= ~((max) << (bits)))

#define BITS_SET(reg, value, max, bits) ((reg) |= (((value) & (max)) << (bits)))

#define BIT_SET(reg, bit) BITS_SET(reg, 1U, 1U, bit)

#define BIT_GET(reg, bit) ((reg) & (1U << (bit)))

#define BIT_CLEAR(reg, bit) BITS_CLEAR(reg, 1U, bit)

#define true 1
#define false 0

typedef uint8_t bool;

#define NULL ((void *)0)

static inline char *number_to_str(uint32_t number, char *buffer,
                                  uint32_t buffer_len) {
  char *start = buffer + (buffer_len - 1);
  *start = 0;

  for (uint32_t i = 1; start != buffer; i *= 10) {
    if (i > number) {
      break;
    }

    uint32_t div = (number / i) % 10;

    start--;
    *start = div + 48;
  }

  return start;
}

static inline char *hex_to_str(uint32_t number, char *buffer,
                               uint32_t buffer_len) {
  char *start = buffer + (buffer_len - 1);
  *start = 0;

  for (uint32_t i = 1; start != buffer; i *= 16) {
    if (i > number) {
      break;
    }

    uint32_t div = (number / i) % 16;

    start--;

    if (div <= 9) {
      *start = div + 48;
    } else {
      *start = div + 65 - 10;
    }
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

  for (uint32_t i = 1; addr_str_start != addr_str_end--; i *= 16) {
    uint32_t val;    
    if (*addr_str_end >= 65 && *addr_str_end <= 70) {
      val = *addr_str_end - 65 + 10;
    } else {
      val = *addr_str_end - 48;
    }

    if (i > 1) {
      addr_val += val * i;
    } else {
      addr_val += val;
    }
  }

  return addr_val;
}

#endif // COMMON_H
