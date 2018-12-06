//Copyright 2018 Ryan Furrer
#ifndef TASK_H
#define TASK_H
#include <string>
#include <vector>

#define NTASKS 25
#define NRES_TYPES 10

using std::string;

typedef enum {WAIT, RUN, IDLE} STATUS;

typedef struct {
    char name[100];
    int busyTime;
    int idleTime;
    long totalBusyTime;
    long totalIdleTime;
    long totalWaitTime;
    vector<string> reqResources;
    bool assigned;
    int timesExecuted;
    STATUS status;
} TASK;

#endif