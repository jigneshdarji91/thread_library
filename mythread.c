#include "ucontext.h"
#include "mythread.h"
#include "thread.h"
#include "semaphore.h"
#include "debug.h"
#include "queue.h"

thread_t *main_th;
thread_t *init_th;

thread_t *active_th;
queue_t *ready_q;
queue_t *block_q;


MyThread MyThreadCreate (void(*start_funct)(void *), void *args);
void MyThreadExit(void);

void MyThreadYield(void);
int MyThreadJoin(MyThread thread);
void MyThreadJoinAll(void);
