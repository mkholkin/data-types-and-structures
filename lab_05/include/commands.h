#ifndef COMMANDS_H
#define COMMANDS_H

#include "return_codes.h"
#include "types.h"

return_code process_run_ll_queue_simulation(const size_t requests_limit,
                                            const time_t_ min_enterance,
                                            const time_t_ max_enterence,
                                            const time_t_ min_handle,
                                            const time_t_ max_handle);
return_code process_run_ll_queue_simulation_verbose(const size_t requests_limit,
                                                    const time_t_ min_enterance,
                                                    const time_t_ max_enterence,
                                                    const time_t_ min_handle,
                                                    const time_t_ max_handle);
return_code process_run_sa_queue_simulation(const size_t requests_limit,
                                            const time_t_ min_enterance,
                                            const time_t_ max_enterence,
                                            const time_t_ min_handle,
                                            const time_t_ max_handle);
return_code process_run_sa_queue_simulation_verbose(const size_t requests_limit,
                                                    const time_t_ min_enterance,
                                                    const time_t_ max_enterence,
                                                    const time_t_ min_handle,
                                                    const time_t_ max_handle);
return_code process_set_eneter_timeout_interval(time_t_ *min, time_t_ *max);
return_code process_set_handle_timeout_interval(time_t_ *min, time_t_ *max);
return_code process_show_stat(void);
void process_toggle_show_addr(void);

#endif //COMMANDS_H
