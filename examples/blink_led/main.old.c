//
///
////
/////
/**************************************************************************

                                BLINK LED

This example is about blinking a led connected to GPIO2 which is pin 2 on 40pin
expansion header.

GPIO2 maps to PH6 which means GPIOH pin 6.

In order to enable a GPIO peripheral, it should be enabled (clocked) via the RCC (Reset and Clock Control) unit. In the datasheet section 7.3.10 we find that the AHB1ENR (AHB1 peripheral clock enable register) is responsible to turn GPIO banks on or off.


**************************************************************************/
///
//

#include <stdint.h>
#include <stdint.h>

#define RCC_MP_AHB4ENSETR   (*(volatile uint32_t *)0x50000A28U) // GPIO clocks (A..K)
#define GPIOH_BASE          (0x50009000U)
#define GPIOH_MODER         (*(volatile uint32_t *)(GPIOH_BASE + 0x00))
#define GPIOH_PUPDR         (*(volatile uint32_t *)(GPIOH_BASE + 0x0C))
#define GPIOH_BSRR          (*(volatile uint32_t *)(GPIOH_BASE + 0x18))

static void delay(volatile uint32_t t){ while(t--) {}; }

int main(void) {
    // 1) Enable GPIOH clock (bit 7)
    RCC_MP_AHB4ENSETR = (1U << 7);

    // 2) PH6: output (01b at bits 13:12), no pull (00b at bits 13:12)
    GPIOH_MODER = (GPIOH_MODER & ~(3U << (6*2))) | (1U << (6*2));
    GPIOH_PUPDR = (GPIOH_PUPDR & ~(3U << (6*2)));

    // 3) Active-low control via BSRR (write-only):
    //    ON  = reset bit (6+16)
    //    OFF = set bit (6)

    // Turn OFF (drive high)
    GPIOH_BSRR = (1U << 6);
    
    delay(10000000);
    // Turn ON (drive low)
    GPIOH_BSRR = (1U << (6 + 16));


    while (1) {
        /* // Blink */
        /* GPIOH_BSRR = (1U << (6 + 16));  // ON */
        /* delay(4000000); */
        /* GPIOH_BSRR = (1U << 6);         // OFF */
        /* delay(4000000); */
    }
}
