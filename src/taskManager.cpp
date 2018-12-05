
#include "parsers.h"
#include "taskManager.h"
#include "task.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>

#define RUN_FLAG "RUN"
#define IDLE_FLAG "IDLE"
#define WAIT_FLAG "WAIT"

// GLOBAL VARS
std::map<std::string, int> resourceMap;
std::vector<TASK> taskList;
//GLOBAL VARS END

clock_t START = 0;
clock_t END;

tms tmsstart, tmsend;

pthread_mutex_t threadMutex;
pthread_mutex_t iterationMutex;
pthread_mutex_t monitorMutex;

float getTime() {

    END = times(&tmsend);
    return (END - START);
}

/**
 * Prints to screen the status of tasks (WAITING, RUNNING, IDLE)
 */
void printMonitor() {
    std::string waitTasks;
    std::string runTasks;
    std::string idleTasks;

    for (auto &task : taskList) {
        switch (task.status) {
            case WAIT:
                waitTasks.append(task.name);
                waitTasks.append(" ");
                break;
            case RUN:
                runTasks.append(task.name);
                runTasks.append(" ");
            default:
                idleTasks.append(task.name);
                idleTasks.append(" ");
        }
    }

    printf("INFO: Monitor: [WAIT] %s\n\t [RUN] %s\n\t [IDLE] %s\n\n", waitTasks.c_str(),
           runTasks.c_str(), idleTasks.c_str());
}

/**
 * Prints to screen the status of tasks (WAITING, RUNNING, IDLE) every `interval` milliseconds
 * @return
 */
void *monitorThread(void *arg) {
    long monitorTime = (long)arg;
    while (true) {
        delay(monitorTime);
        mutex_lock(&monitorMutex);
        printMonitor();
        mutex_unlock(&monitorMutex);
    }
}

/**
 * Checks if all resources for a task are available
 * @param task
 * @return
 */
bool checkResources(TASK* task) {
    return false;
}

void procureResources(TASK* task) {
}

void releaseResources(TASK* task) {

}


void runTask(uint iterations, TASK* task) {

}

std::string getFormattedSystemResourceInfo() {
    std::string systemResources;
    for (itr = resourceMap.begin(); itr != resourceMap.end(); itr++) {
        char buffer[RESOURCE_MAX_LEN];
        int val = sprintf(buffer, "\t%s: (maxAvail=   %s, held=   0) \n", (itr->first).c_str(), resourceMap[itr->first]);
        if (!val) {
            printf("Failed to print term info");
            exit(EXIT_FAILURE);
        }
        systemResources.append(buffer);
    }
    return systemResources;
}

std::string getFormattedSystemTaskInfo() {
    std::string systemTasks;
    for (int i = 0; i < taskList.size(); i++)
    {
        char buffer[1024];
        char status[20];
        if (taskList.at(i).status == IDLE) {
            strcpy(status, IDLE_FLAG);
        } else if (taskList.at(i).status == WAIT) {
            strcpy(status, WAIT_FLAG);
        } else {
            strcpy(status, RUN_FLAG);
        }
        sprintf(buffer, "[%d] %s (%s, runTime= %lu msec, idleTime= %lu msec):\n", i, taskList.at(i).name, status,
               taskList.at(i).totalBusyTime, taskList.at(i).totalIdleTime);
        sprintf(buffer, "\t (tid= %lu\n", TID[i]);
        // print the required resources
        for (auto &reqResource : taskList.at(i).reqResources) {
            char* resourceName;
            int resourcesNeeded;
            char resourceString[50];
            strcpy(resourceString, reqResource.c_str());
            resourceName = strtok(resourceString, ":");
            resourcesNeeded = atoi(strtok(nullptr, ":"));

            sprintf(buffer, "\t %s: (needed=\t%d, held= 0)\n", resourceName, resourcesNeeded );
        }
        sprintf(buffer, "\t (RUN: %d times, WAIT: %lu msec\n\n", taskList.at(i).timesExecuted, taskList.at(i).totalWaitTime);
        systemTasks.append(buffer);
    }
    return systemTasks;
}

void printTerminationInfo() {
    std::string systemResources;
    std::string systemTasks;
    systemResources = getFormattedSystemResourceInfo();
    systemTasks = getFormattedSystemTaskInfo();

    printf("System Resources:\n%s"
           "\n"
           "\n"
           "System Tasks: \n%s"
           "Running time= %.0f msec", systemResources.c_str(), systemTasks.c_str(), getTime());
}

void runIterations(TASK* task) {
    //TODO
}

void *task_start_routine(void *arg) {
    TID[(long)arg] = pthread_self();
    for (auto &task : taskList) {
        if (task.assigned) {
            continue;
        }
        task.assigned = true;
        mutex_unlock(&threadMutex);
        break;
    }
    pthread_exit(nullptr);
}

void do_pthread_create_with_error_check(void *(*start_routine)){
//    mutex_lock();
    int rval = 1;
//    int rval = pthread_create();
    if (rval) {
        fprintf(stderr, "pthread_create: %s\n", strerror(rval));
        exit(1);
    }
}

void createMonitorThread(){
    do_pthread_create_with_error_check(&monitorThread);
}

void createTaskThreads(){
    for (long i = 0; i <taskList.size(); i++) {
        mutex_lock(&threadMutex);
        do_pthread_create_with_error_check(task_start_routine);
    }
}

void do_pthread_join_with_error_check(int index){
//    int rval = pthread_join(nullptr, NULL);
//    if (rval) {
//        fprintf(stderr, "\n** pthread_join: %s\n", strerror(rval));
//        exit(EXIT_FAILURE);
//    }
}

void doTaskThreads(){
    for (long i = 0; i < taskList.size(); i++) {
//        do_pthread_join_with_error_check
    }
}

int start(CLI_ARGS args) {
    printf("Reading File...\n");
    readInputFile(args.inputFile);

    printf("Doing mutex stuff...\n");
    mutex_init(&threadMutex);
    mutex_init(&iterationMutex);
    mutex_init(&monitorMutex);

    printf("Creating monitor thread...\n");

    createMonitorThread();
    printf("Creating task threads...\n");
    createTaskThreads()
    delay(400);

    printf("Doing tasks...\n");
    doTaskThreads();

    printf("Threads Finished...\nTerminating...\n");
    printTerminationInfo();
    return EXIT_SUCCESS;
}