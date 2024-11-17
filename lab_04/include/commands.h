#ifndef COMMANDS_H
#define COMMANDS_H
#include "sa_stack.h"
#include "da_stack.h"
#include "ll_stack.h"
#include "return_codes.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

return_code process_sa_stack_push(sa_stack *stack);
void process_sa_stack_pop(sa_stack *stack);
void process_sa_stack_show(const sa_stack *stack);
void process_sa_stack_clear(sa_stack *stack);

return_code process_da_stack_push(da_stack *stack);
void process_da_stack_pop(da_stack *stack);
void process_da_stack_show(const da_stack *stack);
void process_da_stack_clear(da_stack *stack);

return_code process_ll_stack_push(ll_stack *stack);
void process_ll_stack_pop(ll_stack *stack, dyn_arr *freed_ptrs);
void process_ll_stack_show(const ll_stack *stack, const dyn_arr *freed_ptrs);
void process_ll_stack_clear(ll_stack *stack, dyn_arr *freed_ptrs);

void process_show_stat(sa_stack *sa_stack, da_stack *da_stack, ll_stack *ll_stack);

#endif //COMMANDS_H
