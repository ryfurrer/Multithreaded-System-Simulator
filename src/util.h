//Copyright 2018 Ryan Furrer

#ifndef MULTITHREADED_SYSTEM_SIMULATOR_UTIL_H
#define MULTITHREADED_SYSTEM_SIMULATOR_UTIL_H

#include <zconf.h>

void delay(int delay);

void mutex_init(pthread_mutex_t* mutex);

void mutex_lock(pthread_mutex_t* mutex);

void mutex_unlock(pthread_mutex_t* mutex);

#endif //MULTITHREADED_SYSTEM_SIMULATOR_UTIL_H
