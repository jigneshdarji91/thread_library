/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  thread queue implementation
 *
 *        Version:  1.0
 *        Created:  01/19/2016 03:04:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "thread.h"
#include "debug.h"

typedef struct queue_t          queue_t;
typedef struct thread_t         thread_t;
typedef struct thread_node_t    thread_node_t;

struct queue_t {
    struct thread_node_t *head;
    struct thread_node_t *tail;
    unsigned int size;
};

void    queue_init(struct queue_t *q);
void    queue_enq(struct queue_t *q, thread_t *t);
void    queue_deq(queue_t *q, thread_t **t);
void    queue_del(queue_t *q, thread_t *t);
int     queue_is_present(queue_t *q, thread_t *t);
void    queue_print(queue_t *q);
int     queue_size(queue_t *q);

#endif /*QUEUE_H*/

