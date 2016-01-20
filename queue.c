/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/20/2016 04:36:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */

#include "queue.h"

void queue_init(struct queue_t *q)
{
    q->head = NULL;
    q->tail = NULL;
}

void queue_enq(queue_t *q, thread_t *t)
{
    log_dbg("begin tid: %d qsize:%d", t->tid, q->size);
    thread_node_t *new_t = (thread_node_t *)malloc(sizeof(thread_node_t));
    new_t->t = *t;
    new_t->next = NULL;
    new_t->prev = q->tail;
    if(q->size == 0)
    {
        log_dbg("empty queue");
        q->head = new_t;
    }
    else 
    {
        q->tail->next = new_t;
    }
    q->tail = new_t;
    q->size++;
    log_dbg("end");
}

void queue_deq(queue_t *q, thread_t *t)
{
    log_dbg("begin size:%d", q->size);
    if(q->size < 1)
    {
        log_wrn("Queue is empty");
        return;
    }

    *t = q->head->t;
    if(q->size > 1)
        q->head = q->head->next;
    else
    {
        q->head = NULL;
        q->tail = NULL;
    }
    //q->head->prev = NULL;
    q->size--;
    log_dbg("end");
}

int queue_size(queue_t *q)
{
    log_dbg("size: %d", q->size);
    return q->size;   
}

