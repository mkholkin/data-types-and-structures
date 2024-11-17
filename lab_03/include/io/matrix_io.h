#ifndef MATRIX_IO_H
#define MATRIX_IO_H
#include <stddef.h>

#include "return_codes.h"
#include "types.h"

return_code input_size(const char *prompt, size_t* val);
return_code input_percent(size_t *val);
return_code input_matrix_size(size_t* nrows, size_t* ncols);
return_code input_matrix(matrix_t* matrix);
return_code input_vector(matrix_t* matrix);
return_code user_fill_matrix(matrix_t* matrix);
return_code hand_fill(matrix_t* matrix);
return_code target_fill(matrix_t* matrix);
return_code target_fill_vector(matrix_t* matrix);
return_code random_fill(matrix_t* matrix);
void print_matrix_normal(const matrix_t* matrix);
void print_matrix_csr(const csr_matrix* matrix);

#endif //MATRIX_IO_H
