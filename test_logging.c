/*
 * =====================================================================================
 *
 *       Filename:  test_logging.c
 *
 *    Description:  testing logging 
 *
 *        Version:  1.0
 *        Created:  01/19/2016 03:54:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */

#include "debug.h"

int main()
{
    int err_no = 10;
    log_err("errno: %d", err_no);
    log_wrn("please write clean code");
}
