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
#include <malloc.h>

void queue_init(struct queue_t *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void queue_enq(queue_t *q, thread_t *t)
{
    log_dbg("begin tid: %d qsize:%d", t->tid, q->size);
    thread_node_t *new_t = (thread_node_t *)malloc(sizeof(thread_node_t));
    new_t->t = t;
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
    queue_print(q);
    log_dbg("end");
}

void    queue_deq(queue_t *q, thread_t **t)
{
    log_dbg("begin size:%d", q->size);
    queue_print(q);
    if(q->size < 1)
    {
        log_wrn("Queue is empty. End.");
        *t = NULL;
        return;
    }

    *t = q->head->t;
    if(q->size > 1)
    {
        q->head         = q->head->next;
        q->head->prev   = NULL;
    }
    else
    {
        q->head = NULL;
        q->tail = NULL;
    }
    //q->head->prev = NULL;
    q->size--;
    log_dbg("end tid: %d", (*t)->tid);
}

void    queue_del(queue_t *q, thread_t *t)
{
    int found = 0; 
    thread_node_t* temp = q->head;
    while(temp != NULL)
    {
        if(temp->t->tid == t->tid)
        {
            log_inf("thread removed");
            found = 1;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
            q->size--;
            break;
        }
        temp = temp->next;
    }
    
    log_dbg("tid: %d deleted: %d", t->tid, found);
    return;
}

int     queue_is_present(queue_t *q, thread_t *t)
{
    int found = 0;
    thread_node_t* temp = q->head;
    while(temp != NULL)
    {
        if(temp->t->tid == t->tid)
        {
            found = 1;
            break;
        }
        temp = temp->next;
    }
    
    log_dbg("tid: %d found: %d", t->tid, found);
    return found;
}

void queue_print(queue_t *q)
{
    log_dbg("begin");
    thread_node_t* temp = q->head;
    while(temp != NULL)
    {
        log_inf("tid: %d", temp->t->tid);
        temp = temp->next;
    }
    log_dbg("end");
}

int queue_size(queue_t *q)
{
    log_dbg("size: %d", q->size);
    return q->size;   
}

