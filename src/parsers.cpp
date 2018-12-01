#include "parsers.h"
#include "util.h"

int validateArgs(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Invalid number of arguments.\n");
        return EINVAL;
    }

    int monitorTime = atoi(argv[2]);
    int iterations = atoi(argv[3]);

    if (!(monitorTime >= 0)) {
        printf("monitorTime invalid\n");
        return EINVAL;
    } else if (!(monitorTime < 99999999)) {
        printf("monitorTime invalid\n");
        return EOVERFLOW;
    }

    if (!(iterations >= 0)) {
        printf("NITER invalid\n");
        return EINVAL;
    } else if (!(iterations < 99999999)) {
        printf("NITER invalid\n");
        return EOVERFLOW;
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

void readInputFile(const string &inputFile) {

}
