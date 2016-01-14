struct MySemaphore 
{
    int value; 
}

MySemaphore MySemaphoreInit(int initialValue);
void MySemaphoreSignal(MySemaphore sem);
void MySemaphoreWait(MySemaphore sem);
int MySemaphoreDestroy(MySemaphore sem);
