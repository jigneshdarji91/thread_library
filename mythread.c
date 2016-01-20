#include <ucontext.h>
#include "debug.h"
#include "mythread.h"
#include "semaphore.h"
#include "thread.h"
#include "queue.h"

thread_t    *main_th;
thread_t    *init_th;

thread_t    *active_th;
queue_t     *ready_q;
queue_t     *block_q;


MyThread MyThreadCreate (void(*start_funct)(void *), void *args)
{
    
}
void MyThreadExit(void)
{

}
void MyThreadYield(void)
{

}
int MyThreadJoin(MyThread thread)
{

}
void MyThreadJoinAll(void)
{

}

// ****** SEMAPHORE OPERATIONS ****** 
// Create a semaphore
MySemaphore MySemaphoreInit(int initialValue)
{

}

// Signal a semaphore
void MySemaphoreSignal(MySemaphore sem)
{

}

// Wait on a semaphore
void MySemaphoreWait(MySemaphore sem)
{

}

// Destroy on a semaphore
int MySemaphoreDestroy(MySemaphore sem)
{

}

// ****** CALLS ONLY FOR UNIX PROCESS ****** 
// Create and run the "main" thread
void MyThreadInit(void(*start_funct)(void *), void *args)
{

}

