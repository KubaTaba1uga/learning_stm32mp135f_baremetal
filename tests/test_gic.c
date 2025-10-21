#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "gic.h"
#include "unity.h"

void test_gicd_regs_mapping() {
  printf("offsetof CTLR: %lx\n", offsetof(struct gicd, CTLR));
  TEST_ASSERT_EQUAL_HEX(0x00, offsetof(struct gicd, CTLR));

  printf("offsetof CTLRNS: %lx\n", offsetof(struct gicd, CTLRNS));
  TEST_ASSERT_EQUAL_HEX(0x00, offsetof(struct gicd, CTLRNS));

  printf("offsetof IGROUPR: %lx\n", offsetof(struct gicd, IGROUPR));
  TEST_ASSERT_EQUAL_HEX(0x080, offsetof(struct gicd, IGROUPR));

  printf("offsetof ISENABLER: %lx\n", offsetof(struct gicd, ISENABLER));
  TEST_ASSERT_EQUAL_HEX(0x100, offsetof(struct gicd, ISENABLER));

  printf("offsetof ICENABLER: %lx\n", offsetof(struct gicd, ICENABLER));
  TEST_ASSERT_EQUAL_HEX(0x180, offsetof(struct gicd, ICENABLER));

  printf("offsetof ISPENDR: %lx\n", offsetof(struct gicd, ISPENDR));
  TEST_ASSERT_EQUAL_HEX(0x200, offsetof(struct gicd, ISPENDR));

  printf("offsetof ICPENDR: %lx\n", offsetof(struct gicd, ICPENDR));
  TEST_ASSERT_EQUAL_HEX(0x280, offsetof(struct gicd, ICPENDR));

  printf("offsetof ISACTIVER: %lx\n", offsetof(struct gicd, ISACTIVER));
  TEST_ASSERT_EQUAL_HEX(0x300, offsetof(struct gicd, ISACTIVER));

  printf("offsetof ICACTIVER: %lx\n", offsetof(struct gicd, ICACTIVER));
  TEST_ASSERT_EQUAL_HEX(0x380, offsetof(struct gicd, ICACTIVER));

  printf("offsetof IPRIORITYR: %lx\n", offsetof(struct gicd, IPRIORITYR));
  TEST_ASSERT_EQUAL_HEX(0x400, offsetof(struct gicd, IPRIORITYR));

  printf("offsetof ITARGETSR: %lx\n", offsetof(struct gicd, ITARGETSR));
  TEST_ASSERT_EQUAL_HEX(0x800, offsetof(struct gicd, ITARGETSR));

  printf("offsetof ICFGR: %lx\n", offsetof(struct gicd, ICFGR));
  TEST_ASSERT_EQUAL_HEX(0xC00, offsetof(struct gicd, ICFGR));

  printf("offsetof PPISR: %lx\n", offsetof(struct gicd, PPISR));
  TEST_ASSERT_EQUAL_HEX(0xD00, offsetof(struct gicd, PPISR));

  printf("offsetof SGIR: %lx\n", offsetof(struct gicd, SGIR));
  TEST_ASSERT_EQUAL_HEX(0xF00, offsetof(struct gicd, SGIR));

  printf("offsetof CPENDSGIR: %lx\n", offsetof(struct gicd, CPENDSGIR));
  TEST_ASSERT_EQUAL_HEX(0xF10, offsetof(struct gicd, CPENDSGIR));

  printf("offsetof PIDR4: %lx\n", offsetof(struct gicd, PIDR4));
  TEST_ASSERT_EQUAL_HEX(0xFD0, offsetof(struct gicd, PIDR4));
  
  printf("offsetof CIDR: %lx\n", offsetof(struct gicd, CIDR));
  TEST_ASSERT_EQUAL_HEX(0xFF0, offsetof(struct gicd, CIDR));
}

void test_gicc_regs_mapping() {
  printf("offsetof CTLR: %lx\n", offsetof(struct gicc, CTLR));
  TEST_ASSERT_EQUAL_HEX(0x00, offsetof(struct gicc, CTLR));

  printf("offsetof CTLRNS: %lx\n", offsetof(struct gicc, CTLRNS));
  TEST_ASSERT_EQUAL_HEX(0x00, offsetof(struct gicc, CTLRNS));

  printf("offsetof APR0: %lx\n", offsetof(struct gicc, APR0));
  TEST_ASSERT_EQUAL_HEX(0xd0, offsetof(struct gicc, APR0));
  
  printf("offsetof NSAPR0: %lx\n", offsetof(struct gicc, NSAPR0));
  TEST_ASSERT_EQUAL_HEX(0xe0, offsetof(struct gicc, NSAPR0));
  
  printf("offsetof IIDR: %lx\n", offsetof(struct gicc, IIDR));
  TEST_ASSERT_EQUAL_HEX(0xFC, offsetof(struct gicc, IIDR));
  
  printf("offsetof DIR: %lx\n", offsetof(struct gicc, DIR));
  TEST_ASSERT_EQUAL_HEX(0x1000, offsetof(struct gicc, DIR));
  
}
