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
                        UART_TX  UART_RX

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

#include "common.h"
#include "gpio.h"
#include "rcc.h"
#include "uart.h"

#include <stdint.h>

const char word[] = "Hello friend";
void print_banner(struct uart *uart);

int main(void) {
  print_banner(UART4);
  
  { // Enable clock for GPIOB and GPIOC
    rcc_enable_gpio(RCC, GPIO_BANK_B);
    rcc_enable_gpio(RCC, GPIO_BANK_C);
  }

  { // Enable clock for USART1
    rcc_set_src_usart12(RCC, RCC_UART_SRC_HSI, true);
    rcc_enable_usart12(RCC, true);
  }

  { // Configure AF for GPIOB 0 - USART1_RX
    gpio_set_mode(GPIOB, 0, GPIO_MODE_INPUT);
    gpio_set_speed(GPIOB, 0, GPIO_SPEED_HIGH);
    gpio_set_pull(GPIOB, 0, GPIO_PULL_UP);

    gpio_set_mode(GPIOB, 0, GPIO_MODE_AF);
    gpio_set_af(GPIOB, 0, 4); // According datasheet USART1_RX
                              //   is 0100=0x4 for PB0.
  }

  { // Configure AF for GPIOC 0 - USART1_TX
    gpio_set_speed(GPIOC, 0, GPIO_SPEED_HIGH);
    gpio_set_mode(GPIOC, 0, GPIO_MODE_AF);
    gpio_set_af(GPIOC, 0, 7); // According datasheet USART1_TX
                              //  is 0111=0x7 for PC0.
  }

  { // Configure USART1
    // Reset USART1 configuration
    uart_init(USART1);

    /* Settings: */
    /*   baudrate 115200 databits 8 */
    /*   no flow control stopbits 1 */
    /* In tio: tio -b 115200 -d 8 -p none -s 1 -f none /dev/ttyUSB0 */

    // Set baud rate (assuming 64MHz HSI clock, 115200 baud)
    uart_set_baud_rate(USART1, 64000000, 115200);
    uart_set_ctrl(USART1, UART_CR1_ALT_RE, 1U); // Enable reciver
    uart_set_ctrl(USART1, UART_CR1_ALT_TE, 1U); // Enable transiver
    uart_set_ctrl(USART1, UART_CR1_ALT_UE, 1U); // Enable uart
  }

  { // Write banner to USART1
    print_banner(USART1);
  }

  { // Enable GPIOH
    rcc_enable_gpio(RCC, GPIO_BANK_H);
  }

  // Configure GPIOH for output
  const uint8_t gpioh_pin = 6;
  gpio_set_mode(GPIOH, gpioh_pin, GPIO_MODE_OUTPUT);

  { // Simulate console on USART1
    while (true) {
      uart_write_str(USART1, "> ");

      char lc = 0;
      while (true) {
        char c = uart_read_char(USART1);
        if (c == '\n' || c == '\r') {
          uart_write_str(USART1, "\r\n");
          { // Switch LED on/off
            if (lc == 'H') {
              gpio_set_pin(GPIOH, gpioh_pin);
            } else if (lc == 'L') {
              gpio_clear_pin(GPIOH, gpioh_pin);
            }
          }
          break;
        }
        uart_write_char(USART1, c);
        lc = c;
      }
    }
  }

  return 0;
}

void print_banner(struct uart *uart) {
  for (uint8_t i = 0; i < 32; i++) {
    uart_write_str(uart, "\r\n");
  }

  uart_write_char(uart, '-');
  uart_write_str(uart, word);
  uart_write_char(uart, '-');
  uart_write_str(uart, "\r\n");

}

