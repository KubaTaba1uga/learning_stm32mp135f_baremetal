//
///
////
/////
/**************************************************************************

                                BASIC TIMERS

Example demonstrates basic timers control on STM32MP135.

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

   Once we have 64MHZ we can set MLAHBDIV to divide by 256 so we have
   64000000HZ/246=250000HZ.

   Once we have 250 000HZ we can set APB1DIV to divide by 16 so we have
   250 000HZ/16 = 15625HZ.

   in one second timer will fire up 15625 times. One millisecond is 1/1000 of
   seconds. So to count one milisecond we need to increment each 15 fires
   because 15*1000=15000.

   To set clock to HSI i changed device tree in optee from stm32mp135f-dk CLK_MLAHBS_PLL3 to CLK_MLAHBS_HSI.





**************************************************************************/
///
//
#include "rcc.h"
#include "stdlib.h"
#include "uart.h"

struct uart *stdout = NULL;

int main(void) {
  /* char buffer[255]; */
  /* char *result; */

  stdout = UART4;

  puts("Hello world");

  switch (RCC->MSSCKSELR & 0b11) {
  case 0b00:
    puts("HSI clock");
    break;
  case 0b01:
    puts("HSE clock");
    break;    
  case 0b10:
    puts("CSI clock");
    break;    
  case 0b11:
    puts("PLL3 clock");
    break;    
  }

  return 0;
}
