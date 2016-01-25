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
#include "queue.h"
#include <malloc.h>

thread_t* thread_create(thread_t *parent, void (*func)(void), void *args, unsigned int stack_size)
{
    log_inf("begin child_tid: %d stack_size: %d", s_id_gen, stack_size);
    thread_t *new_t = (thread_t *) malloc (sizeof(thread_t));
    
    if(new_t == NULL)
        return NULL;
    context_make(&new_t->context, 
                    func, 
                    args,
                    stack_size);
    
    new_t->tid      = s_id_gen;
    s_id_gen++;
    
    new_t->parent   = parent;

    new_t->childq   = (queue_t *) malloc (sizeof(queue_t));
    queue_init(new_t->childq);
    new_t->blockq   = (queue_t *) malloc (sizeof(queue_t));
    queue_init(new_t->blockq);
    
    new_t->state    = THREAD_STATE_READY;
    new_t->sem      = NULL;

    if(parent != NULL && parent->tid > 0)
    {
        queue_enq(parent->childq, &new_t);
    }

    log_inf("end");
    return new_t;
}

void thread_exit(thread_t *t)
{
    log_inf("begin tid:%d", t->tid);   
    if(t == NULL)
        return;

    if(t->parent != NULL)
    {
        //Delete from the childq
        if(queue_is_present(t->parent->childq, &t))
        {
            log_inf("removing from childq tid:%d parent_tid: %d", t->tid, t->parent->tid);
            queue_del(t->parent->childq, &t);
            thread_status_update(t->parent);
        }

        //Delete from the blockq
        if(queue_is_present(t->parent->blockq, &t))
        {
            log_inf(" removing from blockq tid:%d was blocking tid: %d", t->tid, t->parent->tid);
            queue_del(t->parent->blockq, &t);

            //Update parent status
            thread_status_update(t->parent);
        }
    }
    else
    {
        log_wrn("parent thread is dead");
    }
    
    /*
    free(t->context.uc_stack.ss_sp);
    free(t->childq);
    free(t->blockq);
    free(t);
    */
    log_inf("end");
}

void thread_status_update(thread_t *t)
{
    if(t->blockq->size > 0)
    {
        t->state = THREAD_STATE_BLOCKED;
    }
    else if(t->sem != NULL) //TODO: can thread only wait on one sem?
    {
        t->state = THREAD_STATE_BLOCKED;
    }
    else
    {
        t->state = THREAD_STATE_READY;
    }
    log_dbg("tid: %d state:%d", t->tid, t->state);
}

void thread_yield(thread_t *t)
{
    log_inf("begin tid:%d", t->tid);   
    log_inf("end");   
}

int thread_join(thread_t *parent, thread_t *child)
{
    if(parent != NULL && child != NULL)
    {
        log_err("NULL threads being sent");
        return -1;
    }
    //functionality for moving the active thread from running to blocking queue should be present in MyThread
    log_inf("parent: %d child: %d", parent->tid, child->tid);
    queue_enq(parent->blockq, &child);
    parent->state = THREAD_STATE_BLOCKED; 
    return 0;
}

void thread_join_all(thread_t *t)
{
    //functionality for moving the active thread from running to blocking queue should be present in MyThread
    
    log_inf("begin tid: %d", t->tid);
    thread_node_t* temp = t->childq->head;
    while(temp != NULL)
    {
        queue_enq(t->blockq, &temp->t);
        temp = temp->next;
    }
    t->state = THREAD_STATE_BLOCKED; 
    log_inf("end");
}

void thread_switch(thread_t *active, thread_t *next)
{
    log_inf("begin active_tid: %d next_tid: %d", active->tid, next->tid);
    context_swap(&active->context, &next->context);
    log_inf("end");
}

