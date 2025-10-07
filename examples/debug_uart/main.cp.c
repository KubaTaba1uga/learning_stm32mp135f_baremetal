//
///
////
/////
/**************************************************************************

                                DEBUG UART

This example is pabout creating minimal configuration required to used a
CPU IP block. We are beginning with UART because it is relativly simple.

Getting started:
1. Open manual at `Table 9. Register boundary addresses`. Next to peripheral
   you will have first address that peripheral starts with. This is base
   address of a peripheral. All registers addresses will be offset to the
   base address.

2. Open manual at `49.8 USART registers` this section wich tell us what kind
   of registers device has available and what they are doing. When you found
   a mention of any UART register this is section where the register itself
   will be described in details.

3. Open manual at `Character transmission procedure`, which looks as follows:
       1. Program the M bits in USART_CR1 to define the word length.
       2. Select the desired baud rate using the USART_BRR register.
       3. Program the number of stop bits in USART_CR2.
       4. Enable the USART by writing the UE bit in USART_CR1 register to 1.
       5. Select DMA enable (DMAT) in USART_CR3 if multibuffer communication
          must take place. Configure the DMA register as explained in
          Section 49.5.19: Continuous communication using USART and DMA.
       6. Set the TE bit in USART_CR1 to send an idle frame as first
          transmission.
       7. Write the data to send in the USART_TDR register. Repeat this for each
          data to be transmitted in case of single buffer.
          - When FIFO mode is disabled, writing a data to the USART_TDR clears
            the TXE flag.
          - When FIFO mode is enabled, writing a data to the USART_TDR adds one
            data to the TXFIFO. Write operations to the USART_TDR are performed
            when TXFNF flag is set. This flag remains set until the TXFIFO is
            full.
       8. When the last data is written to the USART_TDR register,
          wait until TC = 1.
          - When FIFO mode is disabled, this indicates that the transmission of
            the last frame is complete.
          - When FIFO mode is enabled, this indicates that both TXFIFO and shift
            register are empty.



Now you should have all building blocks to understand how this example was
built.

DISCLAIMER: Hardware registers must be declared volatile, otherwise the compiler
may optimize away reads/writes.

COMPILE:
./../../third_party/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-gcc
-Os -ffreestanding -fno-builtin -nostdlib -nostartfiles   -mcpu=cortex-a7 -marm
-Wl,-e,_start -Wl,-Ttext=0x0 -Wl,--build-id=none -o uart4_A.elf main.c



**************************************************************************/
///
//

#include <stdint.h>

#define UART4_BASE                                                             \
  0x40010000UL // UART4 base address
               // USART control register 1
#define USART_CR1 (volatile uint32_t *)(UART4_BASE + 0x00)

// USART control register 2
#define USART_CR2 (volatile uint32_t *)(UART4_BASE + 0x04)

// USART baud rate register
#define USART_BRR (volatile uint32_t *)(UART4_BASE + 0x0C)

// USART transmit data register
#define USART_TDR (volatile uint32_t *)(UART4_BASE + 0x28)

// USART interrupt and status register
#define USART_ISR (volatile uint32_t *)(UART4_BASE + 0x1C)

#define USART_CR1_UE (1) // USART enable
// This is first bit of register so 0b1.

#define USART_CR1_TE (1 << 3) // Transmit enable
//  This is 4th bit of register, so 0b1000.

#define USART_ISR_TC (1 << 5) // Transfer complete
// This is 6th bit of register, so 0b100000.

#define USART_ISR_TXE (1 << 6) // Transmit data register empty

#define USART_CR1_M0 (1 << 11) // World length part 1
#define USART_CR1_M1 (1 << 28) // World length part 2

#define USART_CR2_STOP0 (1 << 11) // Stop bits part 1
#define USART_CR2_STOP1 (1 << 12) // Stop bits part 2

static void set_bit_in_register(volatile uint32_t *reg, uint32_t bit) {
  *reg |= bit;
}

static void unset_bit_in_register(volatile uint32_t *reg, uint32_t bit) {
  *reg &= ~bit;
}

static uint32_t read_bit_in_register(volatile uint32_t *reg, uint32_t bit) {
  return *reg & bit;
}

static void write_to_register(volatile uint32_t *reg, uint32_t value) {
  *reg = value;
}

void _start(void) {
  /* 1. Program the M bits in USART_CR1 to define the word length. */
  // We set 8 bit word size
  /* unset_bit_in_register(USART_CR1, USART_CR1_M0); */
  /* unset_bit_in_register(USART_CR1, USART_CR1_M1); */

  /* 2. Select the desired baud rate using the USART_BRR register. */
  // We set baud rate 115200
  /* write_to_register(USART_BRR, 115200); */

  /* 3. Program the number of stop bits in USART_CR2.   */
  // We are seting one stop bit
  /* unset_bit_in_register(USART_CR2, USART_CR2_STOP0); */
  /* unset_bit_in_register(USART_CR2, USART_CR2_STOP1); */

  /* 4. Enable the USART by writing the UE bit in USART_CR1 register to 1.   */
  while (!read_bit_in_register(USART_ISR, USART_ISR_TXE)) {
  }

  write_to_register(USART_TDR, 'A');
  write_to_register(USART_TDR, 'A');
}
