#ifndef GIC_H
#define GIC_H

#include "common.h"
#include <stdint.h>

struct gicd {
  union {
    volatile uint32_t CTLR;
    volatile uint32_t CTLRNS;
  };
  volatile uint32_t TYPER;
  volatile uint32_t IIDR;
  volatile uint8_t _reserved[114];
  volatile uint32_t IGROUPR[6];
  volatile uint8_t _reserved1[102];
  volatile uint32_t ISENABLER[6];
  volatile uint8_t _reserved2[102];
  volatile uint32_t ICENABLER[6];
  volatile uint8_t _reserved3[102];
  volatile uint32_t ISPENDR[6];
  volatile uint8_t _reserved4[102];
  volatile uint32_t ICPENDR[6];
  volatile uint8_t _reserved5[102];
  volatile uint32_t ISACTIVER[6];
  volatile uint8_t _reserved6[102];
  volatile uint32_t ICACTIVER[6];
  volatile uint8_t _reserved7[102];
  volatile uint32_t IPRIORITYR[48];
  volatile uint8_t _reserved8[832];
  volatile uint32_t ITARGETSR[48];
  volatile uint8_t _reserved9[832];
  volatile uint32_t ICFGR[12];
  volatile uint8_t _reserved10[208];
  volatile uint32_t PPISR;
  volatile uint32_t SPISR[5];
  volatile uint8_t _reserved11[488];
  volatile uint32_t SGIR;
  volatile uint8_t _reserved12[12];
  volatile uint32_t CPENDSGIR[4];
  volatile uint32_t SPENDSGIR[4];
  volatile uint8_t _reserved13[160];
  volatile uint32_t PIDR4;
  volatile uint32_t PIDR5;
  volatile uint32_t PIDR6;
  volatile uint32_t PIDR7;
  volatile uint32_t PIDR0;
  volatile uint32_t PIDR1;
  volatile uint32_t PIDR2;
  volatile uint32_t PIDR3;
  volatile uint32_t CIDR[4];
};

struct gicc {
  union {
    volatile uint32_t CTLR;
    volatile uint32_t CTLRNS;
  };
  volatile uint32_t PMR;
  volatile uint32_t BPR;
  volatile uint32_t BPRNS;
  volatile uint32_t IAR;
  volatile uint32_t EOIR;
  volatile uint32_t RPR;
  volatile uint32_t HPPIR;
  volatile uint32_t ABPR;
  volatile uint32_t AIAR;
  volatile uint32_t AEOIR;
  volatile uint32_t AHPPIR;
  volatile uint8_t _reserved[160];
  volatile uint32_t APR0;
  volatile uint8_t _reserved1[12];
  volatile uint32_t NSAPR0;
  volatile uint8_t _reserved2[24];
  volatile uint32_t IIDR;
  volatile uint8_t _reserved3[3840];
  volatile uint32_t DIR;
};

#define GICD ((struct gicd *)0xA0021000)
#define GICC ((struct gicc *)0xA0022000)

static inline void gicd_set_cpu0_for_usart1(struct gicd *gicd) {
  // usart1 is id=70

  // 70 = 4 * 17 + 2;
  BITS_SET(gicd->ITARGETSR[17], // Set cpu (for interrupt number 68-71)
           0b01,                   // Cpu Number 0, 01 for cpu 0, 10 for cpu 1
           0b11,                // Max field value 0b11
           16                   // Start at bit 16th (select interrupt id 68+2)
  );
}

static inline void gicd_set_priority_for_usart1(struct gicd *gicd) {
  // usart1 is id=70

  // 70 = 4 * 17 + 2;
  BITS_SET(gicd->IPRIORITYR[17], // Set interrupt priority
           0,           // Set maximum priority
           0b11111000,           // Max field value 0b11111000
           16                    // Start at bit 16th
  );
}

static inline void gicd_enable_usart1(struct gicd *gicd) {
  // usart1 is id=70

  // 70 = 16 * 4 + 6;
  /* BITS_SET(gicd->ICFGR[4], 0b00, 0b11,   */
  /* 	   12); // Set edged triggered interrupt */

  // 70 = 32 * 2 + 6;
  BIT_SET(gicd->ISENABLER[2], // Use x=2

          6);

  BIT_SET(gicd->IGROUPR[2], // Use group1 for usart1
          6);

}

static inline void gicc_set_pmr(struct gicc *gicc) {
  BITS_SET(gicc->PMR, 0b11111, 0b11111, 3);
}

static inline void gicc_enable_cpu(struct gicc *gicc) {
  BIT_SET(gicc->CTLRNS, 0);
  BIT_SET(gicc->CTLRNS, 5);  
  BIT_SET(gicc->CTLRNS, 9);  
}



#endif // GIC_H
