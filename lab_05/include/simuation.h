#ifndef SIMUATION_H
#define SIMUATION_H

#define REQUESTS_LIMIT_DEFAULT 1000
#define CYCLES_BEFORE_OUT 5
#define MIN_ENTERANCE_DEFAULT 0
#define MAX_ENTERANCE_DEFAULT 6
#define MIN_HANDLE_DEFAULT 0
#define MAX_HANDLE_DEFAULT 1

#include <stdbool.h>

#include "types.h"

extern bool SHOW_ADDR;

typedef struct
{
    bool success;
    time_t_ simulation_time;
    time_t_ handler_work_time;
    time_t_ handler_await_time;
    size_t requests_entered;
    size_t requests_out;
    size_t handler_triggers;
} simulation_result_t;

typedef struct
{
    ticks_t total_time_ticks;
    ticks_t handle_time_ticks;

    size_t requests_entered;
    size_t requests_handled;
    size_t requests_out;
    size_t requests_limit;
    size_t queue_lens_sum;
} simulation_status_t;

simulation_result_t ll_queue_simulate(const size_t requests_limit,
                                      const time_t_ min_enterance,
                                      const time_t_ max_enterence,
                                      const time_t_ min_handle,
                                      const time_t_ max_handle);
simulation_result_t ll_queue_simulate_verbose(const size_t requests_limit,
                                             const time_t_ min_enterance,
                                             const time_t_ max_enterence,
                                             const time_t_ min_handle,
                                             const time_t_ max_handle);
simulation_result_t sa_queue_simulate(const size_t requests_limit,
                                      const time_t_ min_enterance,
                                      const time_t_ max_enterence,
                                      const time_t_ min_handle,
                                      const time_t_ max_handle);
simulation_result_t sa_queue_simulate_verbose(const size_t requests_limit,
                                              const time_t_ min_enterance,
                                              const time_t_ max_enterence,
                                              const time_t_ min_handle,
                                              const time_t_ max_handle);

void show_simulation_status(const simulation_status_t *status);

#endif //SIMUATION_H
