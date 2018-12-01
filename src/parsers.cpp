#include "parsers.h"

uint validateArgs(uint argc, char *argv[]) {
    if (argc != 4) {
        return EINVAL;
    }

    return 0;
}

CLI_ARGS parseArgs(uint argc, char *argv[]) {
    CLI_ARGS args;
    args.inputFile = argv[1];
    args.monitorTime = (atoi(argv[2]));
    args.iterations = (atoi(argv[3]));
    return args;
}

uint parseTaskID(const string &taskIDString) {
    return 0;
}

LINE_TYPES getInputFileType(const string &line);

FRAME parseInputFileLine(const string &line);

ResourceArg parseResourceArg(const string &arg);

ResourcesLine parseResourcesLine(const string &line);

TaskLine parseTaskLine(const string &line);
