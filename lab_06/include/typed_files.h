#ifndef TYPED_FILES_H
#define TYPED_FILES_H

#include <stdio.h>

typedef int item_t;

size_t tf_len_items(FILE *stream);

size_t tf_read(FILE *stream, item_t *item);
size_t tf_write(FILE *stream, item_t item);

size_t tf_get_pos(FILE *stream);
int tf_set_pos(FILE *stream, size_t pos);

int get_number_by_pos(int *number, size_t pos, FILE *stream);
int put_number_by_pos(int number, size_t pos, FILE *stream);
int tf_append(item_t item, FILE *stream);

void tf_sort(FILE *stream, int (*compare)(const item_t *a, const item_t *b));


#endif //TYPED_FILES_H
