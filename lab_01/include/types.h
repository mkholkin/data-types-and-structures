#ifndef TYPES_H
#define TYPES_H

#include "defines.h"

#include <stdbool.h>
#include <stddef.h>

typedef unsigned char digit_t;

typedef struct
{
    digit_t digits[EXTENDED_INT_BUFFER_SIZE];
    size_t len;
    bool negative;
} extended_int_t;

typedef struct
{
    extended_int_t mantissa;
    int ord;
} extended_double_t;

#endif //TYPES_H
