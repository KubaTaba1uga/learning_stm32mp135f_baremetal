#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <cstring>
#include <stdint.h>

/*
FR1. --Clocking & Reset--

- Enable peripheral clock in RCC.
- Assert/deassert peripheral reset if applicable.
- Derive UART kernel clock frequency; expose it via `uart_get_srcclk()`.

*/

struct UartDriver {
  char hid[8];        // Human readable id
  uint32_t base_addr; // Base address of memory mapped io
};

static inline int UartDriver_init(const char *hid, uint32_t base_addr,
                                  struct UartDriver *driver) {
  *driver = (struct UartDriver){
      .base_addr = base_addr,
  };

  memcpy(driver->hid, hid, strlen(hid));

  return 0;
};

#endif // UART_DRIVER_H
