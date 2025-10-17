#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>

#include "common.h"

struct gpio {
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFRL;
  volatile uint32_t AFRH;
  volatile uint32_t BRR;
  volatile uint32_t SECCFGR;
  volatile uint32_t HWCFGR9;
  volatile uint32_t HWCFGR8;
  volatile uint32_t HWCFGR7;
  volatile uint32_t HWCFGR6;
  volatile uint32_t HWCFGR5;
  volatile uint32_t HWCFGR4;
  volatile uint32_t HWCFGR3;
  volatile uint32_t HWCFGR2;
  volatile uint32_t HWCFGR1;
  volatile uint32_t HWCFGR0;
  volatile uint32_t VERR;
  volatile uint32_t IPIDR;
  volatile uint32_t SIDR;
};

#define GPIOA ((struct gpio *)0x50002000U)
#define GPIOB ((struct gpio *)0x50003000U)
#define GPIOC ((struct gpio *)0x50004000U)
#define GPIOD ((struct gpio *)0x50005000U)
#define GPIOE ((struct gpio *)0x50006000U)
#define GPIOF ((struct gpio *)0x50007000U)
#define GPIOG ((struct gpio *)0x50008000U)
#define GPIOH ((struct gpio *)0x50009000U)
#define GPIOI ((struct gpio *)0x5000A000U)

enum { GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG };

enum {
  GPIO_SPEED_LOW,
  GPIO_SPEED_MEDIUM,
  GPIO_SPEED_HIGH,
  GPIO_SPEED_VERY_HIGH
};

enum { GPIO_PULL_NONE, GPIO_PULL_UP, GPIO_PULL_DOWN, GPIO_PULL_RESERVED };

enum { GPIO_OUTPUT_PUSH_PULL, GPIO_OUTPUT_OPEN_DRAIN };

static inline void gpio_set_mode(struct gpio *gpio, uint8_t pin, uint8_t mode) {
  const uint8_t max = 3U;
  const uint8_t shift = 2 * pin;

  BITS_CLEAR(gpio->MODER, max, shift);
  BITS_SET(gpio->MODER, mode, max, shift);
}

static inline void gpio_set_pin(struct gpio *gpio, uint8_t pin) {
  BIT_SET(gpio->BSRR, pin);
}

static inline void gpio_clear_pin(struct gpio *gpio, uint8_t pin) {
  BIT_SET(gpio->BSRR, pin + 16);
}

static inline bool gpio_get_pin(struct gpio *gpio, uint8_t pin) {
  return BIT_GET(gpio->ODR, pin);
}

static inline void gpio_set_speed(struct gpio *gpio, uint8_t pin,
                                  uint8_t speed) {
  const uint8_t max = 3U;
  const uint8_t shift = 2 * pin;

  BITS_CLEAR(gpio->OSPEEDR, max, shift);
  BITS_SET(gpio->OSPEEDR, speed, max, shift);
}

static inline void gpio_set_pull(struct gpio *gpio, uint8_t pin, uint8_t pull) {
  const uint8_t max = 3U;
  const uint8_t shift = 2 * pin;

  BITS_CLEAR(gpio->PUPDR, max, shift);
  BITS_SET(gpio->PUPDR, pull, max, shift);
}

static inline void gpio_set_output(struct gpio *gpio, uint8_t pin,
                                   uint8_t output) {
  BIT_CLEAR(gpio->OTYPER, pin);
  BITS_SET(gpio->OTYPER, output, 1U, pin);
}

static inline void gpio_set_af(struct gpio *gpio, uint8_t pin, uint8_t af) {
  const uint8_t max = 0xF;
  const uint8_t shift = 4 * pin;

  if (pin < 8) {
    BITS_CLEAR(gpio->AFRL, max, shift);   // Clear existing setting
    BITS_SET(gpio->AFRL, af, max, shift); // Set new output mode
  } else if (pin < 16) {
    BITS_CLEAR(gpio->AFRH, max, shift);   // Clear existing setting
    BITS_SET(gpio->AFRH, af, max, shift); // Set new output mode
  }
}

#endif
