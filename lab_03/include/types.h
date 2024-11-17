#ifndef TYPES_H
#define TYPES_H
#include <stddef.h>

typedef struct
{
    int **data;
    size_t nrows;
    size_t ncols;
} matrix_t;

typedef struct
{
    int *val;
    size_t *col;
    size_t *row_offset;
    size_t nnz;
    size_t nrows;
    size_t ncols;
} csr_matrix;

typedef struct
{
    int *val;
    size_t *i;
    size_t nnz;
    size_t len;
} csr_vector;

#endif //TYPES_H
