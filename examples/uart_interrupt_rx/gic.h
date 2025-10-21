#ifndef GIC_H
#define GIC_H

#include <stdint.h>

struct gic {
  union {
    volatile uint32_t CTLR;
    volatile uint32_t CTLRNS;
  };

  volatile uint32_t TYPER;
  volatile uint32_t IIDR;
  volatile uint32_t IGROUPR[6];
  volatile uint32_t ISENABLER[6];
  volatile uint32_t ICENABLER[6];
  volatile uint32_t ISPENDR[6];
  volatile uint32_t ISACTIVER[6];
  volatile uint32_t ICACTIVER[6];
  volatile uint32_t IPRIORITYR[48];
  volatile uint32_t ITARGETSR[48];
  volatile uint32_t ICFGR[12];
  volatile uint32_t PPISR;
  volatile uint32_t SPISR[5];
  volatile uint32_t SGIR;
  volatile uint32_t CPENDSGIR[4];
  volatile uint32_t SPENDSGIR[4];
  volatile uint32_t PIDR4;
  volatile uint32_t PIDR[3];
  volatile uint32_t PIDR0;
  volatile uint32_t PIDR1;
  volatile uint32_t PIDR2;
  volatile uint32_t PIDR3;
  volatile uint32_t CIDR0;
  volatile uint32_t CIDR1;
  volatile uint32_t CIDR2;
  volatile uint32_t CIDR3;
};

#endif // GIC_H
