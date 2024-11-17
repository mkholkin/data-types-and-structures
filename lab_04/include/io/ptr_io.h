#ifndef PTR_IO_H
#define PTR_IO_H
#include <stddef.h>
#include <stdint.h>

#include "return_codes.h"

return_code input_ptr(const char *prompt, uintptr_t *val);
return_code input_size(const char *prompt, size_t *val);

#endif //PTR_IO_H
