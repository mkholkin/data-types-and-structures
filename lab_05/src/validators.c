#include "validators.h"

#include <stdlib.h>

#include "types.h"

bool validate_time(const char *str)
{
    const char *pend;
    const time_t_ val = strtod(str, &pend);
    return !*pend && val >= 0;
}
