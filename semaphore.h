/*
 * =====================================================================================
 *
 *       Filename:  semaphore.h
 *
 *    Description:  semaphore library
 *
 *        Version:  1.0
 *        Created:  01/09/2016 10:32:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "debug.h"
#include "queue.h"

typedef struct semaphore_t  semaphore_t;
static unsigned int         s_sem_id_gen = 1;

struct semaphore_t
{
    int                 value;
    unsigned int        sid;
    struct queue_t*     waiting_q;
    struct queue_t*     using_q;
};

semaphore_t*    semaphore_init(int value);
void            semaphore_signal(semaphore_t* sem);
void            semaphore_wait(semaphore_t* sem);
int             semaphore_destroy(semaphore_t* sem);

#endif /*SEMAPHORE_H*/
