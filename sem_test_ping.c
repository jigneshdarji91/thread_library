#include <stdio.h>
#include "mythread.h"

int n;

MySemaphore sem;

void t1(void * who)
{
  printf("t%d start\n", (int)who);
  int i;

  MySemaphoreWait(sem);

  for (i = 0; i < n; i++) {
    printf("t%d yield\n", (int)who);
    MyThreadYield();
  }
  printf("t%d end\n", (int)who);
  MySemaphoreSignal(sem);
  MyThreadExit();
}

void t0(void * dummy)
{
  printf("t0 begin\n");
  MyThreadCreate(t1, (void *)1);
  t1(0);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    return -1;
  n = atoi(argv[1]);
  sem   =   MySemaphoreInit(1);
  MyThreadInit(t0, 0);
  MySemaphoreDestroy(sem);
}
