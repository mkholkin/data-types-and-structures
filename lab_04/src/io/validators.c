#include "io/validators.h"

#include <stdlib.h>

bool size_validator(const char *str)
{
    const char *err;
    return strtoul(str, &err, 10) > 0 && !*err;
}
