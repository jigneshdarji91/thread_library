/*
 * =====================================================================================
 *
 *       Filename:  thread.h
 *
 *    Description:  low-level thread library
 *
 *        Version:  1.0
 *        Created:  01/20/2016 12:57:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */

#ifndef THREAD_H
#define THREAD_H

#include "debug.h"
#include "semaphore.h"
#include <vector>
#include <functional>
#include "context.h"

using namespace std;

static unsigned int     sThreadIdGen = 1;
typedef unsigned int    ThreadID;
struct Thread;
typedef std::vector<Thread>   ThreadQueue;
typedef enum ThreadState
{
    THREAD_STATE_READY = 0,   /*ready  */
    THREAD_STATE_RUNNING,     /*running*/
    THREAD_STATE_BLOCKED         /*waiting*/
}   ThreadState; 

class Thread
{
    private:
        ucontext_t              context;
        ThreadID                tid;
        ThreadState             state;
        Thread*                 parent;
        ThreadQueue             childq;
        ThreadQueue             blockq;

    public:
        Thread (Thread& parent,
                void (*func)(void), 
                void *args, 
                unsigned int stack_size);
        ~Thread();
        void        Exit();
        void        StatusUpdate();
        void        Yield();
        int         Join(Thread& child);
        void        JoinAll();
        static void Switch(Thread& active, Thread& next);
        void        Run(Thread& next);
        bool        IsChild(Thread& t);
        int         RemoveChild(Thread& t);

        friend bool operator==(const Thread &t1, const Thread &t2);
};

bool operator==(const Thread &t1, const Thread &t2)
{
    return t1.tid == t2.tid;
}

#endif /*THREAD_H*/

