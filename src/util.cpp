//Copyright 2018 Ryan Furrer

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
void delay(int delay) {
    //from http://webdocs.cs.ualberta.ca/~c379/F18/379only/raceC.c
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
    //from http://webdocs.cs.ualberta.ca/~c379/F18/379only/raceC.c
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
    //from http://webdocs.cs.ualberta.ca/~c379/F18/379only/raceC.c
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
    //from http://webdocs.cs.ualberta.ca/~c379/F18/379only/raceC.c
    int rval = pthread_mutex_unlock(mutex);
    if (rval) {
        fprintf(stderr, "mutex_unlock: %s\n", strerror(rval));
        exit(EXIT_FAILURE);
    }
}

void do_pthread_join_with_error_check(pthread_t* pthread) {
    int rval = pthread_join(*pthread, NULL);
    if (rval) {
        fprintf(stderr, "\n** pthread_join: %s\n", strerror(rval));
        exit(EXIT_FAILURE);
    }
}

/**
 * Before returning, a successful call to pthread_create() stores the ID of the new thread in the
 * buffer pointed to by thread; this identifier is used to refer to the thread in subsequent calls
 * to other pthreads functions.
 * @param f
 */
void do_pthread_create_with_error_check(void *(*start_function)(void *), void *arg) {
    pthread_t threadID;
    int rval = pthread_create(&threadID, NULL, start_function, arg);
    //attr is NULL, so the thread is created with default attributes.
    if (rval) {
        fprintf(stderr, "pthread_create: %s\n", strerror(rval));
        exit(1);
    }
}
