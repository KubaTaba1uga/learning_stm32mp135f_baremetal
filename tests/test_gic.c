#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "gic.h"
#include "unity.h"

void test_gic_regs_mapping() {
  printf("offsetof CTLR: %lx\n", offsetof(struct gic, CTLR));
  TEST_ASSERT_EQUAL_HEX(0x00, offsetof(struct gic, CTLR));

  printf("offsetof CTLRNS: %lx\n", offsetof(struct gic, CTLRNS));
  TEST_ASSERT_EQUAL_HEX(0x00, offsetof(struct gic, CTLRNS));

  printf("offsetof IGROUPR: %lx\n", offsetof(struct gic, IGROUPR));
  TEST_ASSERT_EQUAL_HEX(0x080, offsetof(struct gic, IGROUPR));

  printf("offsetof ISENABLER: %lx\n", offsetof(struct gic, ISENABLER));
  TEST_ASSERT_EQUAL_HEX(0x100, offsetof(struct gic, ISENABLER));

  printf("offsetof ICENABLER: %lx\n", offsetof(struct gic, ICENABLER));
  TEST_ASSERT_EQUAL_HEX(0x180, offsetof(struct gic, ICENABLER));

  printf("offsetof ISPENDR: %lx\n", offsetof(struct gic, ISPENDR));
  TEST_ASSERT_EQUAL_HEX(0x200, offsetof(struct gic, ISPENDR));

  printf("offsetof ICPENDR: %lx\n", offsetof(struct gic, ICPENDR));
  TEST_ASSERT_EQUAL_HEX(0x280, offsetof(struct gic, ICPENDR));

  printf("offsetof ISACTIVER: %lx\n", offsetof(struct gic, ISACTIVER));
  TEST_ASSERT_EQUAL_HEX(0x300, offsetof(struct gic, ISACTIVER));

  printf("offsetof ICACTIVER: %lx\n", offsetof(struct gic, ICACTIVER));
  TEST_ASSERT_EQUAL_HEX(0x380, offsetof(struct gic, ICACTIVER));

  printf("offsetof IPRIORITYR: %lx\n", offsetof(struct gic, IPRIORITYR));
  TEST_ASSERT_EQUAL_HEX(0x400, offsetof(struct gic, IPRIORITYR));

  printf("offsetof ITARGETSR: %lx\n", offsetof(struct gic, ITARGETSR));
  TEST_ASSERT_EQUAL_HEX(0x800, offsetof(struct gic, ITARGETSR));

  printf("offsetof ICFGR: %lx\n", offsetof(struct gic, ICFGR));
  TEST_ASSERT_EQUAL_HEX(0xC00, offsetof(struct gic, ICFGR));

  printf("offsetof PPISR: %lx\n", offsetof(struct gic, PPISR));
  TEST_ASSERT_EQUAL_HEX(0xD00, offsetof(struct gic, PPISR));

  printf("offsetof SGIR: %lx\n", offsetof(struct gic, SGIR));
  TEST_ASSERT_EQUAL_HEX(0xF00, offsetof(struct gic, SGIR));

  printf("offsetof CPENDSGIR: %lx\n", offsetof(struct gic, CPENDSGIR));
  TEST_ASSERT_EQUAL_HEX(0xF10, offsetof(struct gic, CPENDSGIR));

  printf("offsetof PIDR4: %lx\n", offsetof(struct gic, PIDR4));
  TEST_ASSERT_EQUAL_HEX(0xFD0, offsetof(struct gic, PIDR4));
  
  printf("offsetof CIDR: %lx\n", offsetof(struct gic, CIDR));
  TEST_ASSERT_EQUAL_HEX(0xFF0, offsetof(struct gic, CIDR));
}
