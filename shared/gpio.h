#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

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

static inline void gpio_set_mode(struct gpio *gpio, uint8_t pin, uint8_t mode) {
  gpio->MODER &= ~(3U << (pin * 2));      // Clear existing setting
  gpio->MODER |= (mode & 3) << (pin * 2); // Set new mode
}

static inline void gpio_set_pin(struct gpio *gpio, uint8_t pin) {
  gpio->BSRR |= (1U << pin);
}

static inline void gpio_clear_pin(struct gpio *gpio, uint8_t pin) {
  gpio->BSRR |= (1U << (pin + 16));
}

static inline bool gpio_get_pin(struct gpio *gpio, uint8_t pin) {
  return gpio->ODR & (1U << pin);
}

#endif
