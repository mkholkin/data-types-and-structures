//
// Created by Kriptos on 05.09.2024.
//

#ifndef ARRAY_TOOLS_H
#define ARRAY_TOOLS_H

#include <stddef.h>

void swap(void *a, void *b, const size_t bytes);
void reverse(void *array, const size_t n, const size_t el_size);
void *nulify(void *array, const size_t n, const size_t el_size);
void shift_right(void *array, size_t length, size_t element_size);
void shift_right_mult(void *array, size_t length, size_t element_size, size_t times);
void shift_left(void *array, const size_t length, const size_t element_size);

#endif //ARRAY_TOOLS_H
