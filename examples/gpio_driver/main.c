//
///
////
/////
/**************************************************************************

                                GPIO DRIVER

Example demonstrates modular GPIO control on STM32MP135 using custom rcc, gpio,
and uart drivers to enable GPIOH, configure PH6 as output, and blink an LED
while reporting its state via UART.

**************************************************************************/
///
//

#include <stdint.h>

#include "rcc.h"
#include "uart.h"
#include "gpio.h"

void wait();
void print_pin(struct gpio *gpio, uint8_t pin);

int main(void) {
  // Enable GPIOH clock (bit 7)
  enable_gpio_clock('H');
  /* disable_gpio_clock('H');   */
  
  // Set pin mode for output (01b at bits 13:12)
  gpio_set_mode(GPIOH, 6, GPIO_MODE_OUTPUT);
  
  while (1) {
    // Drive pin high
    gpio_set_pin(GPIOH, 6);
    print_pin(GPIOH, 6);    
    wait();
    
    // Drive pin low
    gpio_clear_pin(GPIOH, 6);
    print_pin(GPIOH, 6);
    wait();
  }

  return 0;  
}


void wait() { uint32_t i = 0x10000000; while (i--) {(void)i;}}

void print_pin(struct gpio *gpio, uint8_t pin) {
  if (gpio_get_pin(gpio,  pin)){
    write_to_uart('H');    
  } else {
    write_to_uart('L');    
  }
}
