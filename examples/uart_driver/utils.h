#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

static inline void *memcpy(void *dest, const void *src, uint32_t count) {
  char *dst = (char *)dest;
  while (count-- > 0) {
    dst[count] = ((char *)src)[count];
  }

  return dst;
}

static inline uint32_t strlen(const char *str) {
  uint32_t i = 0;
  for (; str[i] != 0; i++) {
  }
  return i;
}

static inline void *memset(void *dest, int ch, uint32_t count) {
  char *dst = (char *)dest;
  while (count-- > 0) {
    dst[count] = ch;
  }

  return dst;
}

#endif // UTILS_H
