//Copyright 2018 Ryan Furrer

#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <stdlib.h>
#include <string.h>
#include "parsers.h"
#include "util.h"
#include "task.h"
#include "taskManager.h"


using namespace std;

/**
 * Checks for proper command line arguments and returns 0 on valid
 * args or an errno code
 * @param argc
 * @param argv
 * @return status
 */
int validateArgs(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Invalid number of arguments.\n");
        return EINVAL;
    }

    int monitorTime = atoi(argv[2]);
    int iterations = atoi(argv[3]);

    if (monitorTime < 0) {
        printf("monitorTime invalid\n");
        return EINVAL;
    } else if (monitorTime > 100000) {
        printf("monitorTime invalid\n");
        return EOVERFLOW;
    }

    if (iterations < 0) {
        printf("NITER invalid\n");
        return EINVAL;
    } else if (iterations > 100000) {
        printf("NITER invalid\n");
        return EOVERFLOW;
    }

    return 0;
}

/**
 * Converts args into their types and returns them in a struct
 * @param argc
 * @param argv
 * @return {@code CLI_ARGS} args
 */
CLI_ARGS parseArgs(int argc, char *argv[]) {
    CLI_ARGS args;
    args.inputFile = argv[1];
    args.monitorTime = (atoi(argv[2]));
    args.iterations = (atoi(argv[3]));
    return args;
}

std::string getFormattedSystemResourceInfo() {
    std::map<string, int>::iterator itr;
    std::string systemResources;
    for (itr = resourceMap.begin(); itr != resourceMap.end(); itr++) {
        char buffer[RESOURCE_MAX_LEN];
        int val = sprintf(buffer, "\t%s: (maxAvail=   %i, held=   0) \n", (itr->first).c_str(),
                          resourceMap[itr->first]);
        if (!val) {
            printf("Failed to print term info");
            exit(EXIT_FAILURE);
        }
        systemResources.append(buffer);
    }
    return systemResources;
}

std::string getFormattedSystemTaskInfo() {  //TODO: refactor to be clearer
    std::string systemTasks;
    for (unsigned int i = 0; i < taskList.size(); i++) {
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
        systemTasks.append(buffer);
        sprintf(buffer, "\t (tid= %lu)\n", threads[i]);
        systemTasks.append(buffer);
        for (auto &reqResource : taskList.at(i).reqResources) {
            char *saveptr;
            char *resourceName;
            int resourcesNeeded;
            char resourceString[50];
            strcpy(resourceString, reqResource.c_str());
            resourceName = strtok_r(resourceString, ":", &saveptr);
            resourcesNeeded = atoi(strtok_r(nullptr, ":", &saveptr));

            sprintf(buffer, "\t %s: (needed=\t%d, held= 0)\n", resourceName, resourcesNeeded);
            systemTasks.append(buffer);
        }
        sprintf(buffer, "\t (RUN: %d times, WAIT: %lu msec)\n\n", taskList.at(i).timesExecuted,
                taskList.at(i).totalWaitTime);
        systemTasks.append(buffer);
    }
    return systemTasks;
}

/**
 * Adds resource to the map
 * @param arg
 */
void parseResourceArg(const string &arg) {
    char *saveptr;
    char nameValuePair[RESOURCE_MAX_LEN];
    int number;

    strcpy(nameValuePair, arg.c_str());

    string name(strtok_r(nameValuePair, ":", &saveptr));
    number = atoi(strtok_r(nullptr, ":", &saveptr));

    resourceMap[name] = number;
}

/**
 * Convert a resources line into a map of resource
 * @param line
 */
void parseResourcesLine(const string &line) {
    char *temp;
    char *saveptr;
    char cline[100];
    strcpy(cline, line.c_str());
    vector<char *> resourceStrings;

    //go to first name:value pair
    temp = strtok_r(cline, " ", &saveptr);
    temp = strtok_r(nullptr, " ", &saveptr);
    //iterate through the rest
    while (temp != nullptr) {
        resourceStrings.push_back(temp);
        temp = strtok_r(nullptr, " ", &saveptr);
    }

    for (auto &resourceString : resourceStrings) {
        parseResourceArg(resourceString);
    }
}

/**
 * converts a task line to an item on the task list
 * @param line
 */
void parseTaskLine(const string &line) {
    char *saveptr;
    char *token;
    char cline[100];
    strcpy(cline, line.c_str());
    TASK newTask;
    newTask.status = IDLE;
    newTask.totalIdleTime = 0;
    newTask.totalBusyTime = 0;
    newTask.totalWaitTime = 0;
    newTask.timesExecuted = 0;

    token = strtok_r(cline, " ", &saveptr); //flag
    token = strtok_r(nullptr, " ", &saveptr); //id
    strcpy(newTask.name, token);
    token = strtok_r(nullptr, " ", &saveptr); //busy
    newTask.busyTime = atoi(token);
    token = strtok_r(nullptr, " ", &saveptr); //idle
    newTask.idleTime = atoi(token);

    // Resource requirements
    token = strtok_r(nullptr, " ", &saveptr);
    newTask.assigned = false;
    while (token != nullptr) {
        string str(token);
        newTask.reqResources.push_back(str);
        token = strtok_r(nullptr, " ", &saveptr);
    }

    //add to task list
    taskList.push_back(newTask);
}

LINE_TYPES getInputFileLineType(const string &line) {
    const char *flag;
    if (!line.length() || line[0] == '#' || line[0] == '\r' || line[0] == '\n') {
        return COMMENT_LINE;
    }

    //determine what the leading keyword is (i.e. the input file line flag)
    istringstream iss(line);
    vector <string> items((istream_iterator<string>(iss)), istream_iterator<string>());
    flag = items.at(0).c_str();
    if (strcmp(flag, RESOURCE_FLAG) == 0) {
        return RESOURCE_LINE;
    }
    if (strcmp(flag, TASK_FLAG) == 0) {
        return TASK_LINE;
    }

    return INVALID_LINE;
}

void parseInputFileLine(const string &line) {
    switch (getInputFileLineType(line)) {
        case TASK_LINE:
            printf("Parsing task...\n");
            parseTaskLine(line);
            break;
        case RESOURCE_LINE:
            printf("Parsing resources...\n");
            parseResourcesLine(line);
            break;
        case COMMENT_LINE:
            printf("Ignoring blank/comment line...\n");
            //ignore any comments or white lines
            break;
        default : // INVALID_LINE
            printf("ERROR: INVALID LINE: %s\n", line.c_str());
            exit(EINVAL);
    }
}

void readInputFile(const string &inputFile) {
    string line; //line read from file

    ifstream file(inputFile);
    if (file.fail()) {
        printf("FILE DOES NOT EXIST\n");
        exit(EXIT_FAILURE);
    }

    if (file.good()) {
        printf("File good...\n");
        while (getline(file, line)) {
            parseInputFileLine(line);
        }
    }
}
