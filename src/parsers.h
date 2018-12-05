
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
#define RESOURCE_MAX_LEN 32


using std::string;
using std::vector;

typedef enum {INVALID_LINE, COMMENT_LINE, RESOURCE_LINE, TASK_LINE} LINE_TYPES;

typedef struct {
    string inputFile;
    long monitorTime;
    uint iterations;
} CLI_ARGS;

typedef struct {
    string name;
    vector<uint> value;
} ResourceArg;

typedef struct {
    string flag;
    vector<ResourceArg> resources;
} ResourcesLine;

typedef struct {
    string flag;
    uint taskID;
    uint busy;
    uint idle;
    vector<ResourceArg> resources;
} TaskLine;

typedef union {
    ResourceArg resourceArg;
    ResourcesLine resourcesLine;
    TaskLine taskLine;
} LINE;

typedef struct {
    LINE_TYPES type;
    LINE line;
} FRAME;

std::string getFormattedSystemResourceInfo();

std::string getFormattedSystemTaskInfo();

int validateArgs(int argc, char *argv[]);

CLI_ARGS parseArgs(int argc, char *argv[]);

void readInputFile(const string &inputFile);

#endif