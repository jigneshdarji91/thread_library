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

#include "debug.h"
#include "semaphore.h"

typedef enum thread_state_t
{
    THREAD_READY = 0,   /*ready  */
    THREAD_RUNNING,     /*running*/
    THREAD_BLOCK         /*waiting*/
} thread_state_t; 

typedef struct thread_t
{
    //needs a context, state, next pointer, and child pointer
    //http://www.gnu.org/software/libc/manual/html_node/System-V-contexts.html    
    
    ucontext_t context;

    struct thread_t* parent;
    struct queue_t* children;
    struct queue_t* block_th;

    thread_state_t state;

    semaphore_t *block_sem;

} thread_t;
