#include "simuation.h"

#include <stdio.h>
#include <stdlib.h>

#include "sa_queue.h"
#include "ll_queue.h"

#include "utils.h"

#define TIME_UNIT_TICKS 1e5

static time_t_ rand_time(const time_t_ min, const time_t_ max)
{
    const double range = max - min;
    if (range == 0)
        return min;

    const double div = RAND_MAX / range;
    return min + rand() / div;
}

static ticks_t time_to_ticks(const time_t_ time)
{
    return time * TIME_UNIT_TICKS;
}

static time_t_ ticks_to_time(const ticks_t ticks)
{
    return (double)ticks / TIME_UNIT_TICKS;
}


simulation_result_t ll_queue_simulate(const size_t requests_limit,
                                      const time_t_ min_enterance,
                                      const time_t_ max_enterence,
                                      const time_t_ min_handle,
                                      const time_t_ max_handle)
{
    ticks_t enter_timeout_ticks = time_to_ticks(rand_time(min_enterance, max_enterence));
    ticks_t handle_timeout_ticks = time_to_ticks(rand_time(min_handle, max_handle));

    simulation_status_t status = {
        .requests_entered = 0,
        .requests_handled = 0,
        .requests_out = 0,
        .requests_limit = requests_limit,
        .total_time_ticks = 0,
        .handle_time_ticks = 0,
    };

    request_t entering_request = {.cycles_left = CYCLES_BEFORE_OUT - 1};

    ll_queue_t *queue = ll_queue_create();

    while (status.requests_out < requests_limit)
    {
        if (enter_timeout_ticks == 0)
        {
            ll_queue_enqueue(queue, entering_request);
            entering_request = (request_t){.cycles_left = CYCLES_BEFORE_OUT - 1};
            enter_timeout_ticks = time_to_ticks(rand_time(min_enterance, max_enterence));
            status.requests_entered++;
        }
        else
            enter_timeout_ticks--;

        if (!ll_queue_is_empty(queue))
        {
            if (handle_timeout_ticks == 0)
            {
                const request_t *handling_request = ll_queue_get_first(queue);

                if (handling_request->cycles_left)
                    ll_queue_enqueue(queue, (request_t){.cycles_left = handling_request->cycles_left - 1});
                else
                {
                    status.requests_out++;
                }

                ll_queue_dequeue(NULL, queue);
                handle_timeout_ticks = time_to_ticks(rand_time(min_handle, max_handle));
                status.requests_handled++;
            }
            else
            {
                status.handle_time_ticks++;
                handle_timeout_ticks--;
            }
        }

        status.queue_lens_sum += status.requests_entered - status.requests_out;
        status.total_time_ticks++;
    }

    ll_queue_destroy(queue);

    return (simulation_result_t){
        .simulation_time = ticks_to_time(status.total_time_ticks),
        .handler_work_time = ticks_to_time(status.handle_time_ticks),
        .handler_await_time = ticks_to_time(status.total_time_ticks - status.handle_time_ticks),
        .requests_entered = status.requests_entered,
        .requests_out = status.requests_out,
        .handler_triggers = status.requests_handled,
    };
}


simulation_result_t ll_queue_simulate_verbose(const size_t requests_limit,
                                              const time_t_ min_enterance,
                                              const time_t_ max_enterence,
                                              const time_t_ min_handle,
                                              const time_t_ max_handle)
{
    ticks_t enter_timeout_ticks = time_to_ticks(rand_time(min_enterance, max_enterence));
    ticks_t handle_timeout_ticks = time_to_ticks(rand_time(min_handle, max_handle));

    simulation_status_t status = {
        .requests_entered = 0,
        .requests_handled = 0,
        .requests_out = 0,
        .requests_limit = requests_limit,
        .total_time_ticks = 0,
        .handle_time_ticks = 0,
    };

    request_t entering_request = {.cycles_left = CYCLES_BEFORE_OUT - 1};

    ll_queue_t *queue = ll_queue_create();

    while (status.requests_out < requests_limit)
    {
        if (enter_timeout_ticks == 0)
        {
            ll_queue_enqueue(queue, entering_request);
            entering_request = (request_t){.cycles_left = CYCLES_BEFORE_OUT - 1};
            enter_timeout_ticks = time_to_ticks(rand_time(min_enterance, max_enterence));
            status.requests_entered++;
        }
        else
            enter_timeout_ticks--;

        if (!ll_queue_is_empty(queue))
        {
            if (handle_timeout_ticks == 0)
            {
                const request_t *handling_request = ll_queue_get_first(queue);

                if (handling_request->cycles_left)
                    ll_queue_enqueue(queue, (request_t){.cycles_left = handling_request->cycles_left - 1});
                else
                {
                    status.requests_out++;

                    if (status.requests_out > 0 && status.requests_out % 100 == 0)
                        show_simulation_status(&status);
                }

                ll_queue_dequeue(NULL, queue);
                handle_timeout_ticks = time_to_ticks(rand_time(min_handle, max_handle));
                status.requests_handled++;
            }
            else
            {
                status.handle_time_ticks++;
                handle_timeout_ticks--;
            }
        }

        status.queue_lens_sum += status.requests_entered - status.requests_out;
        status.total_time_ticks++;
    }

    ll_queue_destroy(queue);

    return (simulation_result_t){
        .simulation_time = ticks_to_time(status.total_time_ticks),
        .handler_work_time = ticks_to_time(status.handle_time_ticks),
        .handler_await_time = ticks_to_time(status.total_time_ticks - status.handle_time_ticks),
        .requests_entered = status.requests_entered,
        .requests_out = status.requests_out,
        .handler_triggers = status.requests_handled,
    };
}

