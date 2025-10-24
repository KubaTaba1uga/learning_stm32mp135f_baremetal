#include "common.h"
#include "help.h"
#include "stdlib.h"
#include <stdint.h>

struct cli_cmd {
  const char *id;
  int (*main)(char *str, uint32_t count);
};

static inline char *cli_get_cmd(char *str, uint32_t count);
static inline int cli_run_cmd(char *str, uint32_t count);

void cli_run(void) {
  char *prompt = "> ";
  char buffer[255];

  while (true) {
    print(prompt);
    cli_get_cmd(buffer, sizeof(buffer) / sizeof(char));
    print("\r\n");

    cli_run_cmd(buffer, sizeof(buffer) / sizeof(char));
  }
};

static inline char *cli_get_cmd(char *str, uint32_t count) {
  uint32_t max = count - 2;
  for (uint32_t i = 0; i < max; i++) {
    str[i] = getchar();

    if (str[i] == '\r') {
      str[i + 1] = '\n';
      str[i + 2] = 0;
      break;
    } else if ((str[i] == 8 ||    // backspace
                str[i] == 127) && // delete
               (i > 0)) {
      str[i] = 0; // We do not want to display backspace by accident
      i -= 2;     // We need to go back one place but on the end of loop we will
                  // have ++1 so we need to sub --2.
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

static inline int cli_run_cmd(char *str, uint32_t count) {
  struct cli_cmd cmds[] = {
      {.id = "help", .main = cmd_help},
  };

  for (uint32_t i = 0; i < sizeof(cmds) / sizeof(struct cli_cmd); i++) {
    if (strncmp(cmds[i].id, str, strlen(cmds[i].id)) == 0) {
      return cmds[i].main(str, count);
    }
  }

  print("Invalid command: ");
  print(str);
  puts("Try `help`");
  
  return ERROR_NO_ENTRY;
}
