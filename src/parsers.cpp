#include "parsers.h"
#include "util.h"

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

LINE_TYPES getInputFileType(const string &line);

FRAME parseInputFileLine(const string &line);

ResourceArg parseResourceArg(const string &arg);

ResourcesLine parseResourcesLine(const string &line);

TaskLine parseTaskLine(const string &line);

void readInputFile(const string &inputFile) {

}
