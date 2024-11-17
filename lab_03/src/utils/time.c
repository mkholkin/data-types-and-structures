#include "utils/time.h"

#include <sys/time.h>

nsec_t nanoseconds_now(void)
{
    struct timespec time;
    nsec_t nanoseconds = -1;

    if (clock_gettime(CLOCK_MONOTONIC, &time) == 0)
        nanoseconds = time.tv_sec * 1000000000ULL + time.tv_nsec;

    return nanoseconds;
}
