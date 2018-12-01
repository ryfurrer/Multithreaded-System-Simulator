
#ifndef TASK_H
#define TASK_H
#include <string>

using std::string;

typedef struct {
    int taskIDNum;
    string taskIDString;
    pthread_t tid;
    uint iterNum;
    int time;
} TASK;

#endif