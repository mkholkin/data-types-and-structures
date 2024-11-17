#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "types.h"

void multiply(const matrix_t* a, const matrix_t* b, matrix_t* res);
void spare_mv(const csr_matrix* a, const csr_vector* b, csr_vector* res);
void matrix_random_fill(matrix_t* matrix, size_t n);
void matrix_random_fill_percent(matrix_t* matrix, const size_t percent);
int** matrix_realloc(void* ptr, const size_t nrows, const size_t ncols);
csr_matrix* import_csr_matrix(const matrix_t* m, csr_matrix* sm);
csr_vector* import_csr_vector(const matrix_t* v, csr_vector* sv);
void print_spare_matrix_as_normal(const csr_matrix* m);
void print_spare_vector(const csr_vector* sv);
void print_spare_vector_as_normal(const csr_vector* sv);

#endif //MATRIX_OPERATIONS_H
