
#ifndef TASK_H
#define TASK_H
#include <chrono>
#include <string>

#include "sysThread.h"


using std::chrono::milliseconds;
using std::string;


class Task: public SysThread {
public:
    explicit Task(uint taskID);

    uint getTaskIDNum() const;

    string getTaskIDString() const;

    pthread_t getTID();

    uint getIterNum();

    milliseconds getTime();

    void completePrint();

private:
    uint taskIDNum;

    string taskIDString;

    pthread_t tid;

    uint iterNum;

    milliseconds time;
};

#endif