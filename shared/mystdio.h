#ifndef MYSTDIO_H
#define MYSTDIO_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <uchar.h>

size_t mystrlen(const char *str);
int myputchar(int ch);

static inline int myprintf(const char *format, ...) {
  va_list args;

  va_start(args, format);

  const char *format_end = format + mystrlen(format);
  for (const char *format_cp = format; format_cp != format_end; format_cp++) {
    if (*format_cp == '%') {
      switch (*(format_cp + 1)) {
      case 'c':
        myputchar((char)va_arg(args, int));
        format_cp++;
        break;

      case 's': {
        char *str = va_arg(args, char *);
        while (*str) {
          myputchar(*str);
          str++;
        }
        format_cp++;
      } break;

      case 'd': {
        char buffer[10], *bufp;
        bufp = buffer;
        int number = va_arg(args, int);

        do {
          *bufp = (number % 10) + '0';
          number /= 10;
          bufp++;
        } while (number);

        while (bufp != buffer) {
          bufp--;
          myputchar(*bufp);
        }
      } break;

      case 'x': {
        char buffer[10], *bufp;
        bufp = buffer;
        int number = va_arg(args, int);

        do {
          *bufp = (number % 16);
          if (*bufp <= 9) {
            *bufp = *bufp + '0';
          } else {
            *bufp = *bufp + 'A' - 10;
          }
          number /= 16;
          bufp++;
        } while (number);

        while (bufp != buffer) {
          bufp--;
          myputchar(*bufp);
        }
      } break;

      default:;
      }
    } else {
      myputchar(*format_cp);
    }
  }

  va_end(args);

  return 0;
};

#endif
