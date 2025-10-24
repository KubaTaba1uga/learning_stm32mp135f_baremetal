#include "common.h"
#include "stdlib.h"
struct cli {
  const char *prompt;
  const struct uart *serial_console;
};

struct cli cli;

static inline char *cli_get_cmd(char *str, uint32_t count);
void cli_run(void) {
  char *prompt = "> ";
  char buffer[255];

  while (true) {
    print(prompt);
    cli_get_cmd(buffer, sizeof(buffer) / sizeof(char));
    print("Command is: ");
    print(buffer);
  }
};

static inline char *cli_get_cmd(char *str, uint32_t count) {
  uint32_t max = count - 2;
  for (uint32_t i = 0; i < max; i++) {
    str[i] = getchar();

    if (str[i] == '\r') {
      str[i + 1] = '\n';
      str[i + 2] = 0;
      print("\r\n");
      break;
    } else if ((str[i] == 8 ||    // backspace
                str[i] == 127) && // delete
               (i > 0)) {
      str[i]=0;
      i -= 2;
      putchar(8);
      putchar(' ');
      putchar(8);
    } else if (str[i] >= 33 && str[i] <= 126) {
      putchar(str[i]);
    } else {
      i--;
    }
  }

  str[max] = 0; // In case there is no newline

  return str;
};
