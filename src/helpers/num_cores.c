#include "num_cores.h"

int get_number_of_cores() {
    int n;
    size_t s = sizeof(n);
    if (sysctlbyname("hw.logicalcpu", &n, &s, NULL, 0) == -1) {
        perror("Could not get cores\n");
        exit(1);
    }

    return n;
}