simulation_result_t sa_queue_simulate(const size_t requests_limit,
                                      const time_t_ min_enterance,
                                      const time_t_ max_enterence,
                                      const time_t_ min_handle,
                                      const time_t_ max_handle)
{
    ticks_t enter_timeout_ticks = time_to_ticks(rand_time(min_enterance, max_enterence));
    ticks_t handle_timeout_ticks = time_to_ticks(rand_time(min_handle, max_handle));

    simulation_status_t status = {
        .requests_entered = 0,
        .requests_handled = 0,
        .requests_out = 0,
        .requests_limit = requests_limit,
        .total_time_ticks = 0,
        .handle_time_ticks = 0,
    };

    request_t entering_request = {.cycles_left = CYCLES_BEFORE_OUT - 1};

    sa_queue_t *queue = sa_queue_create();

    while (status.requests_out < requests_limit)
    {
        if (enter_timeout_ticks == 0)
        {
            if (sa_queue_enqueue(queue, entering_request) == ERR_FULL)
                return (simulation_result_t) {.success = false};
            entering_request = (request_t){.cycles_left = CYCLES_BEFORE_OUT - 1};
            enter_timeout_ticks = time_to_ticks(rand_time(min_enterance, max_enterence));
            status.requests_entered++;
        }
        else
            enter_timeout_ticks--;

        if (!sa_queue_is_empty(queue))
        {
            if (handle_timeout_ticks == 0)
            {
                const request_t *handling_request = sa_queue_get_first(queue);

                if (handling_request->cycles_left)
                    sa_queue_enqueue(queue, (request_t){.cycles_left = handling_request->cycles_left - 1});
                else
                {
                    status.requests_out++;
                }

                sa_queue_dequeue(NULL, queue);
                handle_timeout_ticks = time_to_ticks(rand_time(min_handle, max_handle));
                status.requests_handled++;
            }
            else
            {
                status.handle_time_ticks++;
                handle_timeout_ticks--;
            }
        }

        status.queue_lens_sum += status.requests_entered - status.requests_out;
        status.total_time_ticks++;
    }

    sa_queue_destroy(queue);

    return (simulation_result_t){
        .success = true,
        .simulation_time = ticks_to_time(status.total_time_ticks),
        .handler_work_time = ticks_to_time(status.handle_time_ticks),
        .handler_await_time = ticks_to_time(status.total_time_ticks - status.handle_time_ticks),
        .requests_entered = status.requests_entered,
        .requests_out = status.requests_out,
        .handler_triggers = status.requests_handled,
    };
}

simulation_result_t sa_queue_simulate_verbose(const size_t requests_limit,
                                              const time_t_ min_enterance,
                                              const time_t_ max_enterence,
                                              const time_t_ min_handle,
                                              const time_t_ max_handle)
{
    ticks_t enter_timeout_ticks = time_to_ticks(rand_time(min_enterance, max_enterence));
    ticks_t handle_timeout_ticks = time_to_ticks(rand_time(min_handle, max_handle));

    simulation_status_t status = {
        .requests_entered = 0,
        .requests_handled = 0,
        .requests_out = 0,
        .requests_limit = requests_limit,
        .total_time_ticks = 0,
        .handle_time_ticks = 0,
    };

    request_t entering_request = {.cycles_left = CYCLES_BEFORE_OUT - 1};

    sa_queue_t *queue = sa_queue_create();

    while (status.requests_out < requests_limit)
    {
        if (enter_timeout_ticks == 0)
        {
            if (sa_queue_enqueue(queue, entering_request) == ERR_FULL)
                return (simulation_result_t) {.success = false};
            entering_request = (request_t){.cycles_left = CYCLES_BEFORE_OUT - 1};
            enter_timeout_ticks = time_to_ticks(rand_time(min_enterance, max_enterence));
            status.requests_entered++;
        }
        else
            enter_timeout_ticks--;

        if (!sa_queue_is_empty(queue))
        {
            if (handle_timeout_ticks == 0)
            {
                const request_t *handling_request = sa_queue_get_first(queue);

                if (handling_request->cycles_left)
                    sa_queue_enqueue(queue, (request_t){.cycles_left = handling_request->cycles_left - 1});
                else
                {
                    status.requests_out++;

                    if (status.requests_out > 0 && status.requests_out % 100 == 0)
                        show_simulation_status(&status);
                }

                sa_queue_dequeue(NULL, queue);
                handle_timeout_ticks = time_to_ticks(rand_time(min_handle, max_handle));
                status.requests_handled++;
            }
            else
            {
                status.handle_time_ticks++;
                handle_timeout_ticks--;
            }
        }

        status.queue_lens_sum += status.requests_entered - status.requests_out;
        status.total_time_ticks++;
    }

    sa_queue_destroy(queue);

    return (simulation_result_t){
        .simulation_time = ticks_to_time(status.total_time_ticks),
        .handler_work_time = ticks_to_time(status.handle_time_ticks),
        .handler_await_time = ticks_to_time(status.total_time_ticks - status.handle_time_ticks),
        .requests_entered = status.requests_entered,
        .requests_out = status.requests_out,
        .handler_triggers = status.requests_handled,
    };
}

void show_simulation_status(const simulation_status_t *status)
{
    printf("[%zu/%zu] Queue status:\n", status->requests_out, status->requests_limit);
    printf(
        "   Reqeusts in queue: "ANSI_COLOR_CYAN"%zu"ANSI_COLOR_RESET"\n"\
        "   Mean requests in queue: "ANSI_COLOR_CYAN"%lf"ANSI_COLOR_RESET"\n",
        status->requests_entered - status->requests_out,
        (double) status->queue_lens_sum / status->total_time_ticks
    );
}
