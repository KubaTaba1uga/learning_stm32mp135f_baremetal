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




#endif // COMMON_H
