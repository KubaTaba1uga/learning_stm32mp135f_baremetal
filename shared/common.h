#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

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

#endif // COMMON_H
