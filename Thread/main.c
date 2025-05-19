#include <stdio.h>
#include <string.>
#include "shell.h"
#include "thread.h"

// Alternativas de versões:
// 1. Thread com prioridade 6 que executa e finaliza antes da chamada da função shell_run, ou seja, não é listada no ps
// 2. Thread de prioridade 8 que executa infinitamente em background e que é listada no ps

// 1.
static char stack[THREAD_STACKSIZE_MAIN];

static void *thread_handler(void *arg){
  (void)arg;
  puts("Hello from thread!");
  return 0;
}

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
  thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, 0, thread_handler, NULL, "new_thread");
  char linhaBuffer[SHELL_DEFAULT_BUFFSIZE];
  shell_run(shell_commands, linhaBuffer, SHELL_DEFAULT_BUFSIZE);
  return 0;
}


// 2.
static char stack[THREAD_STACKSIZE_MAIN];

static void *thread_handler(void *arg){
  (void)arg;
  while(1){}
  return NULL;
}

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
  thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN +1, 0, thread_handler, NULL, "new_thread");
  char linhaBuffer[SHELL_DEFAULT_BUFFSIZE];
  shell_run(shell_commands, linhaBuffer, SHELL_DEFAULT_BUFSIZE);
  return 0;
}
