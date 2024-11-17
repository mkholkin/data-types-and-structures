#include "io/ptr_io.h"

#include <stdlib.h>

#include "io/io.h"
#include "io/validators.h"

return_code input_ptr(const char* prompt, uintptr_t* val)
{
    char buff[20 + 1];

    const return_code rc = input_until_valid(prompt, buff, 20 + 1, size_validator);
    if (rc == OK)
        *val = (uintptr_t) strtoull(buff, NULL, 10);

    return rc;
}

return_code input_size(const char* prompt, size_t* val)
{
    char buff[20 + 1];

    const return_code rc = input_until_valid(prompt, buff, 20 + 1, size_validator);
    if (rc == OK)
        *val = strtoull(buff, NULL, 10);

    return rc;
}
