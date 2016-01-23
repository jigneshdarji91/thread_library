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
#include "queue.h"
#include "context.h"

typedef enum    thread_state_t  thread_state_t;
typedef struct  thread_t        thread_t;
typedef struct  thread_node_t   thread_node_t;

enum thread_state_t
{
    THREAD_STATE_READY = 0,   /*ready  */
    THREAD_STATE_RUNNING,     /*running*/
    THREAD_STATE_BLOCKED         /*waiting*/
}; 

struct thread_t
{
    ucontext_t              context;
    unsigned int            tid;
    enum thread_state_t     state;
    struct thread_t         *parent;
    struct queue_t          *childq;
    struct queue_t          *blockq;
    struct semaphore_t      *sem;
};

struct thread_node_t 
{
    struct thread_t         *t;
    struct thread_node_t    *next;
    struct thread_node_t    *prev;
};

static unsigned int s_id_gen = 1;

thread_t*   thread_create(thread_t *parent, void (*func)(void), void *args, unsigned int stack_size);
void        thread_exit(thread_t* /*t*/);
void        thread_status_update(thread_t *t);
void        thread_yield(thread_t* /*t*/);
int         thread_join(thread_t *parent, thread_t *child);
void        thread_join_all(thread_t *t);
void        thread_switch(thread_t *active, thread_t *next);

#endif /*THREAD_H*/

