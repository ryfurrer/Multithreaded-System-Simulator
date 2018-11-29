#include "parsers.h"

int validateArgs(int argc, char *argv[]) {
    if (argc != 4) {
        return EINVAL;
    }

    return 0;
}
