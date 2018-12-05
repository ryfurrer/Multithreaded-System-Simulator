
#include "parsers.h"
#include "taskManager.h"
#include "task.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>

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
}

/**
 * Prints to screen the status of tasks (WAITING, RUNNING, IDLE) every `interval` milliseconds
 * @return
 */
void *monitorThread(void *arg) {
    long monitorTime = (long)arg;
    while (true) {
        delay(monitorTime);
        //lock
        printMonitor();
        //unlock
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

void printTerminationInfo() {
}

void runIterations(TASK* task) {

}

void do_pthread_create_with_error_check(int index){
//    mutex_lock();
    int rval = 1;
//    int rval = pthread_create();
    if (rval) {
        fprintf(stderr, "pthread_create: %s\n", strerror(rval));
        exit(1);
    }
}

void createMonitorThread(){
//    do_pthread_create_with_error_check
}

void createTaskThreads(){
    for (long i = 0; i <NTASKS; i++) {
//        do_pthread_create_with_error_check
    }
}

void do_pthread_join_with_error_check(int index){
//    int rval = pthread_join(nullptr, NULL);
//    if (rval) {
//        fprintf(stderr, "\n** pthread_join: %s\n", strerror(rval));
//        exit(EXIT_FAILURE);
//    }
}

void waitForTaskThreads(){
    for (long i = 0; i <NTASKS; i++) {
//        do_pthread_join_with_error_check
    }
}

int start(CLI_ARGS args) {
    prinf("Reading File...\n");
    readInputFile(args.inputFile);

    prinf("Doing mutex stuff...\n");
    mutex_init(&threadMutex);
    mutex_init(&iterationMutex);
    mutex_init(&monitorMutex);

    prinf("Creating monitor thread...\n");

    createMonitorThread();
    delay(400);

    prinf("Doing tasks...\n");

    waitForTaskThreads();

    printf("\n\nThreads Finished...  Terminating...\n");
    printTerminationInfo();
    return EXIT_SUCCESS;
}