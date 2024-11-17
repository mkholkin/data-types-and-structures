#include "../include/commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "iinput_funcs.h"
#include "ll_queue.h"
#include "sa_queue.h"
#include "simuation.h"
#include "utils.h"
#include "utils/time.h"

static double error(double est, double real)
{
    return (real - est) / est * 100;
}


return_code process_run_ll_queue_simulation(const size_t requests_limit, const time_t_ min_enterance,
                                            const time_t_ max_enterence, const time_t_ min_handle,
                                            const time_t_ max_handle)
{
    time_t_ mean_enter_time = (max_enterence - min_enterance) / 2;
    time_t_ mean_handle_time = (max_handle - min_handle) / 2;
    time_t_ est_enter_time = requests_limit * mean_enter_time;


    simulation_result_t result =
        ll_queue_simulate(requests_limit, min_enterance, max_enterence, min_handle, max_handle);

    size_t est_requests_entered = result.simulation_time / mean_enter_time;
    time_t_ est_handle_time = result.handler_triggers * mean_handle_time;
    time_t_ est_simulation_time = est_enter_time > est_handle_time ? est_enter_time : est_handle_time;

    printf(
        "Simulation time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"
        ANSI_COLOR_RESET")\n"\
        "Handler await time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET"\n"\
        "Requests entered: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"ANSI_COLOR_RESET")\n"\
        "Requests out: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET"\n"\
        "Handler triggers: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET"\n"\
        "Handler work time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"
        ANSI_COLOR_RESET")\n",
        result.simulation_time, error(est_simulation_time, result.simulation_time),
        result.handler_await_time,
        result.requests_entered, error(est_requests_entered, result.requests_entered),
        result.requests_out,
        result.handler_triggers,
        result.handler_work_time, error(est_handle_time, result.handler_work_time)
    );

    return OK;
}

return_code process_run_ll_queue_simulation_verbose(const size_t requests_limit, const time_t_ min_enterance,
                                                    const time_t_ max_enterence, const time_t_ min_handle,
                                                    const time_t_ max_handle)
{
    time_t_ mean_enter_time = (max_enterence - min_enterance) / 2;
    time_t_ mean_handle_time = (max_handle - min_handle) / 2;
    time_t_ est_enter_time = requests_limit * mean_enter_time;

    simulation_result_t result = ll_queue_simulate_verbose(requests_limit, min_enterance, max_enterence, min_handle,
                                                           max_handle);

    size_t est_requests_entered = result.simulation_time / mean_enter_time;
    time_t_ est_handle_time = result.handler_triggers * mean_handle_time;
    time_t_ est_simulation_time = est_enter_time > est_handle_time ? est_enter_time : est_handle_time;

    printf(
        "Simulation time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"
        ANSI_COLOR_RESET")\n"\
        "Handler await time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET"\n"\
        "Requests entered: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"ANSI_COLOR_RESET")\n"\
        "Requests out: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET"\n"\
        "Handler triggers: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET"\n"\
        "Handler work time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"
        ANSI_COLOR_RESET")\n",
        result.simulation_time, error(est_simulation_time, result.simulation_time),
        result.handler_await_time,
        result.requests_entered, error(est_requests_entered, result.requests_entered),
        result.requests_out,
        result.handler_triggers,
        result.handler_work_time, error(est_handle_time, result.handler_work_time)
    );

    return OK;
}

return_code process_run_sa_queue_simulation(const size_t requests_limit, const time_t_ min_enterance,
                                            const time_t_ max_enterence, const time_t_ min_handle,
                                            const time_t_ max_handle)
{
    time_t_ mean_enter_time = (max_enterence - min_enterance) / 2;
    time_t_ mean_handle_time = (max_handle - min_handle) / 2;
    time_t_ est_enter_time = requests_limit * mean_enter_time;

    simulation_result_t result =
        sa_queue_simulate(requests_limit, min_enterance, max_enterence, min_handle, max_handle);

    size_t est_requests_entered = result.simulation_time / mean_enter_time;
    time_t_ est_handle_time = result.handler_triggers * mean_handle_time;
    time_t_ est_simulation_time = est_enter_time > est_handle_time ? est_enter_time : est_handle_time;

    if (!result.success)
    {
        printf("[!] "ANSI_COLOR_RED"Error: queue overflow\n"ANSI_COLOR_RESET);
        return OK;
    }

    printf(
        "Simulation time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"
        ANSI_COLOR_RESET")\n"\
        "Handler await time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET"\n"\
        "Requests entered: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"ANSI_COLOR_RESET")\n"\
        "Requests out: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET"\n"\
        "Handler triggers: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET"\n"\
        "Handler work time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"
        ANSI_COLOR_RESET")\n",
        result.simulation_time, error(est_simulation_time, result.simulation_time),
        result.handler_await_time,
        result.requests_entered, error(est_requests_entered, result.requests_entered),
        result.requests_out,
        result.handler_triggers,
        result.handler_work_time, error(est_handle_time, result.handler_work_time)
    );

    return OK;
}

