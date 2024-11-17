#include "io/validators.h"

#include <stdlib.h>
#include <string.h>

#include "utils/string_tools.h"

bool size_validator(const char *str)
{
    return is_digits_only(str) && strcmp(str, "0") != 0;
}

bool percent_validator(const char *str)
{
    return is_digits_only(str) && atoi(str) <= 100 && atoi(str) >= 0;
}