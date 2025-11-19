#ifndef MYSTDLIB_H
#define MYSTDLIB_H

#include <stdint.h>

#include "common.h"

extern void *mystdout; // struct uart *

extern int getchar(void);
extern int putchar(int c);
extern int puts(const char *str);
extern void print(char *str);
extern char *gets(char *str, uint32_t count, bool echo);
extern int strncmp(const char *lhs, const char *rhs, long unsigned int count);
extern long unsigned int  strlen(const char *str);
extern int isdigit(int c);
extern int islower(int c);
extern int isupper(int c);

#endif
