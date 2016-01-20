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
#include "queue.h"
#include "semaphore.h"

typedef enum thread_state_t
{
    THREAD_STATE_READY = 0,   /*ready  */
    THREAD_STATE_RUNNING,     /*running*/
    THREAD_STATE_BLOCKED         /*waiting*/
} thread_state_t; 

typedef struct thread_t
{
    //needs a context, state, next pointer, and child pointer
    //http://www.gnu.org/software/libc/manual/html_node/System-V-contexts.html    
    
    ucontext_t context;

    unsigned int tid;
    struct thread_t* parent;
    struct queue_t* childq;
    struct queue_t* blockq;

    thread_state_t state;

    semaphore_t *sem;

} thread_t;

typedef struct thread_node_t {
    thread_t t;
    struct thread_node_t* next;
    struct thread_node_t* prev;
} thread_node_t;

static unsigned int s_id_gen = 1;

thread_t thread_create(thread_t *parent, void(*func)(void*), void *args, unsigned int stack_size)
{
    log_inf("begin parent_tid: %d child_tid: %d stack_size: %d", parent->tid, s_id_gen, stack_size);
    thread_t *new_t = (thread_t *) malloc (thread_t);
    
    context_make(new_t->context, 
                    (void*)  &func, 
                    (void *) &args,
                    stack_size);
    
    new_t->tid      = s_id_gen;
    s_id_gen++;
    
    new_t->parent   = parent;

    new_t->childq   = NULL;
    new_t->blockq   = NULL;
    
    new_t->state    = THREAD_STATE_READY;
    new_t->sem      = NULL;

    log_inf("end");
}

void thread_exit(void)
{
    
}

void thread_yield(void)
{
    
}

int thread_join(thread_t *parent, thread_t *child)
{
    //functionality for moving the active thread from running to blocking queue should be present in MyThread

    queue_enq(parent->blockq, child);
    parent->state = THREAD_STATE_BLOCKED; 
}
void thread_join_all(thread_t *t)
{
    //functionality for moving the active thread from running to blocking queue should be present in MyThread
    
    log_inf("begin tid: %d", t->tid);
    thread_node_t* temp = childq->head;
    while(temp != NULL)
    {
        queue_enq(t->blockq, temp->t);
        temp = temp->next;
    }

    log_inf("end");
}

void thread_switch(thread_t *active, thread_t *next)
{
    log_inf("begin");
    context_swap(active->context, next->context);
    log_inf("end");
}

#endif /*THREAD_H*/

