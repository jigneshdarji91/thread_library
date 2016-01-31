#include <ucontext.h>
#include "debug.h"
#include "mythread.h"
#include "semaphore.h"
#include "thread.h"
#include <malloc.h>
#include <assert.h>
#include <algorithm>

Thread      *mainTh;
Thread      *initTh;

ThreadQueue     activeQ;
ThreadQueue     readyQ;
ThreadQueue     blockQ;

const int STACK_SIZE    = 8000; //FIXME: stack size round off

const int SUCCESS       = 0;
const int FAILURE       = -1;

void MyThreadInit(void(*start_funct)(void *), void *args)
{
    log_inf("begin");
    initTh = new Thread(STACK_SIZE);
    mainTh = new Thread(*initTh, (void(*)(void))start_funct, args, STACK_SIZE);

    activeQ.push_back(*mainTh);
    Thread::Switch(*initTh, *mainTh);
    log_inf("end");
}


MyThread MyThreadCreate (void(*start_funct)(void *), void *args)
{
    //create thread
    log_inf("begin");
    Thread* newTh = new Thread(activeQ.front(), (void(*)(void))start_funct, args, STACK_SIZE);
    
    //add the thread to the ready queue
    readyQ.push_back(*newTh);
    log_inf("end");
    return (MyThread ) newTh;
}

void MyThreadExit(void)
{
    if((*activeQ.begin()).getTID() == (*mainTh).getTID())
    {
        if(readyQ.size() > 0)
        {
            log_wrn("can't allow mainTh to exit");
            MyThreadJoinAll(); //FIXME: Not sure if this would work
        }
    }

    assert(!activeQ.empty());
    Thread* exitTh  =   &(activeQ.front());
    activeQ.erase(activeQ.begin());

    exitTh->Exit();

    //put the parent back to readyQ if applicable
    ThreadQueue::iterator itr = find(blockQ.begin(), blockQ.end(), *(exitTh->getParent()));
    if(exitTh->getParent())
    {
        if(itr != blockQ.end())
        {
            if(itr->getState() == THREAD_STATE_READY)
            {
                readyQ.push_back(*itr);
                blockQ.erase(itr);
                log_inf("parent tid: %d unblocked by tid: %d", itr->getTID(), exitTh->getTID());
            }
        }
    }
    else
    {
        log_wrn("parent is already dead");
    }

    //delete(exitTh);

    if(!readyQ.empty())
    {
        Thread* newTh   =  &(readyQ.front());
        activeQ.push_back(*newTh);
        readyQ.erase(readyQ.begin());
        log_inf("incoming tid: %d", newTh->getTID());
        Thread::Run(*newTh);
    }
    else
    {
        log_inf("readyQ empty, running initTh");
        Thread::Run(*initTh);
    }

    log_dbg("end");
}
void MyThreadYield(void)
{
    log_dbg("begin");
    assert(!activeQ.empty());
    Thread* exitTh  =   &(activeQ.front());
    readyQ.push_back(*exitTh);
    activeQ.erase(activeQ.begin());

    assert(!readyQ.empty());
    Thread* newTh   =  &(readyQ.front());
    activeQ.push_back(*newTh);
    readyQ.erase(readyQ.begin());
    log_inf("incoming tid: %d", newTh->getTID());

    Thread::Run(*newTh);
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

