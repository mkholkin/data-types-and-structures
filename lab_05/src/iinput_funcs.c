#include "iinput_funcs.h"

#include <stdlib.h>

#include "io.h"
#include "validators.h"

return_code input_time(const char *prompt, time_t_ *val)
{
    char buff[20 + 1] = { 0 };

    const return_code rc = input_until_valid(prompt, buff, 20 + 1, validate_time);
    if (rc == OK)
        *val = strtod(buff, NULL);

    return rc;
}
