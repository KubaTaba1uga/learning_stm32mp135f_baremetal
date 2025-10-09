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

/* #define RCC_BASE 0x50000000UL // Reset and clock control base address */
/* #define RCC_AHB4_ENABLE   (volatile uint32_t *)(RCC_BASE + 0x770) // RCC Enable ABH4 Peripherals register */
/* #define ENABLE_GPIOH (1U << 7) // Enable GPIOH clock */

/* #define GPIOH_BASE 0x50009000UL // GPIOH base address */
/* #define GPIOH_MODER                                                            \ */
/*   (volatile uint32_t *)(GPIOH_BASE + 0x00) // GPIOH Moder register */
/* #define GPIOH_PULL                                                             \ */
/*   (volatile uint32_t *)(GPIOH_BASE + 0x0C) // GPIOH Pull up pull down register */
/* #define MODER_OUTPUT (1U << 11) // Set mode of PH6 to output */
/* #define PULL_UP (1U << 11)      // Set PH6 to pullup */
/* #define PULL_DOWN (1U << 10)    // Set PH6 to pulldown */

/* #define GPIOH_ODR                                                             \ */
/*   (volatile uint32_t *)(GPIOH_BASE + 0x14) // GPIOH Pull up pull down register */
/* #define ODR (1U << 6)    // Set PH6 to pulldown */
/* #define UNODR (0U)    // Set PH6 to pulldown */

/* #define GPIOH_BSRR                                                             \ */
/*   (volatile uint32_t *)(GPIOH_BASE + 0x18) */
/* #define SET (1U << 6)    // Set PH6 to pulldown */
/* #define UNSET (1U << 22)    // Set PH6 to pulldown */



/* int main(void) { */
/*   *RCC_AHB4_ENABLE = ENABLE_GPIOH; */
  
/*   *GPIOH_MODER = MODER_OUTPUT; */

/*   *GPIOH_BSRR = SET; */
/*   /\* uint32_t i = 99999999; *\/ */
/*   while (1) { */
/*   } */
/*   /\* *GPIOH_BSRR |= SET; *\/ */
  
/*   /\* *GPIOH_PULL = PULL_UP; *\/ */
/*   /\* uint32_t i = 99999999; *\/ */
/*   /\* while (i--) { *\/ */
/*   /\* } *\/ */
/*   /\* *GPIOH_PULL = PULL_DOWN; *\/ */

/*   while (1) { */
/*   } */
  
/*   return 0; */
/* } */
