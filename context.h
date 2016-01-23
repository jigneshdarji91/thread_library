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

void context_make(ucontext_t *t, void (*func)(void), void *args, unsigned int stack_size);
void context_swap(ucontext_t *prev, ucontext_t *next);

#endif /*CONTEXT_H*/
