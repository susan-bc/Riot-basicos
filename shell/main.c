#include <stdio.h>
#include <string.h>
#include <shell.h>

static int _board_handler(int argc, char **argv){
  (void)argc;
  (void)argv;
  puts(RIOT_BOARD);
  return 0;
}

static int _cpu_handler(int argc, char **argv){
  (void)argc;
  (void)argv;
  puts(RIOT_CPU);
  return 0;
}

static int _hello(int argc, char **argv){
  (void)argc;
  (void)argv;
  puts("Hello world");
  return 0;
}

static const shell_command_t shell_commands[] = {
  {"board", "Prints the board name", _board_handler},
  {"cpu", "Prints the CPU name", _cpu_handler},
  {"hello", "Prints 'Hello world!", _hello},
  {NULL, NULL, NULL }
}

int main(void){
  char linhaBuffer[SHELL_DEFAULT_BUFFSIZE];
  shell_run(shell_commands, linhaBuffer, SHELL_DEFAULT_BUFSIZE);
  return 0;
}
