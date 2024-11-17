#include "utils/utils.h"

#include <string.h>

int is_in(const void *array, size_t el_size, size_t array_size, const void *target)
{
    for (size_t i = 0; i < array_size; ++i)
        if (memcmp(array + i * el_size, target, el_size) == 0)
            return 1;
    return 0;
}
