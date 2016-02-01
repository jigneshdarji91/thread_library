#include <ucontext.h>
#include "debug.h"
#include "mythread.h"
#include "semaphore.h"
#include "thread.h"
#include "queue.h"
#include <malloc.h>
#include <assert.h>

thread_t    *main_th;
thread_t    *init_th;

queue_t     *active_q;
queue_t     *ready_q;
queue_t     *block_q;

const int STACK_SIZE    = 8000; //FIXME: stack size round off

const int SUCCESS       = 0;
const int FAILURE       = -1;

void MyThreadInit(void(*start_funct)(void *), void *args)
{
    log_inf("begin");
    init_th = thread_create(NULL, NULL, NULL, STACK_SIZE);
    main_th = thread_create(init_th, (void*)start_funct, args, STACK_SIZE);

    active_q    = calloc (1, sizeof(queue_t));
    ready_q     = calloc (1, sizeof(queue_t));
    block_q     = calloc (1, sizeof(queue_t));

    queue_init(active_q);
    queue_init(ready_q);
    queue_init(block_q);

    queue_enq(active_q, &main_th);
    thread_switch(init_th, main_th); 
    thread_exit(init_th);
    thread_exit(main_th);
    log_inf("end");
}


MyThread MyThreadCreate (void(*start_funct)(void *), void *args)
{
    //FUNCTIONS:
    //- create thread
    //- add thread to the ready queue
    
    //create thread
    log_inf("begin");
    thread_t *new_th = thread_create(active_q->head->t, (void *)start_funct, args, STACK_SIZE);
    if(new_th == NULL)
    {
        log_err("thread creation failed");
        return (MyThread *)0;
    }
    
    //add the thread to the ready queue
    queue_enq(ready_q, &new_th);
    log_inf("end");
    return (MyThread *)new_th;
}

void MyThreadExit(void)
{
    //FUNCTION: 
    //- make head of ready_q active
    //- free this thread (use thread.h)
    //- check if the parent thread's status has changed

    log_inf("begin");
    thread_t *exit_th = NULL, *parent_th = NULL, *new_active_th = NULL;
    thread_state_t parent_old_state;

    assert(active_q);
    assert(active_q->head);
    if(active_q->head->t->tid > 0 &&
        active_q->head->t->tid == main_th->tid)
    {
        log_dbg("main thread is exiting");
        if(queue_size(ready_q) > 0)
        {
            log_dbg("main thread is exiting while other threads exit");
            MyThreadJoinAll();
        }
    }
    queue_deq(active_q, &exit_th);
    if(exit_th == NULL)
    {
        log_err("active_q returned a NULL thread");
        return;
    }

    parent_th = exit_th->parent; 
    if(parent_th != NULL && parent_th->tid > 0)
    {
        log_inf("parent tid: %d for tid: %d", parent_th->tid, exit_th->tid);
        parent_old_state = parent_th->state;
        thread_exit_update_parent(exit_th);
    }
    else
        log_inf("parent is NULL for tid: %d", exit_th->tid);
    
    log_inf("exiting tid: %d", exit_th->tid);
    thread_exit(exit_th);

    //parent's state
    if(parent_th != NULL 
        && parent_th->state == THREAD_STATE_READY)
    {
        if(queue_is_present(block_q, &parent_th))
        {
            //remove from block queue
            queue_del(block_q, &parent_th);
            queue_enq(ready_q, &parent_th);
        }
    }
    else
    {
        if(parent_th == NULL)
            log_inf("parent is NULL");
        else
        {
            log_inf("parent old_state: %d new_state: %d", parent_old_state, parent_th->state);
        }
    }

    queue_deq(ready_q, &new_active_th);
    if(new_active_th != NULL && new_active_th->tid > 1)
    {
        log_inf("incoming_tid: %d", new_active_th->tid);
        queue_enq(active_q, &new_active_th);
        thread_run(new_active_th);
    }
    log_dbg("end");
    return;
}

void MyThreadYield(void)
{
    log_inf("begin");
    thread_t *exit_th = NULL, *parent_th = NULL, *new_active_th = NULL;
    queue_deq(active_q, &exit_th);
    queue_enq(ready_q, &exit_th);
    log_inf("exiting tid: %d", exit_th->tid);
    queue_deq(ready_q, &new_active_th);
    if(new_active_th != NULL && new_active_th->tid > 0)
    {
        queue_enq(active_q, &new_active_th);
        thread_switch(exit_th, new_active_th);
    }
    else
        log_err("should never come here, yield did not find a thread in the readyq");
    log_inf("end");
}
int MyThreadJoin(MyThread thread)
{
    log_inf("begin");
    thread_t *exit_th = NULL, *parent_th = NULL, *new_active_th = NULL;
    queue_deq(active_q, &exit_th);
    thread_join(exit_th, (thread_t **)&thread);
    queue_enq(block_q, &exit_th);
    log_inf("exiting tid: %d", exit_th->tid);
    queue_deq(ready_q, &new_active_th);
    if(new_active_th != NULL && new_active_th->tid > 1)
    {
        log_inf("yielding tid: %d and starting tid: %d", exit_th->tid, new_active_th->tid);
        queue_enq(active_q, &new_active_th);
        thread_switch(exit_th, new_active_th);
    }
    else
        thread_run(init_th);
    log_inf("end");

}
void MyThreadJoinAll(void)
{
    log_inf("begin");
    thread_t *exit_th = NULL, *parent_th = NULL, *new_active_th = NULL;
    queue_deq(active_q, &exit_th);
    thread_join_all(exit_th);
    queue_enq(block_q, &exit_th);
    log_inf("exiting tid: %d", exit_th->tid);
    queue_deq(ready_q, &new_active_th);
    if(new_active_th != NULL && new_active_th->tid > 1)
    {
        queue_enq(active_q, &new_active_th);
        thread_switch(exit_th, new_active_th);
    }
    else
        thread_run(init_th);
    log_inf("end");
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

