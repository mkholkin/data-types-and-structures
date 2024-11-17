#include "commands.h"

#include <stdio.h>
#include <stdlib.h>

#include "matrix_operations.h"
#include "return_codes.h"
#include "io/matrix_io.h"
#include "utils/time.h"

return_code process_set_matrix(matrix_t* m, csr_matrix* sm)
{
    return_code rc = input_matrix(m);

    if (rc == OK)
        if (!import_csr_matrix(m, sm))
            rc = ERR_CANT_ALLOCATE_MEMORY;

    return rc;
}

return_code process_set_vector(matrix_t* v, csr_vector* sv)
{
    return_code rc = input_vector(v);

    if (rc == OK)
        if (!import_csr_vector(v, sv))
            rc = ERR_CANT_ALLOCATE_MEMORY;

    return rc;
}

return_code process_set_multipliers(matrix_t* m, csr_matrix* sm, matrix_t* v, csr_vector* sv)
{
    printf("[+] Setting matrix\n");
    return_code rc = input_matrix(m);

    if (rc == OK)
        if (!import_csr_matrix(m, sm))
            rc = ERR_CANT_ALLOCATE_MEMORY;

    if (rc == OK)
    {
        printf("\n[+] Setting vector\n");
        v->nrows = m->ncols;
        v->ncols = 1;
        v->data = matrix_realloc(v->data, v->nrows, v->ncols);
        if (v->data == NULL)
            rc = ERR_CANT_ALLOCATE_MEMORY;
        else
            printf("[+] Vector length was automatically set to [%zu]\n", m->ncols);
    }

    if (rc == OK)
        rc = user_fill_matrix(v);

    if (rc == OK)
        if (!import_csr_vector(v, sv))
            rc = ERR_CANT_ALLOCATE_MEMORY;

    return rc;
}

void process_print_matrix(const matrix_t* m)
{
    if (!m->data)
    {
        printf("MATRIX IS UNDEFINED\n");
        return;
    }

    print_matrix_normal(m);
}

void process_print_spare_matrix(const csr_matrix* sm)
{
    if (sm->val)
        print_matrix_csr(sm);
    else
        printf("MATRIX IS UNDEFINED\n");
}

void process_print_spare_vector(const csr_vector* sv)
{
    if (sv->val)
        print_spare_vector(sv);
    else
        printf("VECTOR IS UNDEFINED\n");
}

void process_print_vector(const matrix_t* m)
{
    if (m->data)
    {
        print_matrix_normal(m);
    }
    else
        printf("VECTOR IS UNDEFINED\n");
}

void process_multiply(const matrix_t* m, const matrix_t* v)
{
    if (!v->data || !m->data)
    {
        printf("[!] Error: MATRIX OR VECTOR IS UNDEFINED\n");
        return;
    }

    matrix_t result = {0};
    multiply(m, v, &result);

    if (result.nrows <= 30 && result.ncols <= 30)
        process_print_matrix(&result);
    else
    {
        csr_vector sv = {0};
        import_csr_vector(&result, &sv);
        print_spare_vector(&sv);
        free(sv.val);
        free(sv.i);
    }
    free(result.data);
}

void process_multiply_spare_mv(const csr_matrix* sm, const csr_vector* sv)
{
    if (!sv->val || !sm->val)
    {
        printf("[!] Error: MATRIX OR VECTOR IS UNDEFINED\n");
        return;
    }

    csr_vector result = {0};
    spare_mv(sm, sv, &result);

    if (result.len <= 30)
        print_spare_vector_as_normal(&result);
    else
        print_spare_vector(&result);
}

void process_show_stat(const matrix_t* m, const csr_matrix* sm, matrix_t* v, const csr_vector* sv)
{
    if (!sv->val || !sm->val)
    {
        printf("[!] Error: MATRIX OR VECTOR IS UNDEFINED\n");
        return;
    }

    nsec_t normal = 0;
    nsec_t spare = 0;

    matrix_t dummy = {0};
    csr_vector s_dummy = {0};

    for (int i = 0; i < 10; i++)
    {
        nsec_t beg = nanoseconds_now();
        multiply(m, v, &dummy);
        nsec_t end = nanoseconds_now();
        normal += end - beg;

        beg = nanoseconds_now();
        spare_mv(sm, sv, &s_dummy);
        end = nanoseconds_now();
        spare += end - beg;
    }

    normal /= 10;
    const size_t normal_memory = sizeof(*m) + sizeof(m->data[0][0]) * m->ncols * m->nrows + sizeof(*v) + sizeof(v->data[0][0]) * v->nrows;
    spare /= 10;
    const size_t spare_memory = sizeof(*sm) + (sizeof(sm->val[0]) + sizeof(sm->col[0])) * sm->nnz + sizeof(sm->row_offset[0]) * (sm->nrows + 1) +
        sizeof(*sv) + (sizeof(sv->i[0]) + sizeof(sv->val[0])) * sv->nnz;

    printf(
        "┌────────────────────────────┬──────────────────────┬────────────────────┐\n"
        "│                            │  Time (nanoseconds)  │   Memory (bytes)   │\n"
        "├────────────────────────────┼──────────────────────┼────────────────────┤\n"
        "│ Common method              │ %19llu  │ %18zu │\n"
        "├────────────────────────────┼──────────────────────┼────────────────────┤\n"
        "│ Chang & Gustavson          │ %10llu (%+03.2lf%%) │ %8zu (%+03.2lf%%) │\n"
        "└────────────────────────────┴──────────────────────┴────────────────────┘\n",
        normal, normal_memory,
        spare, 100 * ((double)spare - (double)normal) / normal, spare_memory,
        100 * ((double) spare_memory - (double) normal_memory) / normal_memory
    );

    free(dummy.data);
    free(s_dummy.val);
}
