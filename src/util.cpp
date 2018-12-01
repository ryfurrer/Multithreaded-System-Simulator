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
 * @param milliseconds
 */
void delay(uint delay) {
}

/**
 * Initalizes a mutex
 * @param mutex
 */
void mutex_init(pthread_mutex_t* mutex) {
}

/**
 * Locks a mutex
 * @param mutex
 */
void mutex_lock(pthread_mutex_t* mutex){
}

/**
 * Unlocks a mutex
 * @param mutex
 */
void mutex_unlock(pthread_mutex_t* mutex) {
}