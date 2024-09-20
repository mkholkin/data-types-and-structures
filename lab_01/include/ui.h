#ifndef UI_H
#define UI_H

#include "return_codes.h"
#include "extended_arithmetic.h"


void render_ruler(const char *prompt);
void render_prompt(const char *prompt);
return_code input_extended_int(extended_int_t *a);
return_code input_extended_double(extended_double_t *a);
void print_error(const return_code rc);

#endif //UI_H
