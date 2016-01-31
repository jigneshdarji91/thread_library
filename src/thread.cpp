/*
 * =====================================================================================
 *
 *       Filename:  thread.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/20/2016 04:34:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */

#include "thread.h"
#include <malloc.h>
#include <algorithm>
#include <assert.h>

Thread::Thread ( unsigned int stack_size)
{
    log_dbg("begin child_tid: %d stack_size: %d", sThreadIdGen, stack_size);

    tid    =   sThreadIdGen++;
    parent =   NULL;
    state  =   THREAD_STATE_READY;
    Context::Make(context, NULL, NULL, stack_size);

    log_dbg("end");
}

Thread::Thread (Thread& parentTh,
        void (*func)(void), 
        void *args, 
        unsigned int stack_size)
{
    log_dbg("begin child_tid: %d stack_size: %d", sThreadIdGen, stack_size);

    tid    =   sThreadIdGen++;
    parent =   &parentTh;
    state  =   THREAD_STATE_READY;
    Context::Make(context, func, args, stack_size);

    assert(parent);
    parent->childq.push_back(*this);

    log_dbg("end");
}

Thread::~Thread()
{

}

void        
Thread::Exit()
{
    log_dbg("exiting tid: %d", tid);
    
    if(!parent)
        log_err("parent doesn't exist");
    
    parent->RemoveChild(*this);
}

Thread* 
Thread::getParent()
{
    return parent;
}

int 
Thread::RemoveChild(Thread& t)
{
    log_dbg("removing tid: %d from parent: %d", t.tid, tid);
    ThreadQueue::iterator itr = find(childq.begin(), childq.end(), t);
    if(itr != childq.end())
    {
        childq.erase(itr);
    }
    else
        log_err("tid: %d is NOT a child of tid: %d", t.tid, tid);

    if(!blockq.empty())
    {
        ThreadQueue::iterator itr2 = find(blockq.begin(), blockq.end(), t);
        if(itr2 != childq.end())
        {
            log_inf("itr2 tid: %d", itr2->getTID());
            blockq.erase(itr2);
            StatusUpdate();
        }
        else
            log_inf("tid: %d is NOT blocking tid: %d", t.tid, tid);
    }
    else
        log_inf("blockq is empty");
}

bool
Thread::IsChild(Thread& t)
{
    bool isChild = false;
    ThreadQueue::iterator itr = find(childq.begin(), childq.end(), t);
    if(itr != childq.end())
    {
        isChild = true;
    }
    log_dbg("parent: %d child: %d isChild: %d", tid, t.tid, isChild);
    return isChild;
}

void        
Thread::StatusUpdate()
{
    //TODO: state change when waiting on semaphore
    if(blockq.size() > 0) 
        state   =   THREAD_STATE_BLOCKED;
    else
        state   =   THREAD_STATE_READY;
}

int 
Thread::getTID()
{
    return tid;
}

ThreadState 
Thread::getState()
{
    return state;
}

void        
Thread::Yield()
{
    log_dbg("");
}

int         
Thread::Join(Thread& child)
{

}

void        
Thread::JoinAll()
{

}

void 
Thread::Switch(Thread& active, Thread& next)
{
    Context::Swap(active.context, next.context);
}

void        
Thread::Run(Thread& next)
{
    Context::Set(next.context);
}
