//
// Created by ryfur on 2018-11-29.
//

#ifndef MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H
#define MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H

#include <fstream>
#include <string>
#include <chrono>
#include <vector>

#include "monitor_thread.h"
#include "task_thread.h"

using std::string;
using std::chrono::milliseconds;
using std::ifstream;
using std::vector;

typedef vector<Task> TasksList;

class ThreadManager {
public:
    ThreadManager(const string &inputFile, const milliseconds &monitorTime,
                  const uint &nIter);

    milliseconds getMonitorTime();

    uint getNIter() const;

    void start();

    void print();

    void listResources();

    void listTasks();

    void listElapsedTime();

private:

    string inputFile;

    milliseconds monitorTime;

    milliseconds startTime;

    uint nIter;

    ifstream inputFileStream;

    MonitorThread monitorThread;

    TasksList taskThreads;

    void checkInputFileLine(ifstream &inputFileStream);

};

#endif //MULTITHREADED_SYSTEM_SIMULATOR_TASKMANAGER_H
