#include "parsers.h"

int validateArgs(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Invalid number of arguments.\n");
        return EINVAL;
    }

    return 0;
}

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

LINE_TYPES getInputFileType(const string &line);

FRAME parseInputFileLine(const string &line);

ResourceArg parseResourceArg(const string &arg);

ResourcesLine parseResourcesLine(const string &line);

TaskLine parseTaskLine(const string &line);
