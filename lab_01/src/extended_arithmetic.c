#include "../include/extended_arithmetic.h"
#include "../include/array_tools.h"
#include "../include/defines.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int max(const int a, const int b)
{
    return a > b ? a : b;
}

void round_reversed(extended_int_t *a, const size_t up_to)
{
    if (a->len <= up_to)
        return;

    int i = a->len - up_to;
    const int len_dif = i;

    if (a->digits[i - 1] >= 5)
        a->digits[i] += 1;

    while (a->digits[i] >= BASE)
    {
        if (i == a->len - 1)
            a->len += 1;

        const int k = a->digits[i] / BASE;
        a->digits[i + 1] += k;
        a->digits[i] -= k * BASE;

        i++;
    }

    for (i = 0; i < len_dif; i++)
        a->digits[i] = 0;
}

return_code multiply_float_reversed(const extended_double_t a, const extended_int_t b, extended_double_t *result)
{
    return_code rc = multiply_reversed(a.mantissa, b, &result->mantissa);

    if (rc == OK)
        result->ord = a.ord + result->mantissa.len - a.mantissa.len;

    if (rc == OK && result->mantissa.len > MANTISSA_MAX_OUTPUT_DIGITS)
        round_reversed(&result->mantissa, MANTISSA_MAX_OUTPUT_DIGITS);

    // Remove endig zeroes to according to normal form
    reverse(result->mantissa.digits, result->mantissa.len, sizeof(digit_t));
    while (result->mantissa.len > 0 && result->mantissa.digits[result->mantissa.len - 1] == 0)
        result->mantissa.len--;
    reverse(result->mantissa.digits, result->mantissa.len, sizeof(digit_t));

    return rc;
}

return_code multiply_float(extended_double_t a, extended_int_t b, extended_double_t *result)
{
    reverse(a.mantissa.digits, a.mantissa.len, sizeof(digit_t));
    reverse(b.digits, b.len, sizeof(digit_t));

    return_code rc = multiply_float_reversed(a, b, result);

    if (rc == OK)
        reverse(result->mantissa.digits, result->mantissa.len, sizeof(digit_t));

    return rc;
}

return_code multiply_reversed(const extended_int_t a, const extended_int_t b, extended_int_t *result)
{
    return_code rc = OK;

    for (size_t i = 0; rc == OK && i < a.len; i++)
    {
        extended_int_t tmp = {{0}, b.len};

        for (size_t j = 0; j < b.len; j++)
        {
            tmp.digits[j] = a.digits[i] * b.digits[j];
        }

        // TODO: think of how to move it to the top
        // Сдвиг на i десятков
        tmp.len += i;
        if (tmp.len > EXTENDED_INT_BUFFER_SIZE)
            return BUFFER_OVERFLOW_ERROR;

        shift_right_mult(tmp.digits, tmp.len, sizeof(digit_t), i);
        rc = add_reversed(*result, tmp, result);
    }

    if (rc == OK)
        result->negative = a.negative ^ b.negative;

    return rc;
}

return_code add_reversed(extended_int_t a, extended_int_t b, extended_int_t *result)
{
    nulify(result->digits, EXTENDED_INT_BUFFER_SIZE, sizeof(digit_t));
    result->len = max(a.len, b.len);

    for (size_t i = 0; i < result->len; i++)
    {
        if (i < a.len)
            result->digits[i] += a.digits[i];

        if (i < b.len)
            result->digits[i] += b.digits[i];

        if (result->digits[i] >= BASE)
        {
            if (i >= EXTENDED_INT_BUFFER_SIZE)
                return BUFFER_OVERFLOW_ERROR;

            if (i == result->len - 1)
                result->len += 1;

            const int k = result->digits[i] / BASE;
            result->digits[i + 1] += k;
            result->digits[i] -= k * BASE;
        }
    }

    return OK;
}

