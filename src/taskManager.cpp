
#include "parsers.h"
#include "task.h"

/**
 * Prints to screen the status of tasks (WAITING, RUNNING, IDLE)
 */
void printMonitor() {
}

/**
 * Prints to screen the status of tasks (WAITING, RUNNING, IDLE) every `interval` milliseconds
 * @return
 */
void monitorThread(uint interval) {
    //delay
    //lock
    printMonitor();
    //unlock
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


int start(CLI_ARGS args) {
    return EXIT_SUCCESS;
}