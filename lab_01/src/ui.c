#include "../include/ui.h"
#include "../include/defines.h"
#include "../include/return_codes.h"
#include "../include/extended_arithmetic.h"

#include <stdio.h>
#include <string.h>

static void render_ruler_heading(const char *prompt)
{
    const size_t step = strlen(RULER_UNIT);
    const size_t n_units = RULER_WIDTH / step;

    fprintf(stdout, "%*s ", (int) strlen(prompt), " ");

    for (int i = 0; i < n_units; i++)
    {
        const int spaces = i * step < 10 ? step - 1 : step - 2;
        fprintf(stdout, "%*s%zu", spaces, " ", (i + 1) * step);
    }
}

static void render_ruler_body(const char *prompt)
{
    const size_t n_units = RULER_WIDTH / strlen(RULER_UNIT);

    fprintf(stdout, "%*s>", (int) strlen(prompt), " ");
    for (int i = 0; i < n_units; i++)
    {
        fprintf(stdout, "%s", RULER_UNIT);
    }
}

void render_ruler(const char *prompt)
{
    render_ruler_heading(prompt);
    fprintf(stdout, "\n");
    render_ruler_body(prompt);
    fprintf(stdout, "\n");
}

void render_prompt(const char *prompt)
{
    render_ruler(prompt);
    fprintf(stdout, prompt);
}

return_code input_extended_int(extended_int_t *a)
{
    render_prompt("Enter integer: ");
    return read_extended_int(a);
}

return_code input_extended_double(extended_double_t *a)
{
    render_prompt("Enter decimal: ");
    return read_extended_double(a);
}

void print_error(const return_code rc)
{
    switch (rc)
    {
        case BUFFER_OVERFLOW_ERROR:
            printf("Error: Buffer has been overflowed during calculations\n");
            break;
        case ORD_OVERFLOW_ERROR:
            printf("Error: Order overflow\n");
            break;
        case ERROR_INVALID_INPUT_INT:
            printf("Error: Invalid integer input\n"
                "Correct format: [+-]\\d+");
            break;
        case ERROR_INVALID_INPUT_DOUBLE:
            printf("Error: invalid double input\n"
                "Correct format: [+-]\\d+?.\\d+([eE][+-]\\d+)?");
        case MANTISSA_OVERFLOW_ERROR:
            printf("Error: limit of meaning numbers is %d", MANTISSA_MAX_INPUT_DIGITS);
        default:
            break;
    }
}
