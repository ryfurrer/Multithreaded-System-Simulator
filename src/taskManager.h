//
// Created by ryfur on 2018-11-29.
//

#ifndef MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H
#define MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H

#include "parsers.h"
// GLOBAL VARS
extern pthread_mutex_t threadMutex;
extern pthread_mutex_t iterationMutex;
extern pthread_mutex_t monitorMutex;

int start(CLI_ARGS args);

#endif //MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H