return_code read_extended_int(extended_int_t *dst)
{
    bool sign_defined = false;
    bool seen_nonzero = false;

    char c, prev_char = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            break;

        if (c == '-' || c == '+')
        {
            if (sign_defined)
                return ERROR_INVALID_INPUT_INT;
            sign_defined = true;
            dst->negative = c == '-';
        }
        else if (isdigit(c))
        {
            if (!sign_defined)
                sign_defined = true;
            if (!seen_nonzero && c != '0')
                seen_nonzero = true;
            if (seen_nonzero)
            {
                if (dst->len == INT_MAX_DIGITS)
                    return ERROR_INVALID_INPUT_INT;

                dst->digits[dst->len] = c - '0';
                dst->len += 1;
            }
        }
        else
            return ERROR_INVALID_INPUT_INT;

        prev_char = c;
    }

    if (!sign_defined)
        return ERROR_INVALID_INPUT_INT;

    if (prev_char == '-' || prev_char == '+')
        return ERROR_INVALID_INPUT_INT;

    return OK;
}

return_code read_extended_double(extended_double_t *dst)
{
    bool sign_defined = false;
    bool seen_nonzero = false;
    bool seen_period = false;
    size_t zeroes = 0;
    size_t numbers_read = 0;

    char c, prev_c = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            break;
        // Текущий символ - знак +/-
        if (c == '-' || c == '+')
        {
            if (sign_defined)
                return ERROR_INVALID_INPUT_DOUBLE;
            sign_defined = true;
            dst->mantissa.negative = c == '-';
        }
        // Текущий символ - цифра
        else if (isdigit(c))
        {
            if (numbers_read == MANTISSA_MAX_INPUT_DIGITS)
                return MANTISSA_OVERFLOW_ERROR;
            if (!sign_defined)
                sign_defined = true;
            if (!seen_nonzero && c != '0')
                seen_nonzero = true;
            if (zeroes != 0 && c != '0')
            {
                dst->mantissa.len += zeroes;
                zeroes = 0;
            }
            // Уменьшить порядок на 1, если это число - незначащий ноль после точки
            if (!seen_nonzero && seen_period)
            {
                dst->ord -= 1;
                numbers_read += 1;
            }
            // Увеличить порядок на 1, если еще не было точки
            if (seen_nonzero && !seen_period)
                dst->ord += 1;
            if (seen_nonzero && seen_period && c == '0')
            {
                zeroes += 1;
            }
            if (seen_nonzero && zeroes == 0)
            {
                if (dst->mantissa.len == MANTISSA_MAX_INPUT_DIGITS)
                    return ERROR_INVALID_INPUT_DOUBLE;
                dst->mantissa.digits[dst->mantissa.len] = c - '0';
                dst->mantissa.len += 1;
                numbers_read += 1;
            }
        }
        // Текущий символ - точка
        else if (c == '.')
        {
            if (seen_period)
                return ERROR_INVALID_INPUT_DOUBLE;
            if (!sign_defined)
                sign_defined = true;
            seen_period = true;
        }
        // Текущий символ - e/E
        else if (c == 'e' || c == 'E')
        {
            if (!isdigit(prev_c))
                return ERROR_INVALID_INPUT_DOUBLE;

            int ord;
            char end = 0;
            if (scanf("%d%c", &ord, &end) < 1 || !(end == 0 || end == '\n'))
                return ERROR_INVALID_INPUT_DOUBLE;
            if (abs(ord) > ABS_ORD_MAX)
                return ORD_OVERFLOW_ERROR;
            dst->ord += ord;
            break;
        }
        else
            return ERROR_INVALID_INPUT_DOUBLE;

        prev_c = c;
    }

    if (!sign_defined)
        return ERROR_INVALID_INPUT_DOUBLE;

    if (prev_c == '-' || prev_c == '+')
        return ERROR_INVALID_INPUT_DOUBLE;

    return OK;
}
