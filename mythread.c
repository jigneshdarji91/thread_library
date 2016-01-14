MyThread MyThreadCreate (void(*start_funct)(void *), void *args);
void MyThreadYield(void);
int MyThreadJoin(MyThread thread);
void MyThreadJoinAll(void);
void MyThreadExit(void);
