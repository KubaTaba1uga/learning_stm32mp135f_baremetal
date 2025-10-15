//
///
////
/////
/**************************************************************************

                                UART DRIVER

Wich GPIO to use for uart?
USART1 is exposed via alternate functions of:
- GPIO pin 8  - CPU pin PC0 - USART1_TX
- GPIO pin 10 - CPU pin PB0 - USART1_RX
- GPIO pin 11 - CPU pin PC2 - USART1_RTS
- GPIO pin 36 - CPU pin PA7 - USART1_CTS

For this example we will use only:
- USART1_TX
- USART1_RX

40 pin gpio:
                              GND
                              |
                              |       1
* * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * *
                              | |     2
                              | |
                        UART_RX  UART_TX

Memory regions:
USART1 memory start is 0x4C000000
GPIOC memory start is  0x50004000
GPIOB memory start is  0x50003000


How enable USART1 clock?
10.8.71  RCC_UART12CKSELR  - allow choosing clock source for usart1, we use
                             `pll3_q_ck`.
10.8.131 RCC_MP_APB6ENSETR - enable clock for usart1
10.8.132 RCC_MP_APB6ENCLRR - disable clock for usart1

How enable alternate function of GPIO pin?
Section 11.3.2
Each I/O pin has a multiplexer with up to sixteen alternate function inputs (AF0
to AF15) that can be configured through the GPIOx_AFRL (for pin 0 to 7) and
GPIOx_AFRH (for pin 8 to 15) registers.

To use an I/O in a given configuration, the user has to proceed as follows:
  1. GPIO: configure the desired I/O as output, input or analog in the
     GPIOx_MODER register.
  2. Connect the I/O to the desired AFx in one of the GPIOx_AFRL or GPIOx_AFRH
     register.
  3. Select the type, pull-up/pull-down and output speed via the GPIOx_OTYPER,
     GPIOx_PUPDR and GPIOx_OSPEEDER registers, respectively.
  4. Configure the desired I/O as an alternate function in the GPIOx_MODER
     register.



**************************************************************************/
///
//

#include "gpio.h"
#include "rcc.h"
#include <stdint.h>

// Base address cannot be cast to ptr because then all additions are treated
//  as ptrs additions not as address adition causing bugs.
#define UART4_BASE 0x40010000U  // UART4 base address
#define USART1_BASE 0x4C000000U // UART4 base address

// USART transmit data register
#define USART4_TDR (volatile uint32_t *)(UART4_BASE + 0x28)
#define USART1_TDR (volatile uint32_t *)(USART1_BASE + 0x28)

// USART interrupt and status register
#define USART4_ISR (volatile uint32_t *)(UART4_BASE + 0x1C)
#define USART1_ISR (volatile uint32_t *)(USART1_BASE + 0x1C)

#define USART_ISR_TXE (1u << 7) // Transmit data register empty
// This is 7th bit of register so we want 0b1000000.

static uint32_t read_bit_in_register(volatile uint32_t *reg, uint32_t bit) {
  return *reg & bit;
}

static void write_to_register(volatile uint32_t *reg, uint32_t value) {
  *reg = value;
}

// By using data from .rodata section we
// confirm that linker script is working properly
const char word[] = "Hello friend";

void print_banner() {
  { // Print banner
    while (!read_bit_in_register(USART4_ISR, USART_ISR_TXE)) {
    }
    write_to_register(USART4_TDR, '-');

    for (int32_t i = 0; word[i] != 0; i++) {
      while (!read_bit_in_register(USART4_ISR, USART_ISR_TXE)) {
      }
      write_to_register(USART4_TDR, word[i]);
    }

    while (!read_bit_in_register(USART4_ISR, USART_ISR_TXE)) {
    }
    write_to_register(USART4_TDR, '-');
  }
}

int main(void) {
  /*
    TO-DO:
      1. Enable alternate function of PC0 and PB0. DONE
      2. Enable clock for USART1. DONE
      3. Create func to write char.
      4. Create func to write str.
      5. Create func to read char by polling.
      6. Create func to read char as interrupt handler.
  */

  print_banner();
  
  { // Configure AF for PB0 - USART1_RX
    gpio_set_mode(GPIOB, 0, GPIO_MODE_INPUT);
    gpio_set_af(GPIOB, 0, 0x4); // According datasheet USART1_RX
                                //   is 0100=0x4 for PB0    
    gpio_set_pull(GPIOB, 0, GPIO_PULL_NONE);
    gpio_set_speed(GPIOB, 0, GPIO_SPEED_MEDIUM);
    gpio_set_mode(GPIOB, 0, GPIO_MODE_AF);
  }

  { // Configure AF for PC0 - USART1_TX
    gpio_set_mode(GPIOC, 0, GPIO_MODE_OUTPUT);
    gpio_set_af(GPIOC, 0, 0x7); // According datasheet USART1_TX
                                //  is 0111=0x7 for PC0    
    gpio_set_output(GPIOC, 0, GPIO_OUTPUT_PUSH_PULL);
    gpio_set_pull(GPIOC, 0, GPIO_PULL_NONE);
    gpio_set_speed(GPIOC, 0, GPIO_SPEED_MEDIUM);
    gpio_set_mode(GPIOC, 0, GPIO_MODE_AF);
  }

  { // Enable clock for USART1
    rcc_set_src_usart12(RCC, RCC_UART_SRC_PLL3, true);
    rcc_enable_usart12(RCC, true);
  }

  /* { // Write character to USART1 */
  /*   while (!read_bit_in_register(USART1_ISR, USART_ISR_TXE)) { */
  /*   } */
  /*   write_to_register(USART1_TDR, '-'); */
  /* } */

  print_banner();
  
  return 0;
}
