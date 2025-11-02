#include <stdint.h>

#include "cmd/echo.h"
#include "cmd/help.h"
#include "cmd/memread.h"
#include "cmd/memwrite.h"
#include "cmd/sleep.h"
#include "common.h"
#include "stdlib.h"

struct cli_cmd {
  const char *id;
  int (*main)(int argc, char *argv[]);
};

static inline char *cli_get_cmd(char *str, uint32_t count);
static inline int cli_run_cmd(char *str, uint32_t count);
void cli_prepare_args(char *str, uint32_t count, int *argc, char *argv[255]);

void cli_run(void) {
  char buffer[255];

  puts("\r\n"
       "==========================================\r\n"
       "|                                        |\r\n"
       "|           Console App Example          |\r\n"
       "|                                        |\r\n"
       "==========================================\r\n"
       "\r\n"
       "Type `help` to view the list of available commands.\r\n"
       "\r\n");

  while (true) {
    print("> ");
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
    } else if (str[i] == ' ') {
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
    {.id = "memread", .main = cmd_memread},
    {.id = "memwrite", .main = cmd_memwrite},
      {.id = "sleep", .main = cmd_sleep},
      /* {.id = "echo", .main = cmd_echo}, */
  };

  for (uint32_t i = 0; i < sizeof(cmds) / sizeof(struct cli_cmd); i++) {
    if (strncmp(cmds[i].id, str, strlen(cmds[i].id)) == 0) {
      char *argv[255];
      int argc;

      cli_prepare_args(str, count, &argc, argv);

      return cmds[i].main(argc, argv);
    }
  }

  print("Invalid command: ");
  print(str);
  puts("Try `help`");

  return ERROR_NO_ENTRY;
}

void cli_prepare_args(char *str, uint32_t count, int *argc, char *argv[255]) {
  *argc = 1;
  argv[0] = str;

  for (uint32_t i = 0; i < count && str[i]; i++) {
    if (str[i] == '\r' || str[i] == '\n') {
      str[i] = 0;
      break;
    }

    if (str[i] == ' ') {
      str[i] = 0;
      argv[*argc] = str + i + 1;
      *argc += 1;
    }
  }
}
