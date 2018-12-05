#include "parsers.h"
#include "util.h"
#include "task.h"
#include "taskManager.h"
#include <cstring>
#include <iostream>
#include <fstream>

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


uint parseTaskID(const string &taskIDString) {
    return 0;
}

/**
 * Adds resource to the map
 * @param arg
 */
void parseResourceArg(const string &arg) {
    char nameValuePair[RESOURCE_MAX_LEN];
    int number;

    strcpy(nameValuePair, arg.c_str());

    string name(strtok(nameValuePair, ":"));
    number = atoi(strtok(nullptr, ":"));

    resourceMap[name] = number;
}

/**
 * Convert a resources line into a map of resource
 * @param line
 */
void parseResourcesLine(const string &line) {
    char* temp;
    char cline[100];
    strcpy(cline, line.c_str());
    vector<char*> resourceStrings;

    //go to first name:value pair
    temp = strtok(cline, " ");
    temp = strtok(nullptr, " ");
    //iterate through the rest
    while (temp != nullptr) {
        resourceStrings.push_back(temp);
        temp = strtok(nullptr, " ");
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
    char* token;
    char cline[100];
    strcpy(cline, line.c_str());
    TASK newTask;
    newTask.status = IDLE;
    newTask.totalIdleTime = 0;
    newTask.totalBusyTime = 0;
    newTask.totalWaitTime = 0;
    newTask.timesExecuted = 0;

    token = strtok(cline, " "); //flag
    token = strtok(nullptr, " "); //id
    strcpy(newTask.name, token);
    token = strtok(nullptr, " "); //busy
    newTask.busyTime = atoi(token);
    token = strtok(nullptr, " "); //idle
    newTask.idleTime = atoi(token);

    // Resource requirements
    token = strtok(nullptr, " ");
    newTask.assigned = false;
    while (token != nullptr){
        string str(token);
        newTask.reqResources.push_back(str);
        token = strtok(nullptr, " ");
    }

    //add to task list
    taskList.push_back(newTask);
}

LINE_TYPES getInputFileLineType(const string &line) {
    char cline[100];
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n') {
        return COMMENT_LINE;
    }

    //determine what the leading keyword is (i.e. the input file line flag)
    strcpy(cline, line.c_str());
    flag = strtok(cline, " ");
    if ((strcmp(flag, RESOURCE_FLAG) == 0) {
        return LINE_TYPES.RESOURCE_LINE;
    }
    if ((strcmp(flag, TASK_FLAG) == 0) {
        return TASK_LINE;
    }

    return INVALID_LINE;
}

void parseInputFileLine(const string &line) {
    switch(getInputFileLineType(line)) {
        case TASK_LINE:
            parseTaskLine(line);
            break;
        case RESOURCE_LINE:
            parseResourcesLine(line);
            break;
        case COMMENT_LINE:
            //ignore any comments or white lines
            break;
        default : // INVALID_LINE
            printf("ERROR: INVALID LINE: %s\n", line);
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
        while (getline(file, line)) {
            parseInputFileLine(line);
        }
    }
}
