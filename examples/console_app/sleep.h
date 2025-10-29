#ifndef SLEEP_H
#define SLEEP_H

#include <stdint.h>

#include "common.h"
#include "rcc.h"
#include "stdlib.h"
#include "string.h"
#include "tim.h"

static inline int cmd_sleep(char *str, uint32_t count) {
  char buffer[255];

  uint32_t user_number = str_to_number(str, count);

  // Enable TIM6 clock
  rcc_enable_tim67(RCC, true);

  enum CLOCK apb1_clk = rcc_get_mlahb_clk(RCC);
  switch (apb1_clk) {
  case CLOCK_HSI:
    puts("APB1 clock=HSI");
    break;
  default:
    puts("APB1 clock=Not supported");
    goto err_out;
  }

  print("HSI frequency=");
  uint32_t hsi_freq = rcc_get_hsi_frq(RCC);
  switch (hsi_freq) {
  case -1:
    puts("Invalid value");
    goto err_out;
  default:
    puts(number_to_str(hsi_freq, buffer, 255));
  }

  print("MLAHB divisor=");
  uint32_t mlahb_div = rcc_get_mlahb_div(RCC);
  switch (mlahb_div) {
  case 0:
    puts("Not divided");
    break;
  case -1:
    puts("Invalid value");
    goto err_out;
  default:
    hsi_freq = hsi_freq / mlahb_div;
    puts(number_to_str(mlahb_div, buffer, 255));
  };

  print("APB1 divisor=");
  uint32_t apb1_div = rcc_get_apb1_div(RCC);
  switch (apb1_div) {
  case 0:
    puts("Not divided");
    break;
  case -1:
    puts("Invalid value");
    goto err_out;
  default:
    hsi_freq = hsi_freq / apb1_div;
    puts(number_to_str(apb1_div, buffer, 255));
  }

  print("HSI multiplier=");
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
  puts(number_to_str(hsi_multi, buffer, 255));

  uint32_t timer_freq =
      hsi_freq / 1000; // We want one tick per milisecond, 1 second has 1000
                       // milisceonds hence the value.
  if (timer_freq > (uint16_t)-1) {
    print("Invalid timer freq");
    puts(number_to_str(apb1_div, buffer, 255));
    goto err_out;
  }
  tim_init(TIM6);

  tim_set_prescaler(TIM6, timer_freq);
  tim_enable_counter_mode(TIM6);

  struct tim_status tim6_dump = tim_dump_status(TIM6);
  if (tim6_dump.is_enabled) {
    puts("TIM6=Enabled");
  } else {
    puts("TIM6=Disabled");
  }

  if (tim6_dump.is_update_enabled) {
    puts("TIM6=Update diabled");
  } else {
    puts("TIM6=Update enabled");
  }

  if (tim6_dump.is_one_pulse_mode_enabled) {
    puts("TIM6=one-pulse mode enabled");
  } else {
    puts("TIM6=one-pulse mode disabled");
  }

  if (tim6_dump.is_auto_reload_enabled) {
    puts("TIM6=auto reaload enabled");
  } else {
    puts("TIM6=auto reaload disabled");
  }

  print("TIM6=Prescaler: ");
  puts(number_to_str(tim6_dump.prescaler, buffer, 255));

  // Observe the counter
  uint32_t last = tim_get_counter(TIM6);
  uint32_t now = tim_get_counter(TIM6);
  uint32_t miliseconds = 0;
  while (user_number) {
    if (now != last) {
      if (miliseconds % 1000 == 0) {
        print("Timer: ");
        puts(number_to_str(user_number, buffer, 255));
        user_number--;
      }

      last = now;
      miliseconds++;
    }

    now = tim_get_counter(TIM6);
  }

  return 0;

err_out:
  return ERROR_INVALID_INPUT;
}

#endif
