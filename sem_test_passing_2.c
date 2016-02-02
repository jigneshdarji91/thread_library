#include <stdio.h>
#include "mythread.h"

int mode = 0;

MySemaphore sem1, sem2;

void t0(void * n)
{
  MyThread T;

  int n1 = (int)n; 
  printf("t0 start %d\n", n1);
  MySemaphoreWait(sem1);

  int n2 = n1 -1 ;
  if (n1 > 0) {
    printf("t0 create %d\n", n2);
    MySemaphoreWait(sem2);
    T = MyThreadCreate(t0, (void *)n2);
    if (mode == 1)
    {
        printf("t0 yield %d\n", n1);
        MyThreadYield();
    }
    else if (mode == 2)
      MyThreadJoin(T);
    printf("t0 continue %d\n", n1);
    MySemaphoreSignal(sem2);
  }
  printf("t0 end %d\n", n1);
  MySemaphoreSignal(sem1);
  MyThreadExit();
}

int main(int argc, char *argv[])
{
  int count; 
  
  if (argc < 2 || argc > 3)
    return -1;
  count = atoi(argv[1]);
  if (argc == 3)
    mode = atoi(argv[2]);
  sem1   =   MySemaphoreInit(1);
  sem2   =   MySemaphoreInit(5);
  MyThreadInit(t0, (void *)count);
  MySemaphoreDestroy(sem1);
  MySemaphoreDestroy(sem2);
}
