//Copyright 2018 Ryan Furrer
#include "parsers.h"
#include "taskManager.h"
#include "util.h"
#include <string.h>
#include <sys/times.h>

// GLOBAL VARS
std::map<std::string, int> resourceMap;
std::vector<TASK> taskList;
pthread_t threads[NTASKS];
//GLOBAL VARS END

uint ITERATIONS = 0;

clock_t START = 0;
clock_t END;
long _CLK_TCK = 0;

pthread_mutex_t threadMutex;
pthread_mutex_t iterationMutex;
pthread_mutex_t monitorMutex;

float getTime() {
    tms tmsend;
    END = times(&tmsend);
    return (END - START) / (double) _CLK_TCK * 1000;
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

    printf("Monitor: [WAIT] %s\n\t [RUN] %s\n\t [IDLE] %s\n\n", waitTasks.c_str(),
           runTasks.c_str(), idleTasks.c_str());
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
/**
 * Prints to screen the status of tasks (WAITING, RUNNING, IDLE) every `interval` milliseconds
 * @return
 */
void *monitorThread(void *arg) {
    auto monitorTime = (long) arg;
    while (true) {
        delay(monitorTime);
        mutex_lock(&monitorMutex);
        printMonitor();
        mutex_unlock(&monitorMutex);
    }
}

#pragma clang diagnostic pop

/**
 * Returns whether all resources for a task are available
 * @param task {@code TASK *}
 * @return {@code bool}
 */
bool checkResourcesAvailable(TASK *task) {
    for (auto &resourceString : task->reqResources) {
        char *saveptr;
        char resource[RESOURCE_MAX_LEN];

        strcpy(resource, resourceString.c_str());

        char *resName = strtok_r(resource, ":", &saveptr);
        int resNumber = atoi(strtok_r(nullptr, ":", &saveptr));
//        printf("Need %i, %i avail\n", resNumber, resourceMap[resName]);

        if (resourceMap[resName] < resNumber) {
            printf("\n\nNo resource %s", resName);
            return false;
        }
    }
    return true;
}


/**
 * Handles switching a task's status with restriction that tasks cannot switch
 * if the monitor is printing
 * @param task
 * @param status
 */
void switchStatus(TASK *task, STATUS status) {
    mutex_lock(&monitorMutex);
    task->status = status;
    mutex_unlock(&monitorMutex);
}

void waitForResources(TASK *task) { // todo - fix does not work correctly
    switchStatus(task, WAIT);
    bool resAvailable = false;
    while (!resAvailable) {
        mutex_lock(&iterationMutex); // resourceMap needs to be consistent across threads
        resAvailable = checkResourcesAvailable(task);
        mutex_unlock(&iterationMutex);
        if (!resAvailable) {
            delay(20);
        }
    }
}

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

void adjustResources(TASK *task, int (*operation)(int, int)) {
    for (auto &resourceString : task->reqResources) {
        char *saveptr;
        char resource[RESOURCE_MAX_LEN];

        strcpy(resource, resourceString.c_str());
        char *resName = strtok_r(resource, ":", &saveptr);
        int resNumber = atoi(strtok_r(nullptr, ":", &saveptr));
        int currentValue = resourceMap[resName];

        resourceMap[resName] = operation(currentValue, resNumber);
    }
}


void procureResources(TASK *task) {
    mutex_lock(&iterationMutex); // resourceMap needs to be consistent across threads
    adjustResources(task, sub);
    mutex_unlock(&iterationMutex);
}

void releaseResources(TASK *task) {
    mutex_lock(&iterationMutex); // resourceMap needs to be consistent across threads
    adjustResources(task, add);
    mutex_unlock(&iterationMutex);
}


void runTaskIteration(TASK *task) {
    procureResources(task);
    delay(task->busyTime);
    task->totalBusyTime += task->busyTime;
    releaseResources(task);
}

void doTaskIdle(TASK *task) {
    delay(task->idleTime);
    task->totalIdleTime += task->idleTime;
}


void runTask(TASK *task) { // todo
    clock_t iterStart, iterWait;
    struct tms tmsIterStart, tmsIterWait;
    uint iterCount = 0;

    while (iterCount != ITERATIONS) {
        switchStatus(task, WAIT);
        iterStart = times(&tmsIterStart);
        waitForResources(task);
        iterWait = times(&tmsIterWait);
//        printf("Waited %li\n", (iterWait - iterStart) * 1000 / _CLK_TCK);
        task->totalWaitTime += (iterWait - iterStart) * 1000 / _CLK_TCK;

        switchStatus(task, RUN);
        runTaskIteration(task);

        switchStatus(task, IDLE);
        doTaskIdle(task);

        task->timesExecuted += 1;
        iterCount++;
        printf("task: %s (tid= %lu, iter= %d, time= %.0f msec) \n", task->name, pthread_self(),
               iterCount, getTime());
    }
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
           "Running time= %.0f msec\n", systemResources.c_str(), systemTasks.c_str(), getTime());
}

void *task_start_routine(void *arg) {
    threads[(long) arg] = pthread_self();
    for (auto &task : taskList) {
        if (task.assigned) {
            continue;
        }
//        printf("%s\n", task.name);
        task.assigned = true;
        mutex_unlock(&threadMutex);
        runTask(&task);
        break;
    }
    pthread_exit(nullptr);
}

void createMonitorThread(long time) {
    do_pthread_create_with_error_check(&monitorThread, (void *) time);
}

void createTaskThreads() {
    for (unsigned long i = 0; i < taskList.size(); i++) {
        mutex_lock(&threadMutex);
        do_pthread_create_with_error_check(task_start_routine, (void *) i);
    }
}

void waitForTaskTermination() {
    for (unsigned int i = 0; i < taskList.size(); i++) {
        do_pthread_join_with_error_check(&threads[i]);
    }
}

int run(CLI_ARGS args) {
    tms tmsstart;
    ITERATIONS = args.iterations;

    if ((_CLK_TCK = sysconf(_SC_CLK_TCK)) < 0) {
        printf("ERROR: getting sysconfig clock tick\n");
        exit(-1);
    }

    printf("Trying to read File...\n");
    readInputFile(args.inputFile);

    START = times(&tmsstart);

    printf("Initializing Mutexes...\n");
    mutex_init(&threadMutex);
    mutex_init(&iterationMutex);
    mutex_init(&monitorMutex);

    printf("Creating monitor thread...\n");
    createMonitorThread(args.monitorTime);
    printf("Creating task threads...\n");
    createTaskThreads();
    delay(400); //delay long enough for threads array to be initialized

    printf("Waiting on tasks...\n");
    waitForTaskTermination();

    printf("Tasks Finished...\n");
    printTerminationInfo();
    return EXIT_SUCCESS;
}
