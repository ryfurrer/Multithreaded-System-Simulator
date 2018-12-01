//
// Created by ryfur on 2018-11-30.
//

#include <time.h>
#include <zconf.h>
#include <cstdlib>
#include <pthread.h>
#include <cstring>
#include <cerrno>
#include <cstdio>

#include "util.h"

/**
 * Delays a thread by `delay` milliseconds
 * @param delay
 */
void delay(uint delay) {
    //from lab experiments on eClass
    struct timespec interval;
    interval.tv_sec = (long) delay / 1000;
    interval.tv_nsec = (long) ((delay % 1000) * 1000000);
    if (nanosleep(&interval, NULL) < 0)
        printf("warning: delay: %s\n", strerror(errno));
}

/**
 * Initalizes a mutex
 * @param mutex
 */
void mutex_init(pthread_mutex_t *mutex) {
    //from lab exercise on eclass
    int rval = pthread_mutex_init(mutex, NULL);
    if (rval) {
        fprintf(stderr, "mutex_init: %s\n", strerror(rval));
        exit(EXIT_FAILURE);
    }
}


/**
 * Locks a mutex
 * @param mutex
 */
void mutex_lock(pthread_mutex_t *mutex) {
    //from lab exercise on eclass
    int rval = pthread_mutex_lock(mutex);
    if (rval) {
        fprintf(stderr, "mutex_lock: %s\n", strerror(rval));
        exit(EXIT_FAILURE);
    }
}

/**
 * Unlocks a mutex
 * @param mutex
 */
void mutex_unlock(pthread_mutex_t *mutex) {
    //from lab exercise on eclass
    int rval = pthread_mutex_unlock(mutex);
    if (rval) {
        fprintf(stderr, "mutex_unlock: %s\n", strerror(rval));
        exit(EXIT_FAILURE);
    }
}
