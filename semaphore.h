#define "debug.h"
#define "queue.h"

typedef struct semaphore_t
{
    int value;
    queue_t* waiting_q;
    queue_t* using_q;
} semaphore_t;

MySemaphore MySemaphoreInit(int initialValue);
void MySemaphoreSignal(MySemaphore sem);
void MySemaphoreWait(MySemaphore sem);
int MySemaphoreDestroy(MySemaphore sem);
