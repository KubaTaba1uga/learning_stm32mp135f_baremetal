#ifndef SLEEP_H
#define SLEEP_H

#include <stdint.h>

#include "common.h"
#include "rcc.h"
#include "stdlib.h"
#include "string.h"
#include "tim.h"

static inline int __cmd_sleep_init(void) {
  rcc_enable_tim67(RCC, true);

  enum CLOCK apb1_clk = rcc_get_mlahb_clk(RCC);
  switch (apb1_clk) {
  case CLOCK_HSI:
    break;
  default:
    puts("APB1 clock=Not supported");
    goto err_out;
  }

  uint32_t hsi_freq = rcc_get_hsi_frq(RCC);
  switch (hsi_freq) {
  case -1:
    puts("HSI frequency=Invalid value");
    goto err_out;
  default:;
  }

  uint32_t mlahb_div = rcc_get_mlahb_div(RCC);
  switch (mlahb_div) {
  case 0:
    break;
  case -1:
    puts("MLAHB divisor=Invalid value");
    goto err_out;
  default:
    hsi_freq = hsi_freq / mlahb_div;
  };

  uint32_t apb1_div = rcc_get_apb1_div(RCC);
  switch (apb1_div) {
  case 0:
    break;
  case -1:
    print("APB1 divisor=Invalid value");
    goto err_out;
  default:
    hsi_freq = hsi_freq / apb1_div;
  }

  uint32_t hsi_multi = RCC->TIMG1PRER & 0x1;
  if (hsi_multi == 0) {
    switch (apb1_div) {
    case 0x1:
    case 0x2:
      hsi_multi = 1;
      break;
    default:
      hsi_multi = 2;
    }
  } else {
    switch (apb1_div) {
    case 0x1:
    case 0x2:
    case 0x4:
      hsi_multi = 1;
      break;
    default:
      hsi_multi = 4;
    }
  }

  hsi_freq = hsi_freq * hsi_multi;

  uint32_t timer_freq =
      hsi_freq / 1000; // We want one tick per milisecond, 1 second has 1000
                       // milisceonds hence the value.
  if (timer_freq > (uint16_t)-1) {
    print("Invalid timer freq");
    goto err_out;
  }

  tim_init(TIM6);
  tim_set_prescaler(TIM6, timer_freq);
  tim_enable_counter_mode(TIM6);

  return 0;

err_out:
  return ERROR_INVALID_INPUT;
}

static inline int __cmd_sleep_main(int argc, char *argv[]) {
  char buffer[255];

  if (argc < 2) {
    puts("You have to provide number of seconds.");
    puts("For example: sleep 10");
    return ERROR_INVALID_INPUT;
  }

  uint32_t user_number = str_to_number(argv[1], strlen(argv[1]));
  if (user_number == -1) {
    puts("You have to provide valid number.");
    puts("For example: sleep 10");
    return ERROR_INVALID_INPUT;
  }

  struct tim_status tim6 = tim_dump_status(TIM6);
  if (!tim6.is_enabled) {
    puts("Timer is not configured.");
    return ERROR_INVALID_INPUT;
  }

  uint32_t last = tim_get_counter(TIM6);
  uint32_t now = last - 10;
  uint32_t miliseconds = 1;
  uint32_t seconds = 0;
  while (seconds < user_number) {
    if (now != last) {
      if (miliseconds % 1000 == 0) {
        seconds++;

        print("Timer: ");
        puts(number_to_str(seconds, buffer, 255));
      }

      last = now;
      miliseconds++;
    }

    now = tim_get_counter(TIM6);
  }

  return 0;
}

#endif
