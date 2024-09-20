#include "../include/array_tools.h"

#include <string.h>

void swap(void *a, void *b, const size_t bytes)
{
    for (size_t i = 0; i < bytes; i++)
    {
        *(unsigned char *) a = *(unsigned char *) b ^ *(unsigned char *) a;
        *(unsigned char *) b = *(unsigned char *) a ^ *(unsigned char *) b;
        *(unsigned char *) a = *(unsigned char *) b ^ *(unsigned char *) a;

        a++;
        b++;
    }
}

void *nulify(void *array, const size_t n, const size_t el_size)
{
    return memset(array, 0, n * el_size);
}

void reverse(void *array, const size_t n, const size_t el_size)
{
    for (size_t i = 0; i < n / 2; i++)
        swap(array + i * el_size, array + (n - i - 1) * el_size, el_size);
}

void shift_right(void *array, const size_t length, const size_t element_size)
{
    if (length == 1)
        return;

    unsigned char *end = array + (length - 1) * element_size;

    // swap every element from second to last
    for (int i = length; i > 0; i--)
    {
        swap(end, end - element_size, element_size);
        end -= element_size;
    }

    // null first element
    memset(array, 0, element_size);
}

void shift_right_mult(void *array, const size_t length, const size_t element_size, const size_t times)
{
    for (size_t i = 0; i < times; i++)
        shift_right(array, length, element_size);
}

void shift_left(void *array, const size_t length, const size_t element_size)
{
    if (length == 1)
        return;

    unsigned char *start = array;

    // swap every element from first to pre-last
    for (int i = 0; i < length - 1; i++)
    {
        swap(start, start + element_size, element_size);
        start += element_size;
    }

    // null last element
    memset(start, 0, element_size);
}
