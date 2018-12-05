//
// Created by ryfur on 2018-11-29.
//

#ifndef MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H
#define MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H

#include "parsers.h"
#include <string>
// GLOBAL VARS
extern std::map<std::string, int> resourceMap;
extern std::vector<TASK> taskList;
//GLOBAL VARS END

//extern pthread_mutex_t threadMutex;
//extern pthread_mutex_t iterationMutex;
//extern pthread_mutex_t monitorMutex;

int start(CLI_ARGS args);

#endif //MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H
