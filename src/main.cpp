#include <stdio.h> /* printf */
#include <cstring> /* string compare */
#include <signal.h>
#include <stdlib.h>     /* atoi */
#include "parsers.h"

using std::string;
using std::chrono::milliseconds;

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
        string inputFile = argv[1];
        milliseconds monitorTime = static_cast<milliseconds>(atoi(argv[2]));
        uint nIter = static_cast<uint>(atoi(argv[3]));
        // TODO: enter thread
    }
    return status;
}