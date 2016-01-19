/*
 * =====================================================================================
 *
 *       Filename:  debug.h
 *
 *    Description:  debug utilities based on http://c.learncodethehardway.org/book/ex20.html
 *
 *        Version:  1.0
 *        Created:  01/19/2016 03:33:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jignesh Darji (jignesh), jndarji@ncsu.edu
 *   Organization:  North Carolina State University
 *
 * =====================================================================================
 */


#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define log_err(M, ...) fprintf(stderr, "[ERR] %s | %s | %s | " M "\n", __DATE__, __TIME__, __FUNCTION__, ##__VA_ARGS__)
#define log_wrn(M, ...) fprintf(stderr, "[WRN] %s | %s | %s | " M "\n", __DATE__, __TIME__, __FUNCTION__, ##__VA_ARGS__)
#define log_inf(M, ...) fprintf(stderr, "[INF] %s | %s | %s | " M "\n", __DATE__, __TIME__, __FUNCTION__, ##__VA_ARGS__)
#define log_dbg(M, ...) fprintf(stderr, "[DBG] %s | %s | %s | " M "\n", __DATE__, __TIME__, __FUNCTION__, ##__VA_ARGS__)

#endif
