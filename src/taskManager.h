//Copyright 2018 Ryan Furrer

#ifndef MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H
#define MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H

#include "parsers.h"
#include "task.h"
#include <map>
#include <string>

// GLOBAL VARS
extern std::map<std::string, int> resourceMap;
extern std::vector <TASK> taskList;
extern pthread_t threads[NTASKS];
//GLOBAL VARS END

int start(CLI_ARGS args);

#endif //MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H
