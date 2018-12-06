//Copyright 2018 Ryan Furrer
#ifndef _PARSERS_
#define _PARSERS_

#include <chrono>
#include <string>
#include <tuple>
#include <vector>
#include <errno.h>

#define RESOURCE_FLAG "resources"
#define TASK_FLAG "task"
#define COMMENT_FLAG "#"

#define RUN_FLAG "RUN"
#define IDLE_FLAG "IDLE"
#define WAIT_FLAG "WAIT"

#define RESOURCE_MAX_LEN 32


using std::string;
using std::vector;

typedef enum {
    INVALID_LINE, COMMENT_LINE, RESOURCE_LINE, TASK_LINE
} LINE_TYPES;

typedef struct {
    string inputFile;
    long monitorTime;
    uint iterations;
} CLI_ARGS;

std::string getFormattedSystemResourceInfo();

std::string getFormattedSystemTaskInfo();

int validateArgs(int argc, char *argv[]);

CLI_ARGS parseArgs(int argc, char *argv[]);

void readInputFile(const string &inputFile);

#endif
