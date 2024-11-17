#include "../include/typed_files.h"

#include <stdio.h>

size_t tf_len_items(FILE *stream)
{
    fseek(stream, 0, SEEK_END);
    size_t len_items = ftell(stream) / sizeof(item_t);
    rewind(stream);
    return len_items;
}

size_t tf_read(FILE *stream, item_t *item)
{
    return fread(item, sizeof(item_t), 1, stream);
}

size_t tf_write(FILE *stream, item_t item)
{
    return fwrite(&item, sizeof(item_t), 1, stream);
}

size_t tf_get_pos(FILE *stream)
{
    return ftell(stream) / sizeof(item_t);
}

int tf_set_pos(FILE *stream, size_t pos)
{
    return fseek(stream, pos * sizeof(item_t), SEEK_SET);
}

int get_number_by_pos(int *number, size_t pos, FILE *stream)
{
    // returns 0 is everything is OK else - nonzero
    int rc = tf_set_pos(stream, pos);

    if (rc == 0)
        rc = !tf_read(stream, number);

    return rc;
}

int put_number_by_pos(int number, size_t pos, FILE *stream)
{
    // returns 0 is everything is OK else - nonzero
    int rc = tf_set_pos(stream, pos);

    if (rc == 0)
        rc = !tf_write(stream, number);

    return rc;
}

void tf_sort(FILE *stream, int (*compare)(const item_t *a, const item_t *b))
{
    int n = tf_len_items(stream);
    int swaped;
    item_t a, b;

    for (int i = 0; i < n; ++i)
    {
        swaped = 0;
        for (int j = 0; j < n - i - 1; ++j)
        {
            get_number_by_pos(&a, j, stream);
            get_number_by_pos(&b, j + 1, stream);
            if (compare(&a, &b) > 0)
            {
                put_number_by_pos(a, j + 1, stream);
                put_number_by_pos(b, j, stream);
                swaped = 1;
            }
        }

        if (!swaped)
            break;
    }
}
