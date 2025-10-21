//
///
////
/////
/**************************************************************************

                                UART INTERRUPT IO

First to configure interrupt we need to set interrupt handler address in
vector table.

When an ARM MPU executes code first thing it expect is .text section with
entrypoint. However one can set there also interrupt handlers branching
and set VBAR to point to that address, from now on the beginning of the
program memory serves also as vector table for the progam.

According Table 111. STM32MP13xx interrupt mapping for Cortex-A7 GIC:
- USART1 IRQ id is 70

GIC is composed of few elements, we are interested in distributor and CPU
intrface. Minimal configuration required for interrupt handling is:
    - Distributor (GICD):
      Set target CPU (usually CPU0) for USART1’s INTID.
      Set priority and trigger type (per RM).
      Enable Enable GIC interrupt for id=70 via (GICD_ISENABLERx)

    - CPU Interface(GICC):
      Set PMR(priority mask) so your chosen priority is not masked.
      Set BPR(binary point) if you use preemption.
      Enable the CPU interface.

Once interrupt is delivered we keen to know IRQ id to do so read GICC_IAR
register.

Once interrupt is handled we need to acknowledghe end of interrupot via writing
value wich we got from IAR into GICC_EOIR.

**************************************************************************/
///
//

#include "common.h"
#include "gic.h"
#include "gpio.h"
#include "rcc.h"
#include "uart.h"

#include <stdint.h>

const char word[] = "Hello friend";
void print_banner(struct uart *uart);
void default_interrupt_handler(void);

int main(void) {
  uart_write_str(UART4, __func__);
  uart_write_str(UART4, "\r\n");
  
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

  { // Configure General interrupt controller
    gicd_set_cpu0_for_usart1(GICD);
    gicd_set_priority_for_usart1(GICD);
    gicd_enable_usart1(GICD);

    gicc_set_pmr(GICC);
    gicc_enable_cpu(GICC);
  }

  uart_write_str(USART1, "Done");
  while (1) {
  }

  return 0;
}

void print_banner(struct uart *uart) {
  uart_write_str(UART4, __func__);
  uart_write_str(UART4, "\r\n");
  
  for (uint8_t i = 0; i < 32; i++) {
    uart_write_str(uart, "\r\n");
  }

  uart_write_char(uart, '-');
  uart_write_str(uart, word);
  uart_write_char(uart, '-');
  uart_write_str(uart, "\r\n");
}

void default_interrupt_handler(void) {
  uart_write_str(UART4, __func__);
  uart_write_str(UART4, "\r\n");
  
  uart_write_char(UART4, 'I');

  uint32_t intrrpt_id = GICC->AIAR;

  uart_read_char(USART1);
  /* uint32_t i= 0xFFFF; */
  /* while (i--) { */
  /* } */

  uart_write_char(UART4, 'X');

  GICC->AEOIR = intrrpt_id;
  /* GICC->DIR = intrrpt_id;   */
};
