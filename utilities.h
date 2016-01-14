#include <string>
#include <cstdio>
#include <ctime>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <fstream>
extern "C"
{
    #include <pthread.h>
}

using namespace std;

#ifndef __JUTILITIES__
#define __JUTILITIES__

static pthread_mutex_t logMutex;
static time_t log_timestamp_raw;
static string timestamp;
//Logging related
#define LOG(x) pthread_mutex_lock(&logMutex); \
    time(&log_timestamp_raw); \
    timestamp = ctime(&log_timestamp_raw); \
    cout << timestamp.substr(0, timestamp.length() - 1) << " | " \
    << __PRETTY_FUNCTION__ << " "  << " | " << x << endl; \
    pthread_mutex_unlock(&logMutex);

#define LOG_INFO(x) pthread_mutex_lock(&logMutex); \
    time(&log_timestamp_raw); \
    timestamp = ctime(&log_timestamp_raw); \
    cout << timestamp.substr(0, timestamp.length() - 1) << " | " \
    << "INFO" << " | " \
    << __PRETTY_FUNCTION__ << " "  << " | " << x << endl; \
    pthread_mutex_unlock(&logMutex);

#define LOG_ERR(x) pthread_mutex_lock(&logMutex); \
    time(&log_timestamp_raw); \
    timestamp = ctime(&log_timestamp_raw); \
    cout << timestamp.substr(0, timestamp.length() - 1) << " | " \
    << "ERROR" << " | " \
    << __PRETTY_FUNCTION__ << " "  << " | " << x << endl; \
    pthread_mutex_unlock(&logMutex);

#define LOG_DBG(x) pthread_mutex_lock(&logMutex); \
    time(&log_timestamp_raw); \
    timestamp = ctime(&log_timestamp_raw); \
    cout << timestamp.substr(0, timestamp.length() - 1) << " | " \
    << "DEBUG" << " | " \
    << __PRETTY_FUNCTION__ << " "  << " | " << x << endl; \
    pthread_mutex_unlock(&logMutex);

#define LOG_PERF(x) pthread_mutex_lock(&logMutex); \
    time(&log_timestamp_raw); \
    timestamp = ctime(&log_timestamp_raw); \
    cout << timestamp.substr(0, timestamp.length() - 1) << " | " \
    << "PERF" << " | " \
    << __PRETTY_FUNCTION__ << " "  << " | " << x << endl; \
    pthread_mutex_unlock(&logMutex);



enum ReturnValueE
{
    SUCCESS = 0,
    FAILURE = -1
};


//Error check macros
#define JCHECK_ERROR(func, arg) int retVal; \
                                        if(SUCCESS != ( retVal = (func arg))) \
                                            LOG_ERR("failed in " #func " " #arg);

#define JCHECK_ERROR_ASSERT(func, arg) if(SUCCESS != (func arg)) { \
                                        LOG_ERR("failed in " #func " " #arg); \
                                        assert(0); \
                                        }

#define JCHECK_ERROR_MSG(func, arg, x) if(SUCCESS != (func arg)) \
                                            LOG_ERR("failed in " #func " " #arg " ERR_MSG: " << x);

#define JCHECK_ERROR_MSG_ASSERT(func, arg, x) if(SUCCESS != (func arg)) { \
                                                LOG_ERR("failed in" << ##func << " " <<##arg << " MSG: " << x); \
                                                assert(0); \
                                            }

//Performance macros
#define JCHECK_PERF_AND_ERROR(func, arg) clock_t start; double duration; \
    start = clock(); \
    JCHECK_ERROR(func, arg); \
    duration = (clock() - start ) / ((double) CLOCKS_PER_SEC); \
    LOG_PERF(#func " " #arg << " took " << duration << " seconds");
 
#endif /* __JUTILITIES__ */
