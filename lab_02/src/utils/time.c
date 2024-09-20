#include "../../include/utils/time.h"

#include <sys/time.h>

unsigned long long nanoseconds_now(void)
{
    struct timespec time;
    unsigned long long nanoseconds = -1;

    if (clock_gettime(CLOCK_MONOTONIC, &time) == 0)
        nanoseconds = time.tv_sec * 1000000000ULL + time.tv_nsec;

    return nanoseconds;
}
