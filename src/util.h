//
// Created by ryfur on 2018-11-30.
//

#ifndef MULTITHREADED_SYSTEM_SIMULATOR_UTIL_H
#define MULTITHREADED_SYSTEM_SIMULATOR_UTIL_H

#include <zconf.h>

#define NTASKS 25
#define NRES_TYPES 10

void delay(int delay);

void mutex_init(pthread_mutex_t* mutex);

void mutex_lock(pthread_mutex_t* mutex);

void mutex_unlock(pthread_mutex_t* mutex);

#endif //MULTITHREADED_SYSTEM_SIMULATOR_UTIL_H
