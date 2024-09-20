#ifndef EXTENDED_ARITHMETIC_H
#define EXTENDED_ARITHMETIC_H

#include "types.h"
#include "return_codes.h"

return_code multiply_reversed(const extended_int_t a, const extended_int_t b, extended_int_t *result);
return_code add_reversed(const extended_int_t a, const extended_int_t b, extended_int_t *result);
return_code multiply_float_reversed(const extended_double_t a, const extended_int_t b, extended_double_t *result);
return_code multiply_float(const extended_double_t a, const extended_int_t b, extended_double_t *result);
return_code multiply_float(const extended_double_t a, const extended_int_t b, extended_double_t *result);
return_code read_extended_double(extended_double_t *dst);
return_code read_extended_int(extended_int_t *dst);
void round_reversed(extended_int_t *a, const size_t up_to);

#endif //EXTENDED_ARITHMETIC_H
