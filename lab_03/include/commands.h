#ifndef COMMANDS_H
#define COMMANDS_H

#include "return_codes.h"
#include "types.h"

return_code process_set_matrix(matrix_t *m, csr_matrix *sm);
return_code process_set_vector(matrix_t *v, csr_vector *sv);
return_code process_set_multipliers(matrix_t *m, csr_matrix *sm, matrix_t *v, csr_vector *sv);
void process_print_matrix(const matrix_t *m);
void process_print_spare_matrix(const csr_matrix *sm);
void process_print_vector(const matrix_t *m);
void process_print_spare_vector(const csr_vector *sv);
void process_multiply(const matrix_t* m, const matrix_t* v);
void process_multiply_spare_mv(const csr_matrix *sm, const csr_vector *sv);
void process_multiply_spare_vm(const csr_vector *sv, const csr_matrix *sm);
void process_show_stat(const matrix_t *m, const csr_matrix *sm, matrix_t *v, const csr_vector *sv);

#endif //COMMANDS_H
