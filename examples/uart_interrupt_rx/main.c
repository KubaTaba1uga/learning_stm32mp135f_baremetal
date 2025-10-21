//
///
////
/////
/**************************************************************************

                                UART INTERRUPT IO

First to configure interrupt we need to set interrupt handler address in
vector table.

When an ARM MCU boots, it reads a so-called "vector table" from the beginning of
flash memory. A vector table is a concept common to all ARM MCUs. That is an
array of 32-bit addresses of interrupt handlers. First 16 entries are reserved
by ARM and are common to all ARM MCUs. The rest of interrupt handlers are
specific to the given MCU - these are interrupt handlers for peripherals.

According Table 111. STM32MP13xx interrupt mapping for Cortex®-A7 GIC:
- USART1 IRQ id is 70

To know IRQ id read GICC_IAR register.

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
extern void _STACK_START_(void);
extern void _Reset(void);
void default_interrupt_handler(void);
void dummy_interrupt_handler(void);
__attribute__((section(".vectors_table"))) void (*const tab[8])(void) = {
    _Reset,                    // 0x00: Entrypoint
    dummy_interrupt_handler,   // 0x04: Undefined instruction
    dummy_interrupt_handler,   // 0x08: Software interrupt (SWI/SVC)
    dummy_interrupt_handler,   // 0x0C: Prefetch abort
    dummy_interrupt_handler,   // 0x10: Data abort
    dummy_interrupt_handler,   // 0x14: Reserved
    default_interrupt_handler, // 0x18: IRQ interrupt
    dummy_interrupt_handler,   // 0x1C: FIQ interrupt
};

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
    uart_set_ctrl(USART1, UART_CR1_ALT_RXFNEIE, 1U); // Enable IRQ
    uart_set_ctrl(USART1, UART_CR1_ALT_RE, 1U);      // Enable reciver
    uart_set_ctrl(USART1, UART_CR1_ALT_TE, 1U);      // Enable transiver
    uart_set_ctrl(USART1, UART_CR1_ALT_UE, 1U);      // Enable uart
  }

  { // Write banner to USART1
    print_banner(USART1);
  }

  /* Distributor (GICD):
      Set target CPU (usually CPU0) for USART1’s INTID.
      Set priority and trigger type (per RM).
      Enable Enable GIC interrupt for id=70 via (GICD_ISENABLERx)

     CPU Interface(GICC):
      Set PMR(priority mask) so your chosen priority is not masked.
      Set BPR(binary point) if you use preemption.
      Enable the CPU interface.
  */

  uart_write_str(USART1, "Done");
  // Configure GPIOH for output

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

void default_interrupt_handler(void) { uart_write_char(UART4, 'I'); };

void dummy_interrupt_handler(void) {};
