#include <stdio.h>
#include <string.h>
#include "thread.h"
#include "ztimer.h"
#include "mutex.h"

typedef struct{
  char buffer[128];
  mutex_t lock;
} data_t;
static data_t data;

static char writer_stack[THREAD_STACKSIZE_MAIN];

static void *writer_thread(void *arg){
  (void)arg;

  while(1){
    mutex_lock(&data.lock);

    size_t p = sprintf(data.buffer, "start: %"PRIu32"", ztimer_now(ZTIMER_MSEC));
    ztimer_sleep(ZTIMER_MSEC, 200);
    p += sprintf(&data.buffer[p], " - end: %"PRIu32"", ztimer_now(ZTIMER_MSEC));

    mutex.unlock(&data.lock);

    ztimer_sleep(ZTIMER_MSEC, 100);
  }
  return NULL;
}

int main(void){
  puts("Riot application with safe thread concurrency");

  thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN +1, 0, writer_thread, NULL, "writer thread");

  while(1){
    mutex_lock(&data.lock);
    printf("%s\n", data.buffer);
    mutex_unlock(&data.lock);

    ztimer_sleep(ZTIMER_MSEC, 200);
  }

  return 0;
}
