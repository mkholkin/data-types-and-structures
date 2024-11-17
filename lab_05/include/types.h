#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>

typedef double time_t_;
typedef size_t ticks_t;

typedef struct
{
    size_t cycles_left;
} request_t;

typedef request_t item_t;
#define ITEM_FMT "%lf"

#endif //TYPES_H
