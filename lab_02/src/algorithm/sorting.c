#include "../../include/algorithm/sorting.h"

#include <stdlib.h>


// ReSharper disable once CppDFAConstantParameter
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

// ReSharper disable once CppDFAConstantParameter
static void selectsort(void *base, const size_t nmemb, const size_t size, int (*cmp)(const void *, const void *))
{
    for (size_t i = 0; i < nmemb; i++)
    {
        size_t min_i = i;
        for (size_t j = i + 1; j < nmemb; j++)
            if (cmp((char *) base + j * size, (char *)base + min_i * size) < 0)
                min_i = j;

        if (min_i != i)
            swap((char *) base + min_i * size, (char *) base + i * size, size);
    }
}

static int cmp_cars_by_price(const car_t *a, const car_t *b)
{
    return a->price - b->price;
}

static int cmp_key_price(const key_price *a, const key_price *b)
{
    return a->price - b->price;
}

void selectsort_cars_by_price(car_t *cars, const size_t n)
{
    selectsort(cars, n, sizeof(car_t), cmp_cars_by_price);
}

void qsort_cars_by_price(car_t *cars, const size_t n)
{
    qsort(cars, n, sizeof(car_t), cmp_cars_by_price);
}

void key_tbl_selectsort_cars_by_price(key_price *items, const size_t n)
{
    qsort(items, n, sizeof(key_price), cmp_key_price);
}

void key_tbl_qsort_cars_by_price(key_price *items, const size_t n)
{
    selectsort(items, n, sizeof(key_price), cmp_key_price);
}
