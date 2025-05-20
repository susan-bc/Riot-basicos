#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "thread.h"
#include "ztimer.h"
#include "mutex.h"
#include "msg.h"

static char stack[THREAD_STACKSIZE_MAIN];

static void *thread_handler(void *arg){
	int counter = 0;
	while(1){
		counter++;
		printf("Message %d from %s\n", counter, (char *)arg);
		ztimer_sleep(ZTIMER_MSEC, 1000);
	}
	return NULL;
}

int main(void){
	thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, 0, thread_handler, "my thread", "thread");
	int counter = 0;
  
	while(1){
		counter++;
		printf("Message %d from main thread\n", counter);
		ztimer_sleep(ZTIMER_MSEC, 500);
	}
	
	return 0;
}
