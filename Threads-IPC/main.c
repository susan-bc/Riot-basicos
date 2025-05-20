#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "thread.h"
#include "ztimer.h"
#include "mutex.h"
#include "msg.h"

static kernel_pid_t pid;
static char stack[THREAD_STACKSIZE_MAIN];

static void *listener_thread(void *arg){
  (void)arg;

  while(1){
    msg_t msg;
    msg_receive(&msg);
    printf("Message received: %s\n", (char *)msg.content.ptr);
  }
  return NULL;
}

static int send_command(int argc, char **argv){
  if (argc < 2){
    printf("Usage: %s 'Olá'\n", argv[0]);
    return 1;
  }
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
        printf("Hello world!\n");
        return 0;
}

static const shell_command_t shell_commands[] = {
        {"board", "Print the board name", _board_handler},
        {"cpu", "Print the cpu name", _cpu_handler},
        {"hello", "Print 'Hello world!'", _hello},
        {"send", "Sends a message via IPC", send_command},
        {NULL, NULL, NULL}
};

int main(void){

  puts("Messaging through thread IPC");
	pid = thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, 0, listener_thread, NULL, "listener thread");
  char linhaBuffer[SHELL_DEFAULT_BUFSIZE];
	shell_run(shell_commands, linhaBuffer, SHELL_DEFAULT_BUFSIZE);

  return 0;
}
