#ifndef RCC_H
#define RCC_H

#include <stdint.h>

/* Table 9. Register boundary addresses */
#define RCC_BASE (0x50000000U)

/* 10.8.137 RCC non-secure AHB4 peripheral enable set register */
#define RCC_MP_NS_AHB4ENSETR (*(volatile uint32_t *)(RCC_BASE + 0x770))
/* 10.8.138 RCC non-secure AHB4 peripheral clear register */
#define RCC_MP_NS_AHB4ENCLRR (*(volatile uint32_t *)(RCC_BASE + 0x774))

static inline void enable_gpio_clock(char bank) {
  uint8_t pin = -1;
  switch (bank) {
  case 'A':
    pin = 0;
    break;
  case 'B':
    pin = 1;
    break;
  case 'C':
    pin = 2;
    break;
  case 'D':
    pin = 3;
    break;
  case 'E':
    pin = 4;
    break;
  case 'F':
    pin = 5;
    break;
  case 'G':
    pin = 6;
    break;
  case 'H':
    pin = 7;
    break;
  case 'I':
    pin = 8;
    break;
  default:;
  }

  if (pin != (uint8_t)-1) {
    RCC_MP_NS_AHB4ENSETR = (1U << pin);
  }
}

static inline void disable_gpio_clock(char bank) {
  uint8_t pin = -1;
  switch (bank) {
  case 'A':
    pin = 0;
    break;
  case 'B':
    pin = 1;
    break;
  case 'C':
    pin = 2;
    break;
  case 'D':
    pin = 3;
    break;
  case 'E':
    pin = 4;
    break;
  case 'F':
    pin = 5;
    break;
  case 'G':
    pin = 6;
    break;
  case 'H':
    pin = 7;
    break;
  case 'I':
    pin = 8;
    break;
  default:;
  }

  if (pin != (uint8_t)-1) {
    RCC_MP_NS_AHB4ENCLRR = (1U << pin);
  }
}

#endif
