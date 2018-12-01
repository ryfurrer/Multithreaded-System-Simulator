
#ifndef TASK_H
#define TASK_H
#include <string>

using std::string;

typedef struct {
    uint taskIDNum;
    string taskIDString;
    pthread_t tid;
    uint iterNum;
    uint time;
} TASK;

#endif