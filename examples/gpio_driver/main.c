//
///
////
/////
/**************************************************************************

                                BLINK LED

This example is about blinking a led connected to GPIO2 which is pin 2 on 40pin
expansion header. GPIO2 maps to PH6 which means GPIOH pin 6.

GPIOH is connected to ABH4 so first thing to do is to enable clock for GPIOH via
RCC on ABH4.

In order to enable a GPIO peripheral, it should be enabled (clocked) via the RCC
(Reset and Clock Control) unit. In the datasheet section 10.8.137 we find that
the AHB4ENSETR (AHB1 peripheral clock enable set register) is responsible to
turn GPIO banks on or off.

Once this is done we should set mode for pin 6 to output so we can drive led.
To set pin 6 to output we need to write 1 on 6th bit on 11.4.1 GPIOH mode
register.

Then to drive pin 6 high we write 1 to 6th bit of GPIOH bit set/reset register.
To drive pin 6 low we write 22nd bit of GPIOH bit set/reset register.

**************************************************************************/
///
//

#include <stdint.h>

#include "rcc.h"
#include "uart.h"
#include "gpio.h"

/* Table 9. Register boundary addresses */
#define RCC_BASE (0x50000000U)

/* 10.8.137 RCC non-secure AHB4 peripheral enable set register */
#define RCC_MP_NS_AHB4ENSETR (*(volatile uint32_t *)(RCC_BASE + 0x770))
/* 10.8.138 RCC non-secure AHB4 peripheral clear register */
#define RCC_MP_NS_AHB4ENCLRR (*(volatile uint32_t *)(RCC_BASE + 0x774))

void wait() { uint32_t i = 0x10000000; while (i--) {(void)i;}}

void print_pin(struct gpio *gpio, uint8_t pin) {
  if (gpio_get_pin(gpio,  pin)){
    write_to_uart('H');    
  } else {
    write_to_uart('L');    
  }
}

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
