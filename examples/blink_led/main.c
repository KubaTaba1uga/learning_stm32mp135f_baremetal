//
///
////
/////
/**************************************************************************

                                BLINK LED

This example is about blinking a led connected to GPIO2 which is pin 2 on 40pin
expansion header.

GPIO2 maps to PH6 which means GPIOH pin 6.

GPIOH is connected to ABH4 so first thing to do is to enable clock for GPIOH via
RCC on ABH4.



In order to enable a GPIO peripheral, it should be enabled (clocked) via the RCC (Reset and Clock Control) unit. In the datasheet section 10.8.137 we find that the AHB4ENSETR (AHB1 peripheral clock enable set register) is responsible to turn GPIO banks on or off.


**************************************************************************/
///
//

#include <stdint.h>

#include "uart.h"

/* Table 9. Register boundary addresses */
#define RCC_BASE (0x50000000U)
#define GPIOH_BASE (0x50009000U)

/* 10.8.137 RCC non-secure AHB4 peripheral enable set register */
#define RCC_MP_NS_AHB4ENSETR (*(volatile uint32_t *)(RCC_BASE + 0x770))
/* 10.8.138 RCC non-secure AHB4 peripheral clear register */
#define RCC_MP_NS_AHB4ENCLRR (*(volatile uint32_t *)(RCC_BASE + 0x774))

/* 11.4.1 GPIOH mode register */
#define GPIOH_MODER (*(volatile uint32_t *)(GPIOH_BASE + 0x00))
/* 11.4.7 GPIOH bit set/reset register */
#define GPIOH_BSRR  (*(volatile uint32_t *)(GPIOH_BASE + 0x18))


int main(void) {

  // Enable GPIOH clock (bit 7)  
  RCC_MP_NS_AHB4ENSETR = (1U << 7);

  // 2) PH6: output (01b at bits 13:12), no pull (00b at bits 13:12)
  GPIOH_MODER = (GPIOH_MODER & ~(3U << (6*2))) | (1U << (6*2));
  
  /* Turn off   */
  GPIOH_BSRR = (1U << (6 + 16));
  
  if (RCC_MP_NS_AHB4ENSETR & (1U << 7)) {
    write_to_uart('Y');
  } else {
    write_to_uart('N');
  }
  /* if (RCC_MP_NS_AHB4ENSETR & (1U << 7)) { */
  /*   USART_TDR = 'Y'; */
  /* } else { */
  /*   USART_TDR = 'N'; */
  /* } */

  /* // Disable GPIOH clock (bit 7) */
  RCC_MP_NS_AHB4ENCLRR = (1U << 7);

  if (RCC_MP_NS_AHB4ENSETR & (1U << 7)) {
    write_to_uart('Y');
  } else {
    write_to_uart('N');
  }

  GPIOH_BSRR = (1U << 6);
  
  while(1){
  }
}

/* __attribute__((naked)) void _start(void) { */
/*     __asm volatile ( */
/*         "ldr r0, =_stack_top \n" */
/*         "mov sp, r0          \n" */
/*         "bl  main            \n" */
/*         "b   .               \n" */
/*     ); */
/* } */


/* void _start(void){ */
/*   asm volatile("ldr r0, =_stack_top; mov sp, r0;"); */
/*   main()  ; */
/*   } */
