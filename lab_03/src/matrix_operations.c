#include "matrix_operations.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io/matrix_io.h"
#include "utils/utils.h"

void multiply(const matrix_t* a, const matrix_t* b, matrix_t* res)
{
    res->nrows = a->nrows;
    res->ncols = b->ncols;
    res->data = matrix_realloc(res->data, res->nrows, res->ncols);

    for (int i = 0; i < a->nrows; i++)
        for (int j = 0; j < b->ncols; j++)
        {
            for (int k = 0; k < b->nrows; k++)
                res->data[i][j] += a->data[i][k] * b->data[k][j];
        }
}

int** matrix_realloc(void* ptr, const size_t nrows, const size_t ncols)
{
    int** res = realloc_zero(ptr, sizeof(int) * nrows * ncols + sizeof(int*) * nrows);
    if (!res)
        return NULL;

    int* data = (int*)(res + nrows);

    for (int i = 0; i < nrows; i++)
        res[i] = data + i * ncols;

    return res;
}

csr_matrix* import_csr_matrix(const matrix_t* m, csr_matrix* sm)
{
    int n = 0;
    int last_line = 0;

    for (int i = 0; i < m->nrows; i++)
        for (int j = 0; j < m->ncols; j++)
            if (m->data[i][j] != 0)
            {
                last_line = i;
                n++;
            }

    sm->nnz = n;
    sm->val = realloc_zero(sm->val, sizeof(sm->val[0]) * n);
    if (!sm->val)
        return NULL;

    sm->col = realloc_zero(sm->col, sizeof(sm->col[0]) * n);
    if (!sm->col)
        return NULL;

    sm->row_offset = realloc_zero(sm->row_offset, sizeof(sm->row_offset[0]) * (m->nrows + 1));
    if (!sm->row_offset)
        return NULL;

    int k = 0;
    for (int i = 0; i < m->nrows; i++)
    {
        sm->row_offset[i] = k;
        bool seen_nonzero = false;
        for (int j = 0; j < m->ncols; j++)
            if (m->data[i][j] != 0)
            {
                sm->val[k] = m->data[i][j];
                sm->col[k] = j;
                if (!seen_nonzero)
                {
                    sm->row_offset[i] = k;
                    seen_nonzero = true;
                }
                k++;
            }
        sm->row_offset[m->nrows] = sm->row_offset[m->nrows - 1];
    }

    for (int i = last_line + 1; i < m->nrows + 1; i++)
        sm->row_offset[i] = n;

    sm->ncols = m->ncols;
    sm->nrows = m->nrows;

    return sm;
}

csr_vector* import_csr_vector(const matrix_t* v, csr_vector* sv)
{
    int n = 0;

    for (int i = 0; i < v->nrows; i++)
        if (v->data[i][0] != 0)
            n++;

    sv->nnz = n;
    sv->val = realloc_zero(sv->val, sizeof(sv->val[0]) * n);
    if (!sv->val)
        return NULL;

    sv->i = realloc_zero(sv->i, sizeof(sv->i[0]) * n);
    if (!sv->i)
        return NULL;

    int k = 0;
    for (int i = 0; i < v->nrows; i++)
        if (v->data[i][0] != 0)
        {
            sv->val[k] = v->data[i][0];
            sv->i[k] = i;
            k++;
        }

    sv->len = v->nrows;
    return sv;
}

void print_matrix(const matrix_t* m)
{
    if (m->ncols <= 30 && m->nrows <= 30)
    {
        print_matrix_normal(m);
    }
    else
    {
        csr_matrix sm;
        import_csr_matrix(m, &sm);
        print_matrix_csr(&sm);
        free(sm.val);
    }
}

void print_spare_matrix_as_normal(const csr_matrix* m)
{
    // Проходим по каждой строке матрицы
    for (int i = 0; i < m->nrows; i++)
    {
        int value_index = m->row_offset[i]; // Начальный индекс для строки i
        const int next_value_index = m->row_offset[i + 1]; // Конечный индекс для строки i

        for (int j = 0; j < m->ncols; j++)
        {
            if (value_index < next_value_index && m->col[value_index] == j)
            {
                // Если текущий столбец соответствует ненулевому элементу
                printf("%d ", m->val[value_index]);
                value_index++; // Переходим к следующему ненулевому элементу в строке
            }
            else
            {
                // Если элемент равен нулю
                printf("0 ");
            }
        }
        printf("\n"); // Переход на следующую строку
    }
}

void print_spare_vector_as_normal(const csr_vector* sv)
{
    int k = 0;
    for (int i = 0; i < sv->len; i++)
    {
        if (sv->i[k] == i)
            printf("%d\n", sv->val[k++]);
        else
            printf("0\n");
    }
}

void print_vector(const matrix_t* v)
{
    if (v->nrows <= 30)
    {
        for (int i = 0; i < v->ncols; i++)
            printf("%d\n", v->data[i][0]);
    }
    else
    {
        csr_vector sv;
        import_csr_vector(v, &sv);
        print_spare_vector(&sv);
        free(sv.val);
    }
}

void print_spare_vector(const csr_vector* sv)
{
    printf("VAL     ");
    for (int i = 0; i < sv->nnz; i++)
        printf("%d  ", sv->val[i]);
    printf("\n");

    printf("I       ");
    for (int i = 0; i < sv->nnz; i++)
        printf("%zu  ", sv->i[i]);
    printf("\n");
}


void spare_mv(const csr_matrix* a, const csr_vector* b, csr_vector* res)
{
    // Выделение памяти под результат заранее
    res->val = realloc_zero(res->val, sizeof(res->val[0]) * a->nrows);
    res->i = realloc_zero(res->i, sizeof(size_t) * a->nrows);
    res->len = a->nrows;
    int k = 0;

    // Создание массива для быстрого поиска индексов вектора b
    int* b_map = calloc(a->ncols, sizeof(int));
    for (int idx = 0; idx < b->nnz; idx++)
    {
        b_map[b->i[idx]] = b->val[idx];
    }

    // Обход по строкам матрицы
    for (size_t row = 0; row < a->nrows; row++)
    {
        int row_sum = 0;

        // Обход по ненулевым элементам строки
        for (size_t i = a->row_offset[row]; i < a->row_offset[row + 1]; i++)
        {
            const size_t col = a->col[i];
            const int a_val = a->val[i];

            // Проверка, существует ли соответствующий элемент во входном векторе
            if (b_map[col] != 0)
            {
                row_sum += a_val * b_map[col];
            }
        }

        // Добавление ненулевого результата в итоговый вектор
        if (row_sum != 0)
        {
            res->val[k] = row_sum;
            res->i[k] = row;
            k++;
        }
    }

    // Освобождаем временные массивы и обновляем размеры результата
    free(b_map);
    res->nnz = k;
    res->val = realloc(res->val, sizeof(int) * k);
    res->i = realloc(res->i, sizeof(size_t) * k);
}

void matrix_random_fill(matrix_t* matrix, size_t n)
{
    srand(time(NULL));
    while (n)
    {
        const int i = rand() % matrix->nrows;
        const int j = rand() % matrix->ncols;

        if (matrix->data[i][j] == 0)
        {
            matrix->data[i][j] = rand() % 100 + 1;
            n--;
        }
    }
}


void matrix_random_fill_percent(matrix_t* matrix, const size_t percent)
{
    const size_t n = ceil((double) matrix->nrows * (double) matrix->ncols / 100 * (double) percent);
    matrix_random_fill(matrix, n);
}
