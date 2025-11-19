#ifndef CMD_H
#define CMD_H

#include "echo.h"
#include "help.h"
#include "memread.h"
#include "memwrite.h"
#include "reboot.h"
#include "sleep.h"

struct cmd {
  const char *id;
  int (*init)(void);
  int (*main)(int argc, char *argv[]);
};

static const struct cmd cmd_help = {
    .id = "help",
    .main = __cmd_help,
};

static const struct cmd cmd_echo = {
    .id = "echo",
    .main = __cmd_echo,
};

static const struct cmd cmd_memread = {
    .id = "memread",
    .main = __cmd_memread,
};

static const struct cmd cmd_memwrite = {
    .id = "memwrite",
    .main = __cmd_memwrite,
};

static const struct cmd cmd_reboot = {
    .id = "reboot",
    .main = __cmd_reboot,
};

static const struct cmd cmd_sleep = {
    .id = "sleep",
    .init = __cmd_sleep_init,
    .main = __cmd_sleep_main,
};

static const struct cmd *cmds[] = {
    &cmd_help, &cmd_echo, &cmd_memread, &cmd_memwrite, &cmd_reboot, &cmd_sleep,
};

#endif // CMD_H
