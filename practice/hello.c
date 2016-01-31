/*
 * =====================================================================================
 *
 *       Filename:  hello.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/31/2016 05:31:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */

#include <malloc.h>

int foo(int& num)
{
    printf("num: %d", num);
    return 0;
}

int main()
{
    int x = 10;
    foo(x);
}
