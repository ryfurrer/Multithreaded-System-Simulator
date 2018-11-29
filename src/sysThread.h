//
// Created by ryfur on 2018-11-29.
//

#ifndef MULTITHREADED_SYSTEM_SIMULATOR_SYSTHREAD_H
#define MULTITHREADED_SYSTEM_SIMULATOR_SYSTHREAD_H

#include <thread>
#include <chrono>
#include <sstream>

class SysThread {
public:
    explicit ManagedThread();

    void Start();

    void Stop();

private:
};

#endif //MULTITHREADED_SYSTEM_SIMULATOR_SYSTHREAD_H
