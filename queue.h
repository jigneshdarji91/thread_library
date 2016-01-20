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

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "debug.h"
#include "thread.h"

//Used for testing
//typedef int thread_t;

typedef struct queue_t {
    thread_node_t *head;
    thread_node_t *tail;
    unsigned int size;
    //TODO: Add a semaphore

} queue_t;

void queue_init(struct queue_t *q)
{
    q->head = NULL;
    q->tail = NULL;
}

void queue_enq(struct queue_t *q, thread_t *t)
{
    log_dbg("begin size:%d", q->size);
    thread_node_t *new_t = (thread_node_t *)malloc(sizeof(thread_node_t));
    new_t->t = *t;
    new_t->next = NULL;
    new_t->prev = q->tail;
    if(q->size == 0)
    {
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
    log_inf("value: %d", *t);
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


#endif /*QUEUE_H*/

