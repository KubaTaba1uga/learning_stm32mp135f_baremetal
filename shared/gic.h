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
  volatile uint32_t CPENDSGIR[4]; // Clear pengin interrupt
  volatile uint32_t SPENDSGIR[4]; // Set/read pending interrupt
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

static inline void gicd_init(struct gicd *gicd) {
  BITS_SET(gicd->CTLRNS, 0, 1, 0);

  BITS_SET(gicd->TYPER, 0b00000101, 0xFF, 0);
  BITS_SET(gicd->TYPER, 0b111111, 0b111111, 11);

  BITS_SET(gicd->IIDR, 0b00000001, 0xFF, 24);
  BITS_SET(gicd->IIDR, 0b00000001010000111011, 0b11111111111111111111, 0);

  for (uint8_t i = 0; i < sizeof(gicd->IGROUPR) / sizeof(uint32_t); i++) {
    gicd->IGROUPR[i] = 0;
  }

  BITS_SET(gicd->ISENABLER[0], 0xFFFF, 0xFFFF, 16);
  BITS_SET(gicd->ISENABLER[0], 0, 0b1111111, 25);
  for (uint8_t i = 1; i < sizeof(gicd->IGROUPR) / sizeof(uint32_t); i++) {
    gicd->ISENABLER[i] = 0;
  }

  BITS_SET(gicd->ICENABLER[0], 0xFFFF, 0xFFFF, 16);
  BITS_SET(gicd->ICENABLER[0], 0, 0b1111111, 25);
  for (uint8_t i = 1; i < sizeof(gicd->IGROUPR) / sizeof(uint32_t); i++) {
    gicd->ICENABLER[i] = 0;
  }

  for (uint8_t i = 0; i < sizeof(gicd->ISPENDR) / sizeof(uint32_t); i++) {
    gicd->ISPENDR[i] = 0;
  }

  for (uint8_t i = 0; i < sizeof(gicd->ICPENDR) / sizeof(uint32_t); i++) {
    gicd->ICPENDR[i] = 0;
  }

  for (uint8_t i = 0; i < sizeof(gicd->ISACTIVER) / sizeof(uint32_t); i++) {
    gicd->ISACTIVER[i] = 0;
  }

  for (uint8_t i = 0; i < sizeof(gicd->ICACTIVER) / sizeof(uint32_t); i++) {
    gicd->ICACTIVER[i] = 0;
  }

  for (uint8_t i = 0; i < sizeof(gicd->IPRIORITYR) / sizeof(uint32_t); i++) {
    BITS_SET(gicd->IPRIORITYR[i], 0, 0b11111, 3);
    BITS_SET(gicd->IPRIORITYR[i], 0, 0b11111, 11);
    BITS_SET(gicd->IPRIORITYR[i], 0, 0b11111, 19);
    BITS_SET(gicd->IPRIORITYR[i], 0, 0b11111, 27);
  }

  for (uint8_t i = 8; i < sizeof(gicd->ITARGETSR) / sizeof(uint32_t); i++) {
    BITS_SET(gicd->ITARGETSR[i], 0, 0b11, 0);
    BITS_SET(gicd->ITARGETSR[i], 0, 0b11, 8);
    BITS_SET(gicd->ITARGETSR[i], 0, 0b11, 16);
    BITS_SET(gicd->ITARGETSR[i], 0, 0b11, 24);
  }

  gicd->ICFGR[0] = 0b10101010101010101010101010101010;
  BITS_SET(gicd->ICFGR[1], 0b01010101010101, 0b11111111111111, 18);
  for (uint8_t i = 2; i < sizeof(gicd->ICFGR) / sizeof(uint32_t); i++) {
    gicd->ICFGR[i] = 0b01010101010101010101010101010101;
  }

  BITS_SET(gicd->PPISR, 0, 0b1111111, 9);

  for (uint8_t i = 0; i < sizeof(gicd->SPISR) / sizeof(uint32_t); i++) {
    gicd->SPISR[i] = 0;
  }

  for (uint8_t i = 8; i < sizeof(gicd->CPENDSGIR) / sizeof(uint32_t); i++) {
    BITS_SET(gicd->CPENDSGIR[i], 0, 0b11, 0);
    BITS_SET(gicd->CPENDSGIR[i], 0, 0b11, 8);
    BITS_SET(gicd->CPENDSGIR[i], 0, 0b11, 16);
    BITS_SET(gicd->CPENDSGIR[i], 0, 0b11, 24);
  }
  
  for (uint8_t i = 8; i < sizeof(gicd->SPENDSGIR) / sizeof(uint32_t); i++) {
    BITS_SET(gicd->SPENDSGIR[i], 0, 0b11, 0);
    BITS_SET(gicd->SPENDSGIR[i], 0, 0b11, 8);
    BITS_SET(gicd->SPENDSGIR[i], 0, 0b11, 16);
    BITS_SET(gicd->SPENDSGIR[i], 0, 0b11, 24);
  }

  gicd->PIDR0 = 0b1001;  
  gicd->PIDR1 = 0b00101101;
  gicd->PIDR2 = 0b110101;
  gicd->PIDR3 = 0;
  gicd->PIDR4 = 0b001;  
  
  gicd->PIDR5 = 0;
  gicd->PIDR6 = 0;
  gicd->PIDR7 = 0;

  gicd->CIDR[0] = 0b1011;
  gicd->CIDR[1] = 0b00001111;
  gicd->CIDR[2] = 0b101;
  gicd->CIDR[3] = 0b10001101;
    
}

