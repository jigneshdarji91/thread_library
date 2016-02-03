#include <stdio.h>
#include "mythread.h"

void t0(void * dummy)
{
  printf("t0 start\n");
  MySemaphore sem = MySemaphoreInit(1);
  MySemaphoreWait(sem);
  MySemaphoreSignal(sem);
  MyThreadExit();
}

int main()
{
  MyThreadInit(t0, NULL);
}
