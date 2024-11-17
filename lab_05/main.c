#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "commands.h"
#include "simuation.h"

#define CHOICE_COMMANDS_MENU \
"Chose command:\n"\
"   [1] Run list queue simulation\n"\
"   [2] Run list queue simulation (VERBOSE)\n"\
"   [3] Run array queue simulation\n"\
"   [4] Run array queue simulation (VERBOSE)\n"\
"   [5] Set enterance timeout\n"\
"   [6] Set handle timeout\n"\
"   [7] Show stat\n"\
"   [8] Toggle address visualization\n"\
"\n"\
"   [0] Exit\n"
return_code start_polling(size_t *requests_limit,
                          time_t_ *min_enterance,
                          time_t_ *max_enterence,
                          time_t_ *min_handle,
                          time_t_ *max_handle);
return_code exec_command(size_t *requests_limit,
                         time_t_ *min_enterance,
                         time_t_ *max_enterence,
                         time_t_ *min_handle,
                         time_t_ *max_handle);

bool SHOW_ADDR = false;

int main(void)
{
    size_t requests_limit = REQUESTS_LIMIT_DEFAULT;
    time_t_ min_enterance = MIN_ENTERANCE_DEFAULT;
    time_t_ max_enterance = MAX_ENTERANCE_DEFAULT;
    time_t_ min_handle = MIN_HANDLE_DEFAULT;
    time_t_ max_handle = MAX_HANDLE_DEFAULT;
    return start_polling(&requests_limit, &min_enterance, &max_enterance, &min_handle, &max_handle);
}

return_code start_polling(size_t *requests_limit,
                          time_t_ *min_enterance,
                          time_t_ *max_enterence,
                          time_t_ *min_handle,
                          time_t_ *max_handle)
{
    return_code rc;

    do
    {
        rc = exec_command(requests_limit, min_enterance, max_enterence, min_handle, max_handle);
    }
    while (rc == OK);

    return rc;
}

return_code exec_command(size_t *requests_limit,
                         time_t_ *min_enterance,
                         time_t_ *max_enterence,
                         time_t_ *min_handle,
                         time_t_ *max_handle)
{
    return_code rc;
    char *user_choice = NULL;

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
            rc = process_run_ll_queue_simulation(*requests_limit, *min_enterance, *max_enterence, *min_handle,
                                                 *max_handle);
            break;
        case 2:
            rc = process_run_ll_queue_simulation_verbose(*requests_limit, *min_enterance, *max_enterence, *min_handle,
                                                 *max_handle);
            break;
        case 3:
            rc = process_run_sa_queue_simulation(*requests_limit, *min_enterance, *max_enterence, *min_handle,
                                                 *max_handle);
            break;
        case 4:
            rc = process_run_sa_queue_simulation_verbose(*requests_limit, *min_enterance, *max_enterence, *min_handle,
                                                 *max_handle);
            break;
        case 5:
            rc = process_set_eneter_timeout_interval(min_enterance, max_enterence);
            break;
        case 6:
            rc = process_set_handle_timeout_interval(min_handle, max_handle);
            break;
        case 7:
            rc = process_show_stat();
            break;
        case 8:
            process_toggle_show_addr();
            break;
        default:
            assert(0);
        }

        if (rc == DIALOG_EXIT)
            rc = OK;
    }

    return rc;
}
