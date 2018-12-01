
#ifndef _PARSERS_
#define _PARSERS_

#include <chrono>
#include <string>
#include <tuple>
#include <vector>

#define RESOURCE_FLAG "resources"
#define TASK_FLAG "task"
#define COMMENT_FLAG "#"


using std::string;
using std::vector;

typedef enum {INVALID_LINE, COMMENT_LINE, RESOURCE_LINE, TASK_LINE} LINE_TYPES;

typedef struct {
    string inputFile;
    uint monitorTime;
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

uint validateArgs(uint argc, char *argv[]);

CLI_ARGS parseArgs(uint argc, char *argv[]);

uint parseTaskID(const string &taskIDString);

LINE_TYPES getInputFileType(const string &line);

FRAME parseInputFileLine(const string &line);

ResourceArg parseResourceArg(const string &arg);

ResourcesLine parseResourcesLine(const string &line);

TaskLine parseTaskLine(const string &line);

#endif