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

typedef struct semaphore_t semaphore_t;

struct semaphore_t
{
    int                 value;
    struct queue_t*     waiting_q;
    struct queue_t*     using_q;
};

#endif /*SEMAPHORE_H*/
