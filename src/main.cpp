//Copyright 2018 Ryan Furrer
#include "parsers.h"
#include "taskManager.h"

/**
 *  Main entry point for a4tasks.
 *
 * @param argc
 * @param argv
 * @return {@code int} Exit Status
 */
int main(int argc, char *argv[]) {
    int status = validateArgs(argc, argv);

    if (!status) {
        return start(parseArgs(argc, argv));
    }

    return status;
}