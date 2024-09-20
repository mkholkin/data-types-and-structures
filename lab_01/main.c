#include <stdio.h>

#include "include/ui.h"
#include "include/extended_arithmetic.h"

void print_extended_double(const extended_double_t *a)
{
    if (a->mantissa.len == 0)
    {
        printf("0\n");
        return;
    }

    if (a->mantissa.negative)
        printf("-");

    printf("0.");

    for (size_t i = 0; i < a->mantissa.len; i++)
        printf("%u", a->mantissa.digits[i]);
    printf("e%d", a->ord);

    printf("\n");
}

void print_result(extended_double_t *a)
{
    if (a->ord > ABS_ORD_MAX)
    {
        if (a->mantissa.negative)
            printf("-");
        printf("INF (Result is too big that can't be calculated)\n");
    }
    else if (a->ord < -ABS_ORD_MAX)
        printf("ZERO (Result is too low that can't be calculated)\n");
    else
        print_extended_double(a);
}

int main(void)
{
    setbuf(stdout, NULL);

    extended_double_t a = {0};
    extended_int_t b = {0};
    extended_double_t c = {0};

    return_code rc = input_extended_int(&b);

    if (rc == OK)
        rc = input_extended_double(&a);

    if (rc == OK)
        rc = multiply_float(a, b, &c);

    if (rc == OK)
    {
        render_ruler("Result: ");
        printf("Result: ");
        print_result(&c);
    }

    if (rc != OK)
        print_error(rc);

    return rc;
}

// 90009 10001
// Пометить машинный ноль и бесконечность