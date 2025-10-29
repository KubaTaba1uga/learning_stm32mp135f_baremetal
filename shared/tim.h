#ifndef TIM_H
#define TIM_H
#include "common.h"

#include <stdint.h>

struct tim {
  uint32_t CR1;
  uint32_t CR2;
  uint8_t _reserved[4];
  uint32_t DIER;
  uint32_t SR;
  uint32_t EGR;
  uint8_t _reserved0[12];
  uint32_t CNT;
  uint32_t PSC;
  uint32_t ARR;
};

#define TIM6 ((struct tim *)0x40004000)
#define TIM7 ((struct tim *)0x40005000)

static inline void tim_init(struct tim *tim) {
  tim->CR1 = 0;
  tim->CR2 = 0;
  tim->DIER = 0;
  tim->SR = 0;
  tim->EGR = 0;
  tim->CNT = 0;
  tim->PSC = 0;
  tim->ARR = 0xFFFF;
}

static inline void tim_set_prescaler(struct tim *tim, uint16_t prescaler) {
  tim->PSC = prescaler & 0xFFFF;  
}

static inline uint16_t tim_get_prescaler(struct tim *tim) {
  return tim->PSC & 0xFFFF;
}

/*
  Normal mode does not care about prescaler.
  It plainly pass frequency from the bus into the counter.
*/
static inline void tim_enable_normal_mode(struct tim *tim) {
  tim->CR1 = (1U) | (1U << 1);
}

/*
  Counter mode care about prescaler.
  It divide bus frequency by prescaler value before passing it to the counter.
*/
static inline void tim_enable_counter_mode(struct tim *tim) {
  BIT_SET(tim->EGR, 0);
    
  tim->CR1 = (1U);
}

static inline uint32_t tim_get_counter(struct tim *tim) {
  return tim->CNT & 0xFFFF;
}

struct tim_status {
  bool is_enabled;
  bool is_update_enabled;
  bool is_one_pulse_mode_enabled;
  bool is_auto_reload_enabled;
  uint16_t prescaler;
};

static inline struct tim_status tim_dump_status(struct tim *tim) {
  return (struct tim_status){
      .is_enabled = TIM6->CR1 & 0b1,
      .is_update_enabled = TIM6->CR1 & (1U << 1),
      .is_one_pulse_mode_enabled = TIM6->CR1 & (1U << 3),
      .is_auto_reload_enabled = TIM6->CR1 & (1U << 7),
      .prescaler = tim_get_prescaler(tim),
  };
}

#endif // TIM_H
