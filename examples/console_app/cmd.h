#ifndef CMD_H
#define CMD_H

struct uart;
struct cmd_command {
  char *id;
  int (*func)(char *user_input, struct uart *uart);
};

#endif // CMD_H
