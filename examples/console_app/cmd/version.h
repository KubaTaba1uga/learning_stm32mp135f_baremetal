#ifndef VERSION_H
#define VERSION_H

#include <stdint.h>

#include "stdlib.h"

#ifndef VERSION
#error "No version specified"
#endif

static inline int __cmd_version(int argc, char *argv[]) {
  puts(VERSION);
  return 0;
}

#endif
