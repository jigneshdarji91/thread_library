/*
 * =====================================================================================
 *
 *       Filename:  threading.c
 *
 *    Description:  learning to swap contexts
 *
 *        Version:  1.0
 *        Created:  01/14/2016 02:37:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */

#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 64000

typedef struct MyThread 
{
    ucontext_t context;
} MyThread;

MyThread MyThreadCreate (void(*start_funct)(void *), void *args)
{
    MyThread *t = malloc(sizeof(MyThread));
    getcontext(&t->context);
    t->context.uc_link=0;
    t->context.uc_stack.ss_sp=malloc(STACK_SIZE);
    t->context.uc_stack.ss_size=STACK_SIZE;
    t->context.uc_stack.ss_flags=0;
    makecontext(&t->context, (void*)&start_funct, 0);
}

void fibonacci(int n)
{
    int a = 1, b = 1, c = 0;
    for(int i = 2; i < n; i++)
    {
        c += b;
        a = b;
        b = c;
    }
    printf("fib(%d)=%d", n, c);
}

void hello_world()
{
    printf("Hello! World.");
}

int main()
{
    
}
