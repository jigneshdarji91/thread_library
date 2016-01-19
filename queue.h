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

typedef struct thread_node_t {
    thread_t t;
    thread_t *next;
    thread_t *prev;
} thread_node_t;

typedef struct thread_queue_t {
    thread_t *head;
    thread_t *tail;
    unsigned int size;
    //TODO: Add a semaphore

} thread_queue_t;

void queue_enq(thread_queue_t &q, thread_t &t)
{
    log_dbg("begin");
    thread_node_t new_t = (thread_node_t *)malloc(sizeof(thread_node_t));
    new_t = &t;
    new_t.next = NULL;
    new_t.prev = tail;
    tail->next = new_t;
    q.size++;
    log_dbg("end");
}

void queue_deq(thread_queue_t &q, thread_t &t)
{
    log_dbg("begin");
    if(q.size < 1)
    {
        log_wrn("Queue is empty");
        return;
    }

    t = head->t;
    head = head->next;
    q.size--;
    log_dbg("end");
}

int queue_size(thread_queue_t &q)
{
    log_dbg("size: %d", q.size);
    return q.size;   
}


#endif QUEUE_H

