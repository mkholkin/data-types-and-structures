#include "../../include/utils/array_tools.h"

#include <stdlib.h>
#include <string.h>

static void swap(void *a, void *b, const size_t bytes)
{
    unsigned char *a_cursor = a;
    unsigned char *b_cursor = b;

    for (size_t i = 0; i < bytes; i++)
    {
        *a_cursor = *b_cursor ^ *a_cursor;
        *b_cursor = *a_cursor ^ *b_cursor;
        *a_cursor = *b_cursor ^ *a_cursor;

        a_cursor++;
        b_cursor++;
    }
}

int arr_remove(void *array, const size_t el_size, size_t *array_size, void *target_ptr)
{
    if (array == NULL)
        return -1;
    if (target_ptr == NULL)
        return -1;
    if ((target_ptr - array) % el_size != 0)
        return -1;
    if (target_ptr < array || target_ptr > array + *array_size * el_size)
        return -1;

    for (unsigned char *cursor = target_ptr; cursor < array + *array_size * el_size - el_size; cursor += el_size)
        memcpy(cursor, cursor + el_size, el_size);

    --(*array_size);

    return 0;
}

void shuffle(void *array, const size_t el_size, const size_t array_size)
{
    for (int i = 0; i < array_size; ++i)
    {
        const int swap_idx = rand() % array_size;
        swap(array + i * el_size, array + swap_idx * el_size, el_size);
    }
}