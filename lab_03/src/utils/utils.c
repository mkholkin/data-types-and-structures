#include "../../include/utils/utils.h"

#include <stdlib.h>
#include <string.h>

void* realloc_zero(void* ptr, size_t size)
{
    ptr = realloc(ptr, size);
    if (ptr)
        memset(ptr, 0, size);
    return ptr;
}
