//
///
////
/////
/**************************************************************************

                                BASIC TIMERS

Example demonstrates basic timers control on STM32MP135.

The quality of timer can be checked via `sudo ./shared/time.expect`.

NOTES:
   Basic timers are TIM6 and TIM7.

   First thing to do is to select appropriate clock for TIMx via RCC
   and enable it via (RCC_MP_APB1ENSETR 0x700 (1U << 4)

   TIM 6 and 7 are connected to APB1. To control the frequency of their clocks
we need to use APB1DIV and TIMG1PRE.

   To enable clocks use TIM6EN.


             mlahbss_ck            pclk1
   MLAHBDIV -----------> APB1DIV --------> APB1

   We need to find out wich clock is set in (RCC_MSSCKSELR) 0x548

   One can select MLAHB src to be one of:
     HSI (64MHz) clock - default
     HSE clock
     CSI clock
     PLL3 clock

   Once we have 64MHZ we can set MLAHBDIV to not divideso we have 64000000HZ.

   Once we have 64MHZ we can set APB1DIV to divide by 16 so we have
   64MHZ/16 = 4MHZ.

   Then we set prescaler to 4000 wich gives us 4MHz/4000=1KHZ

   To set clock to HSI i changed device tree in optee.

**************************************************************************/
///
//
#include <stdint.h>

#include "common.h"
#include "rcc.h"
#include "stdlib.h"
#include "string.h"
#include "tim.h"
#include "uart.h"

struct uart *stdout = NULL;

int main(void) {
  char buffer[255];

  stdout = UART4;

  puts("Hello world");

  // Enable TIM6 clock
  rcc_enable_tim67(RCC, true);

  enum CLOCK apb1_clk = rcc_get_mlahb_clk(RCC);
  switch (apb1_clk) {
  case CLOCK_HSI:
    puts("APB1 clock=HSI");
    break;
  default:
    puts("APB1 clock=Not supported");
    goto hang;
  }

  print("HSI frequency=");
  uint32_t hsi_freq = rcc_get_hsi_frq(RCC);
  switch (hsi_freq) {
  case -1:
    puts("Invalid value");
    goto hang;
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
    goto hang;
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
    goto hang;
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
    goto hang;
  }
  tim_init(TIM6);

  tim_set_prescaler(TIM6, timer_freq);
  tim_enable_counter_mode(TIM6);

  if (TIM6->CR1 & 0b1) {
    puts("TIM6=Enabled");
  } else {
    puts("TIM6=Disabled");
  }

  if (TIM6->CR1 & (1U << 1)) {
    puts("TIM6=Update diabled");
  } else {
    puts("TIM6=Update enabled");
  }

  if (TIM6->CR1 & (1U << 3)) {
    puts("TIM6=one-pulse mode enabled");
  } else {
    puts("TIM6=one-pulse mode disabled");
  }

  if (TIM6->CR1 & (1U << 7)) {
    puts("TIM6=auto reaload enabled");
  } else {
    puts("TIM6=auto reaload disabled");
  }

  print("TIM6=Prescaler: ");
  puts(number_to_str(TIM6->PSC & 0xFFFF, buffer, 255));

  // Observe the counter
  uint32_t last = tim_get_counter(TIM6);
  uint32_t now = tim_get_counter(TIM6);
  uint32_t miliseconds = 0;
  uint32_t seconds = 0;
  while (1) {
    if (now != last) {
      if (miliseconds % 1000 == 0) {
        print("Timer: ");
        puts(number_to_str(seconds, buffer, 255));
        seconds++;
      }

      last = now;
      miliseconds++;
    }

    now = tim_get_counter(TIM6);
  }

  return 0;

hang:
  while (1) {
  }
}
