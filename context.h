/*
 * =====================================================================================
 *
 *       Filename:  context.h
 *
 *    Description:  a high-level utility for using the ucontext environment
 *
 *        Version:  1.0
 *        Created:  01/20/2016 01:52:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */

#ifndef CONTEXT_H
#define CONTEXT_H

#include <ucontext.h>
#include "debug.h"
#include "thread.h"

static void context_make(ucontext_t *t, void (*func)(void), void *args, unsigned int stack_size)
{
    log_inf("creating a context with stack size: %d", stack_size);
    
    getcontext(t);
    
    t->uc_link              = 0;
    t->uc_stack.ss_sp       = malloc(stack_size);
    t->uc_stack.ss_size     = stack_size;
    t->uc_stack.ss_flags    = 0;
    
    makecontext(t, func, 1, args);
    log_inf("end");
}

static void context_swap(ucontext_t *prev, ucontext_t *next)
{
    log_inf("begin");
    swapcontext(prev, next);
    log_inf("end");
}

#endif /*CONTEXT_H*/
