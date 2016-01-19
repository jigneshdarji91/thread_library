/*
 * =====================================================================================
 *
 *       Filename:  test_queue.c
 *
 *    Description:  testing queue utilities
 *
 *        Version:  1.0
 *        Created:  01/19/2016 04:00:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */

#include "queue.h"

int main()
{
    thread_t x = 10, y = 5, z = 6, w;
    queue_t *q = (queue_t *) malloc(sizeof(queue_t));
    queue_init(q);
    queue_enq(q, &x);
    queue_enq(q, &y);
    queue_enq(q, &z);

    queue_deq(q, &w);
    log_inf("w: %d", w);
    queue_deq(q, &w);
    log_inf("w: %d", w);
    queue_enq(q, &z);
    queue_deq(q, &w);
    log_inf("w: %d", w);
    queue_deq(q, &w);
    log_inf("w: %d", w);
    return 0;
}
