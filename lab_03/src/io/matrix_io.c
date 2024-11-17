#include "io/matrix_io.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix_operations.h"
#include "io/io.h"
#include "io/validators.h"

return_code input_size(const char* prompt, size_t* val)
{
    char buff[20 + 1];

    const return_code rc = input_until_valid(prompt, buff, 20 + 1, size_validator);
    if (rc == OK)
        *val = strtoull(buff, NULL, 10);

    return rc;
}

return_code input_percent(size_t* val)
{
    char buff[3 + 1];

    return_code rc = input_until_valid("Enter filling percentage: ", buff, 3 + 1, percent_validator);
    if (rc == OK)
        *val = strtoull(buff, NULL, 10);;

    return rc;
}

return_code input_matrix_size(size_t* nrows, size_t* ncols)
{
    return_code rc = input_size("Enter number of rows: ", nrows);
    if (rc == OK)
        rc = input_size("Enter number of columns: ", ncols);

    return rc;
}

return_code input_matrix(matrix_t* matrix)
{
    char* user_choice = NULL;
    return_code rc = input_matrix_size(&matrix->nrows, &matrix->ncols);

    if (rc == OK)
    {
        matrix->data = matrix_realloc(NULL, matrix->nrows, matrix->ncols);
        if (matrix->data == NULL)
            rc = ERR_CANT_ALLOCATE_MEMORY;
    }

    if (rc == OK)
    {
        printf(
            "How to fill matrix?\n"
            "   [1] Hand mode\n"
            "   [2] Target\n"
            "   [3] Random\n"
            "\n"
            "   [0] Exit\n");

        rc = input_user_choice(&user_choice, "0", 3, "1", "2", "3");
    }

    if (rc == OK)
        switch (atoi(user_choice))
        {
        case 1:
            rc = hand_fill(matrix);
            break;
        case 2:
            rc = target_fill(matrix);
            break;
        case 3:
            rc = random_fill(matrix);
            break;
        default:
            assert(0);
        }

    return rc;
}

return_code user_fill_matrix(matrix_t* matrix)
{
    char* user_choice = NULL;
    return_code rc = OK;

    printf(
        "How to fill vector?\n"
        "   [1] Hand mode\n"
        "   [2] Target\n"
        "   [3] Random\n"
        "\n"
        "   [0] Exit\n");

    do
    {
        rc = input_user_choice(&user_choice, "0", 3, "1", "2", "3");
    }
    while ((rc == OK || should_retry(rc)) && user_choice == NULL);

    if (rc == OK)
        switch (atoi(user_choice))
        {
        case 1:
            rc = hand_fill(matrix);
            break;
        case 2:
            rc = target_fill_vector(matrix);
            break;
        case 3:
            rc = random_fill(matrix);
            break;
        default:
            assert(0);
        }

    return rc;
}

return_code input_vector(matrix_t* matrix)
{
    matrix->ncols = 1;

    return_code rc = input_size("Enter number of rows: ", &matrix->nrows);

    if (rc == OK)
    {
        matrix->data = matrix_realloc(NULL, matrix->nrows, matrix->ncols);
        if (matrix->data == NULL)
            rc = ERR_CANT_ALLOCATE_MEMORY;
    }

    rc = user_fill_matrix(matrix);

    return rc;
}

return_code hand_fill(matrix_t* matrix)
{
    return_code rc = OK;
    printf("Enter elements:\n");
    for (int i = 0; i < matrix->nrows; i++)
        for (int j = 0; j < matrix->ncols; j++)
            if (scanf("%d", &matrix->data[i][j]) != 1)
                rc = ERR_IO;

    return rc;
}

return_code target_fill(matrix_t* matrix)
{
    int row, col, value;
    char choice;

    // Бесконечный цикл для того, чтобы пользователь мог заполнять несколько ячеек
    while (1)
    {
        // Спросить пользователя, хочет ли он продолжить
        printf("Хотите ввести значение в матрицу? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'n' || choice == 'N')
        {
            break; // Выход из цикла, если пользователь не хочет больше вводить данные
        }

        // Ввод координат
        printf("Введите номер строки (0-%zu): ", matrix->nrows - 1);
        scanf("%d", &row);
        printf("Введите номер столбца (0-%zu): ", matrix->ncols - 1);
        scanf("%d", &col);

        // Проверка корректности введенных координат
        if (row >= 0 && row < matrix->nrows && col >= 0 && col < matrix->ncols)
        {
            // Ввод значения для указанной ячейки
            printf("Введите значение для элемента [%d][%d]: ", row, col);
            scanf("%d", &value);

            // Запись значения в матрицу
            matrix->data[row][col] = value;
        }
        else
        {
            printf("Неверные координаты! Попробуйте еще раз.\n");
        }
    }

    return OK;
}


return_code target_fill_vector(matrix_t* matrix)
{
    int row, value;
    char choice;

    // Бесконечный цикл для того, чтобы пользователь мог заполнять несколько ячеек
    while (1)
    {
        // Спросить пользователя, хочет ли он продолжить
        printf("Хотите ввести значение в матрицу? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'n' || choice == 'N')
        {
            break; // Выход из цикла, если пользователь не хочет больше вводить данные
        }

        // Ввод координат
        printf("Введите номер строки (0-%zu): ", matrix->nrows - 1);
        scanf("%d", &row);

        // Проверка корректности введенных координат
        if (row >= 0 && row < matrix->nrows)
        {
            // Ввод значения для указанной ячейки
            printf("Введите значение для элемента [%d]: ", row);
            scanf("%d", &value);

            // Запись значения в матрицу
            matrix->data[row][0] = value;
        }
        else
        {
            printf("Неверные координаты! Попробуйте еще раз.\n");
        }
    }

    return OK;
}

return_code random_fill(matrix_t* matrix)
{
    size_t filling_percent;
    const return_code rc = input_percent(&filling_percent);

    if (rc == OK)
        matrix_random_fill_percent(matrix, filling_percent);

    printf("[+] Successfully filled %zu%% of matrix with random values\n", filling_percent);
    return rc;
}

void print_matrix_normal(const matrix_t* matrix)
{
    for (int i = 0; i < matrix->nrows; i++)
    {
        // if (matrix->nrows == 1)
        //     printf("( ");
        // else if (i == 0)
        //     printf("/ ");
        // else if (i == matrix->nrows - 1)
        //     printf("\\ ");
        // else
        //     printf("│ ");

        for (int j = 0; j < matrix->ncols; j++)
            printf("%-3d ", matrix->data[i][j]);
        //
        // if (matrix->nrows == 1)
        //     printf(")");
        // else if (i == 0)
        //     printf("\\");
        // else if (i == matrix->nrows - 1)
        //     printf("/");
        // else
        //     printf("│");

        printf("\n");
    }
}

void print_matrix_csr(const csr_matrix* matrix)
{
    printf("VAL           ");
    for (int i = 0; i < matrix->nnz; i++)
        printf("%d  ", matrix->val[i]);
    printf("\n");

    printf("COL           ");
    for (int i = 0; i < matrix->nnz; i++)
        printf("%zu  ", matrix->col[i]);
    printf("\n");

    printf("ROW OFFSET    ");
    for (int i = 0; i < matrix->nrows + 1; i++)
        printf("%zu  ", matrix->row_offset[i]);
    printf("\n");
}
