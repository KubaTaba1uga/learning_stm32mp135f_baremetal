//
///
////
/////
/**************************************************************************

                                DEBUG UART

This example is about printing one char to UART4.

In our config Uboot has already configured UART so what we need to do
is just use data transfer register of UART to write a char to the peripheral.

DISCLAIMER: Hardware registers must be declared volatile, otherwise the compiler
may optimize away reads/writes.

COMPILE:
./../../third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-gcc
-Os -ffreestanding -fno-builtin -nostdlib -nostartfiles -mcpu=cortex-a7 -marm
-Wl,-e,_start -Wl,-Ttext=0x0 -Wl,--build-id=none
-o uart4_A.elf main.c


**************************************************************************/
///
//

#include <stdint.h>

// Base address cannot be cast to ptr because then all additions are treated
//  as ptrs additions not as address adition causing bugs.
#define UART4_BASE 0x40010000UL // UART4 base address

// USART transmit data register
#define USART_TDR (volatile uint32_t *)(UART4_BASE + 0x28)

// USART interrupt and status register
#define USART_ISR (volatile uint32_t *)(UART4_BASE + 0x1C)

#define USART_ISR_TXE (1 << 6) // Transmit data register empty
// This is 7th bit of register so we want 0b1000000.

static uint32_t read_bit_in_register(volatile uint32_t *reg, uint32_t bit) {
  return *reg & bit;
}

static void write_to_register(volatile uint32_t *reg, uint32_t value) {
  *reg = value;
}

void _start(void) {
  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'H');
  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'E');

  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'L');

  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'L');

  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'O');

  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, ' ');

  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'F');
  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'R');
  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'I');
  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'E');
  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'N');
  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'D');
}