return_code process_run_sa_queue_simulation_verbose(const size_t requests_limit, const time_t_ min_enterance,
                                                    const time_t_ max_enterence, const time_t_ min_handle,
                                                    const time_t_ max_handle)
{
    time_t_ mean_enter_time = (max_enterence - min_enterance) / 2;
    time_t_ mean_handle_time = (max_handle - min_handle) / 2;
    time_t_ est_enter_time = requests_limit * mean_enter_time;

    simulation_result_t result = sa_queue_simulate_verbose(requests_limit, min_enterance, max_enterence, min_handle,
                                                           max_handle);

    size_t est_requests_entered = result.simulation_time / mean_enter_time;
    time_t_ est_handle_time = result.handler_triggers * mean_handle_time;
    time_t_ est_simulation_time = est_enter_time > est_handle_time ? est_enter_time : est_handle_time;

    if (!result.success)
    {
        printf("[!] "ANSI_COLOR_RED"Error: queue overflow\n"ANSI_COLOR_RESET);
        return OK;
    }

    printf(
        "Simulation time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"
        ANSI_COLOR_RESET")\n"\
        "Handler await time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET"\n"\
        "Requests entered: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"ANSI_COLOR_RESET")\n"\
        "Requests out: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET"\n"\
        "Handler triggers: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET"\n"\
        "Handler work time (time unit): "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET" (error: "ANSI_COLOR_RED"%+.2lf%%"
        ANSI_COLOR_RESET")\n",
        result.simulation_time, error(est_simulation_time, result.simulation_time),
        result.handler_await_time,
        result.requests_entered, error(est_requests_entered, result.requests_entered),
        result.requests_out,
        result.handler_triggers,
        result.handler_work_time, error(est_handle_time, result.handler_work_time)
    );

    return OK;
}

return_code process_set_eneter_timeout_interval(time_t_ *min, time_t_ *max)
{
    while (true)
    {
        printf("Setting min timeout\n");
        input_time("Enter min timeout: ", min);
        printf("Setting max timeout\n");
        input_time("Enter max timeout: ", max);

        if (*max < *min)
            printf("[!] Max must be higher or equal than low\n");
        else
            break;
    }

    return OK;
}

return_code process_set_handle_timeout_interval(time_t_ *min, time_t_ *max)
{
    while (true)
    {
        printf("Setting min timeout\n");
        input_time("Enter min timeout: ", min);
        printf("Setting max timeout\n");
        input_time("Enter max timeout: ", max);

        if (*max < *min)
            printf("[!] Max must be higher or equal than low\n");
        else
            break;
    }

    return OK;
}

return_code process_show_stat(void)
{
    ll_queue_t *ll_queue = ll_queue_create();
    sa_queue_t *sa_queue = sa_queue_create();

    const int n = 1000;

    nsec_t sa_strat = nanoseconds_now();
    for (int i = 0; i < n; i++)
        sa_queue_enqueue(sa_queue, (item_t){.cycles_left = 0});
    nsec_t sa_end = nanoseconds_now();


    nsec_t ll_strat = nanoseconds_now();
    for (int i = 0; i < n; i++)
        ll_queue_enqueue(ll_queue, (item_t){.cycles_left = 0});
    nsec_t ll_end = nanoseconds_now();

    const nsec_t sa_enqueue = (sa_end - sa_strat) / n;
    const nsec_t ll_enqueue = (ll_end - ll_strat) / n;

    sa_strat = nanoseconds_now();
    for (int i = 0; i < n; i++)
        sa_queue_dequeue(NULL, sa_queue);
    sa_end = nanoseconds_now();

    const size_t sa_queue_size = sa_queue_sizeof(sa_queue);
    const size_t ll_queue_size = ll_queue_sizeof(ll_queue);

    ll_strat = nanoseconds_now();
    for (int i = 0; i < n; i++)
        ll_queue_dequeue(NULL, ll_queue);
    ll_end = nanoseconds_now();

    const nsec_t sa_dequeue = (sa_end - sa_strat) / n;
    const nsec_t ll_dequeue = (ll_end - ll_strat) / n;

    printf("\n");
    printf(
        "              [ENQUEUE]              \n"\
        "-------------------------------------\n"\
        "       Type        Time (nanoseconds)\n"
        "------------------ ------------------\n"\
        "Static array       %18zu\n"\
        "Linked list        %18zu\n",
        sa_enqueue, ll_enqueue
    );
    printf("\n");
    printf(
        "               [MEMORY]              \n"\
        "-------------------------------------\n"\
        "       Type          Memory (bytes)  \n"
        "------------------ ------------------\n"\
        "Static array       %18zu\n"\
        "Linked list        %18zu\n",
        sa_queue_size,
        ll_queue_size
    );
    printf("\n");
    printf(
        "              [DEQUEUE]              \n"\
        "-------------------------------------\n"\
        "       Type        Time (nanoseconds)\n"
        "------------------ ------------------\n"\
        "Static array       %18zu\n"\
        "Linked list        %18zu\n",
        sa_dequeue, ll_dequeue
    );
    printf("\n");

    ll_queue_destroy(ll_queue);
    sa_queue_destroy(sa_queue);

    return OK;
}

void process_toggle_show_addr(void)
{
    SHOW_ADDR = !SHOW_ADDR;
    printf("Adress visualization: %s\n", SHOW_ADDR ? ANSI_COLOR_GREEN"ON"ANSI_COLOR_RESET : ANSI_COLOR_RED"OFF"ANSI_COLOR_RESET);
}