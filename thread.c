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

thread_t* thread_create(thread_t *parent, void (*func)(void), void *args, unsigned int stack_size)
{
    log_inf("begin parent_tid: %d child_tid: %d stack_size: %d", parent->tid, s_id_gen, stack_size);
    thread_t *new_t = (thread_t *) malloc (sizeof(thread_t));
    
    context_make(&new_t->context, 
                    func, 
                    args,
                    stack_size);
    
    new_t->tid      = s_id_gen;
    s_id_gen++;
    
    new_t->parent   = parent;

    new_t->childq   = NULL;
    new_t->blockq   = NULL;
    
    new_t->state    = THREAD_STATE_READY;
    new_t->sem      = NULL;

    log_inf("end");
    return new_t;
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
    thread_node_t* temp = t->childq->head;
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
    context_swap(&active->context, &next->context);
    log_inf("end");
}
