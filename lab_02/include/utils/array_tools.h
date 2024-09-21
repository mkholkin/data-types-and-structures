#ifndef ARRAY_TOOLS_H
#define ARRAY_TOOLS_H
#include <stddef.h>

int arr_remove(void *array, const size_t el_size, size_t *array_size, void *target_ptr);
void shuffle(void *array, const size_t el_size, const size_t array_size);

#endif //ARRAY_TOOLS_H
