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

using namespace std;

class Context{
    public:
        static void Make(ucontext_t& /* t*/, void (*func)(void), void* /*args*/, unsigned int /* stack_size*/);
        static void Swap(ucontext_t& /* prev*/, ucontext_t& /* next*/);
        static void Set(ucontext_t& /*new_context*/);
};

#endif /*CONTEXT_H*/
