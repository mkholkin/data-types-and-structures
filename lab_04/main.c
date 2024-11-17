#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "da_stack.h"
#include "ll_stack.h"
#include "return_codes.h"
#include "sa_stack.h"
#include "io/io.h"

#define CHOICE_COMMANDS_MENU \
"Chose command:\n"\
"   [1] LL push\n"\
"   [2] LL pop\n"\
"   [3] LL print\n"\
"   [4] LL clear\n"\
"\n"\
"   [5] SA push\n"\
"   [6] SA pop\n"\
"   [7] SA print\n"\
"   [8] SA clear\n"\
"\n"\
"   [9] DA push\n"\
"   [10] DA pop\n"\
"   [11] DA print\n"\
"   [12] DA clear\n"\
"\n"\
"   [13] Show stat\n"\
"\n"\
"   [0] Exit\n"\
"\n"

return_code start_polling(ll_stack *ll_stack, sa_stack *sa_stack, da_stack *da_stack, dyn_arr *freed_ptrs);
return_code exec_command(ll_stack *ll_stack, sa_stack *sa_stack, da_stack *da_stack, dyn_arr *freed_ptrs);

int main(void)
{
    ll_stack *ll_stack = ll_stack_create();
    sa_stack *sa_stack = sa_stack_create();
    da_stack *da_stack = da_stack_create();

    dyn_arr *freed_ptrs = da_create();

    assert(da_stack->body);
    assert(da_stack->body->data);

    const return_code rc = start_polling(ll_stack, sa_stack, da_stack, freed_ptrs);

    ll_stack_destroy(ll_stack);
    sa_stack_destroy(sa_stack);
    da_stack_destroy(da_stack);
    
    return rc;
}

return_code start_polling(ll_stack *ll_stack, sa_stack *sa_stack, da_stack *da_stack, dyn_arr *freed_ptrs)
{
    return_code rc;

    do
    {
        rc = exec_command(ll_stack, sa_stack, da_stack, freed_ptrs);
    }
    while (rc == OK);

    return rc;
}

return_code exec_command(ll_stack *ll_stack, sa_stack *sa_stack, da_stack *da_stack, dyn_arr *freed_ptrs)
{
    return_code rc;
    const char* user_choice = NULL;

    printf(CHOICE_COMMANDS_MENU);
    do
    {
        rc = input_user_choice(&user_choice, "0", 13, "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13");
    }
    while ((rc == OK || should_retry(rc)) && user_choice == NULL);

    if (rc == OK)
    {
        switch (atoi(user_choice))
        {
        case 1:
            rc = process_ll_stack_push(ll_stack);
            break;
        case 2:
            process_ll_stack_pop(ll_stack, freed_ptrs);
            break;
        case 3:
            process_ll_stack_show(ll_stack, freed_ptrs);
            break;
        case 4:
            process_ll_stack_clear(ll_stack, freed_ptrs);
            break;
        case 5:
            rc = process_sa_stack_push(sa_stack);
            break;
        case 6:
            process_sa_stack_pop(sa_stack);
            break;
        case 7:
            process_sa_stack_show(sa_stack);
            break;
        case 8:
            process_sa_stack_clear(sa_stack);
            break;
        case 9:
            rc = process_da_stack_push(da_stack);
            break;
        case 10:
            process_da_stack_pop(da_stack);
            break;
        case 11:
            process_da_stack_show(da_stack);
            break;
        case 12:
            process_da_stack_clear(da_stack);
            break;
        case 13:
            process_show_stat(sa_stack, da_stack, ll_stack);
            break;
        default:
            assert(0);
        }

        if (rc == DIALOG_EXIT)
            rc = OK;
    }

    return rc;
}
