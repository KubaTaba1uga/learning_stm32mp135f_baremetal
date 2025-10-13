//
///
////
/////
/**************************************************************************

                                LINKER SCRIPT

This example is about creating minimal linker script working on STM32MP135.

From manual we can read that DDR memory start at 0xC0000000 and end at
 0xE0000000. Our goal is to put all program to DDR and start it there.
We pick 0xC0300000 in case uboot uses some data rigth after 0xC0000000.

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

int main(void) {
  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }
  write_to_register(USART_TDR, '-');

  for (int32_t i = 0; word[i] != 0; i++) {
    while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
    }
    write_to_register(USART_TDR, word[i]);
  }

  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }
  write_to_register(USART_TDR, '-');

  while (1) {
  }
}