static inline void gicd_set_cpu0_for_usart1(struct gicd *gicd) {
  // usart1 is id=70

  // 70 = 4 * 17 + 2;
  BITS_SET(gicd->ITARGETSR[17], // Set cpu (for interrupt number 68-71)
           0b01,                // Cpu Number 0, 01 for cpu 0, 10 for cpu 1
           0b11,                // Max field value 0b11
           16                   // Start at bit 16th (select interrupt id 68+2)
  );
}

static inline void gicd_set_cpu0_for_sig0(struct gicd *gicd) {
  // usart1 is id=70

  // 70 = 4 * 17 + 2;
  BITS_SET(gicd->ITARGETSR[0], // Set cpu (for interrupt number 68-71)
           0b01,                // Cpu Number 0, 01 for cpu 0, 10 for cpu 1
           0b11,                // Max field value 0b11
           0                   // Start at bit 16th (select interrupt id 68+2)
  );
}


static inline void gicd_set_priority_for_usart1(struct gicd *gicd) {
  // usart1 is id=70

  // 70 = 4 * 17 + 2;
  BITS_SET(gicd->IPRIORITYR[17], // Set interrupt priority
           0,                    // Set maximum priority
           0b11111000,           // Max field value 0b11111000
           16                    // Start at bit 16th
  );
}

static inline void gicd_enable_usart1(struct gicd *gicd) {
  // usart1 is id=70
  /* BIT_SET(GICD->CPENDSGIR[0], 0); */
  BIT_SET(gicd->IGROUPR[2], // Use group1 for usart1
          6);

  // 70 = 16 * 4 + 6;
  BITS_SET(gicd->ICFGR[4], 0b00, 0b11,
           12); // Set level triggered interrupt

  // 70 = 32 * 2 + 6;
  BIT_SET(gicd->ISENABLER[2], // Enable interrupt handling for usart 1
          6);
}

static inline void gicc_init(struct gicc*gicc){
  BIT_CLEAR(gicc->CTLRNS, 0);
  BIT_CLEAR(gicc->CTLRNS, 5);
  BIT_CLEAR(gicc->CTLRNS, 6);
  BIT_CLEAR(gicc->CTLRNS, 9);

  BITS_SET(gicc->PMR, 0, 0b11111, 3);

  BITS_SET(gicc->BPRNS, 0b011, 0b111, 0);

  BITS_SET(gicc->IAR, 0b11111111110, 0b11111111111, 0);

  BITS_SET(gicc->RPR, 0b11111, 0b11111, 3);

  BITS_SET(gicc->HPPIR, 0b11111111110, 0b11111111111, 0);

  BITS_SET(gicc->ABPR, 0b110, 0b111, 0);

  BITS_SET(gicc->AIAR, 0b11111111110, 0b11111111111, 0);

  BITS_SET(gicc->AHPPIR, 0b11111111110, 0b11111111111, 0);

  gicc->APR0 = 0;
  gicc->NSAPR0 = 0;

  gicc->IIDR = 0b110111000101000010000001000000;  
  }


static inline void gicc_set_pmr(struct gicc *gicc) {
  BITS_SET(gicc->PMR, 0xFF, 0xFF, 3);
}

static inline void gicc_enable_cpu(struct gicc *gicc) {
  BIT_SET(gicc->CTLRNS, 0); // Enable group 0 interrupt for cpu 0
  BIT_SET(gicc->CTLRNS, 1); // Enable group 1 interrupt for cpu 0                            // 
  BIT_SET(gicc->CTLRNS, 9); // Do not require DIR for ack, only EOIR
}

#endif // GIC_H
