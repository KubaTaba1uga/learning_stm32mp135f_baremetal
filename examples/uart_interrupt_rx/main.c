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
#include <stdint.h>

#define GICD_BASE   0xA0021000u  // GIC Distributor
#define GICC_BASE   0xA0022000u  // GIC CPU Interface

#define GICD_CTLR       0x000u
#define GICD_ISENABLER0 0x100u
#define GICD_SGIR 0xF00u

#define GICC_CTLR  0x000u
#define GICC_PMR   0x004u

static inline void wr32(uintptr_t addr, uint32_t val) { *(volatile uint32_t *)addr = val; }
static inline void dsb(void){ __asm__ volatile("dsb sy" ::: "memory"); }
static inline void isb(void){ __asm__ volatile("isb" ::: "memory"); }

void gic_enable_sgis(void)
{
    /* 1) Disable CPU interface and Distributor */
    wr32(GICC_BASE + GICC_CTLR, 0x00000000u);
    dsb(); isb();
    wr32(GICD_BASE + GICD_CTLR, 0x00000000u);
    dsb(); isb();

    GICD->CPENDSGIR[0] = 0xFFFFFFFF;
    GICD->CPENDSGIR[1] = 0xFFFFFFFF;
    GICD->CPENDSGIR[2] = 0xFFFFFFFF;
    GICD->CPENDSGIR[3] = 0xFFFFFFFF;

    /* 2) Enable SGIs 0..15 (set bits 0..15). 
          If you really want 0..16 inclusive, use 0x0001FFFFu instead. */
    wr32(GICD_BASE + GICD_ISENABLER0, 0x0000FFFFu);   // SGI0..15 enabled

    /* (Recommended) Allow all priorities through the CPU interface */
    wr32(GICC_BASE + GICC_PMR, 0xFFu);

    /* 3) Re-enable Distributor (Grp0 + Grp1) and CPU interface (Grp0 + Grp1) */
    wr32(GICD_BASE + GICD_CTLR, (1u << 0) | (1u << 1));   // ENABLEGRP0 | ENABLEGRP1
    dsb(); isb();
    wr32(GICC_BASE + GICC_CTLR, (1u << 0) | (1u << 1));   // EnableGrp0 | EnableGrp1
    dsb(); isb();
}

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
    /* uart_set_ctrl(USART1, UART_CR1_ALT_RXFNEIE, 1U); // Enable IRQ */
    uart_set_ctrl(USART1, UART_CR1_ALT_RE, 1U);      // Enable reciver
    uart_set_ctrl(USART1, UART_CR1_ALT_TE, 1U);      // Enable transiver
    uart_set_ctrl(USART1, UART_CR1_ALT_UE, 1U);      // Enable uart
  }

  { // Write banner to USART1
    print_banner(USART1);
  }

  { // Configure General interrupt controller
    /* gicd_init(GICD); */
    gicd_set_cpu0_for_usart1(GICD);
    gicd_set_priority_for_usart1(GICD);
    gicd_enable_usart1(GICD);

    /* gicc_init(GICC); */


    gicc_set_pmr(GICC);
    gicc_enable_cpu(GICC);
  }
  
  if (GICD->ISENABLER[0] & 0b1) {
    uart_write_str(UART4, "SIG0=enabled");
  } else {
    uart_write_str(UART4, "SIG0=disabled");
  }
  uart_write_str(UART4, "\r\n");

  if (GICD->ISENABLER[0] & 0b10) {
    uart_write_str(UART4, "SIG1=enabled");
  } else {
    uart_write_str(UART4, "SIG1=disabled");
  }
  uart_write_str(UART4, "\r\n");

  
  if (GICD->ISENABLER[2] & (1U<<6)) {
    uart_write_str(UART4, "USART1=enabled");
  } else {
    uart_write_str(UART4, "USART1=disabled");
  }
  uart_write_str(UART4, "\r\n");

  GICD->ISENABLER[2] = (1U<<6)  ;
  if (GICD->ISENABLER[2] & (1U<<6)) {
    uart_write_str(UART4, "USART1=enabled");
  } else {
    uart_write_str(UART4, "USART1=disabled");
  }
  uart_write_str(UART4, "\r\n");

  if (GICD->SPENDSGIR[0] & 0b1) {
    uart_write_str(UART4, "SIG0=pending");
  } else {
    uart_write_str(UART4, "SIG0=not pending");
  }
  uart_write_str(UART4, "\r\n");
  
  /* GICD->ISACTIVER[0] = 0b1; */
  if (GICD->ISACTIVER[0] & 0b1) {
    uart_write_str(UART4, "SIG0=active");
  } else {
    uart_write_str(UART4, "SIG0=not active");
  }
  uart_write_str(UART4, "\r\n");

  if (GICD->IGROUPR[0] & 0b1) {
    uart_write_str(UART4, "SIG0=group1");
  } else {
    uart_write_str(UART4, "SIG0=group0");
  }
  uart_write_str(UART4, "\r\n");
  
  uint32_t secure = (*(uint32_t *)(0x5C007000 + 0x14)) & 0b11;
  switch (secure) {
  case 0b00:
    uart_write_str(UART4, "USART1=read secure and write secure");
    break;
  case 0b01:
    uart_write_str(UART4, "USART1=read non-secure and write secure");
    break;
  case 0b10:
    uart_write_str(UART4, "USART1=reserved");
    break;
  case 0b11:
    uart_write_str(UART4, "USART1=read non-secure and write non-secure");
    break;
  }


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
  uint32_t iar = GICC->IAR;
  uint32_t id  = iar & 0x3FFu;          // INTID in [9:0]

  uart_write_str(UART4, "IRQ start\r\n");
  
  // 1023 == spurious on GICv2; just return
  if (id == 1023u){
    uart_write_str(UART4, "IRQ=invalid\r\n");
    return;    
    } 

  if (id < 16u) {                        // SGI (0..15)
    // handle SGI 'id' here if you want to log/branch
    GICC->EOIR = iar;                    // write back EXACT IAR value
    GICC->DIR = id;                      // optional but fine on v2 1N model
    if (id==0){
    uart_write_str(UART4, "IRQ=SGI0\r\n");    
    } else {
    uart_write_str(UART4, "IRQ=SGI1\r\n");          
    }

    return;
  }

  if (id == 70u) {                       // USART1 (SPI)
  uart_write_str(UART4, "IRQ=USART1\r\n");
    (void)uart_read_char(USART1);        // clear UART condition
    GICC->EOIR = iar;                    // EOI with full IAR
    return;
  }

  uart_write_str(UART4, "IRQ=other\r\n");
  
  // Other interrupts (if any)
  GICC->EOIR = iar;
}
