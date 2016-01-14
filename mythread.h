enum MyThreadState
{
    THREAD_READY = 0,   /*ready  */
    THREAD_RUNNING,     /*running*/
    THREAD_WAIT         /*waiting*/
}

typedef struct MyThread
{
    //needs a context, state, next pointer, and child pointer
    //http://www.gnu.org/software/libc/manual/html_node/System-V-contexts.html    
    
    MyThread* next;
    MyThread* prev;
    MyThread* children;
    MyThread* parent;

    MyThreadState state;

    MySemaphore *semaphore;

} MyThread;

MyThread MyThreadCreate (void(*start_funct)(void *), void *args);
void MyThreadYield(void);
int MyThreadJoin(MyThread thread);
void MyThreadJoinAll(void);
void MyThreadExit(void);
