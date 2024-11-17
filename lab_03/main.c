#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "matrix_operations.h"
#include "return_codes.h"
#include "types.h"
#include "io/io.h"

#define CHOICE_COMMANDS_MENU \
"Chose command:\n"\
"   [1] Set multipliers (Matrix & Vector)\n"\
"   [2] Show matrix\n"\
"   [3] Show matrix in CSR view\n"\
"   [4] Show vector\n"\
"   [5] Show vector in CSR view\n"\
"   [6] Multiply\n"\
"   [7] Multiply CSR (Matrix × Vector)\n"\
"   [8] Show stat\n"\
"\n"\
"   [0] Exit\n"\
"\n"

return_code start_polling(matrix_t* m, csr_matrix* sm, matrix_t* v, csr_vector* sv);
return_code exec_command(matrix_t* m, csr_matrix* sm, matrix_t* v, csr_vector* sv);

int main(void)
{
    matrix_t m = {0}, v = {0};
    csr_matrix sm = {0};
    csr_vector sv = {0};

    return start_polling(&m, &sm, &v, &sv);
}


return_code start_polling(matrix_t* m, csr_matrix* sm, matrix_t* v, csr_vector* sv)
{
    return_code rc;

    do
    {
        rc = exec_command(m, sm, v, sv);
    }
    while (rc == OK);

    return rc;
}

return_code exec_command(matrix_t* m, csr_matrix* sm, matrix_t* v, csr_vector* sv)
{
    return_code rc;
    const char* user_choice = NULL;

    printf(CHOICE_COMMANDS_MENU);
    do
    {
        rc = input_user_choice(&user_choice, "0", 8, "1", "2", "3", "4", "5", "6", "7", "8");
    }
    while ((rc == OK || should_retry(rc)) && user_choice == NULL);

    if (rc == OK)
    {
        switch (atoi(user_choice))
        {
        case 1:
            rc = process_set_multipliers(m, sm, v, sv);
            break;
        case 2:
            process_print_matrix(m);
            break;
        case 3:
            process_print_spare_matrix(sm);
            break;
        case 4:
            process_print_vector(v);
            break;
        case 5:
            process_print_spare_vector(sv);
            break;
        case 6:
            process_multiply(m, v);
            break;
        case 7:
            process_multiply_spare_mv(sm, sv);
            break;
        case 8:
            process_show_stat(m, sm, v, sv);
            break;
        default:
            assert(0);
        }

        if (rc == DIALOG_EXIT)
            rc = OK;
    }

    return rc;
}
