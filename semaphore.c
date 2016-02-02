/*
 * =====================================================================================
 *
 *       Filename:  semaphore.c
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

#include "semaphore.h"
#include <malloc.h>

semaphore_t* semaphore_init(int value)
{
    log_dbg("begin value: %d", value);
    
    semaphore_t* sem = calloc (1, sizeof(semaphore_t));
    sem->sid         = s_sem_id_gen++;
    sem->value      = value;

    sem->waiting_q  = calloc (1, sizeof(queue_t));
    queue_init(sem->waiting_q);
    sem->using_q    = calloc (1, sizeof(queue_t));
    queue_init(sem->using_q);

    log_dbg("end");
    return sem;
}

void semaphore_signal(semaphore_t* sem)
{
    sem->value++;
    log_dbg("sid: %d value: %d", sem->sid, sem->value);
    return;
}
void semaphore_wait(semaphore_t* sem)
{
    sem->value--;
    log_dbg("sid: %d value: %d", sem->sid, sem->value);
    return;
}

int semaphore_destroy(semaphore_t* sem)
{
    free(sem);
}

