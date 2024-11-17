#include "../include/commands.h"

#include <stdio.h>

#include "io/ptr_io.h"
#include "utils/time.h"
#include "utils/utils.h"

return_code process_sa_stack_push(sa_stack *stack)
{
    item_t val;
    input_ptr("Enter ptr: ", &val);

    return_code rc = sa_stack_push(val, stack);
    if (rc == ERR_STACK_OVERFLOW)
    {
        printf("[!] Can't perform stack limit reached\n");
        rc = OK;
    }

    return rc;
}

void process_sa_stack_pop(sa_stack *stack)
{
    const item_t val = sa_stack_pop(stack);

    if (val)
        printf("%p\n", val);
    else
        printf("[!] Stack is empty\n");
}

void process_sa_stack_show(const sa_stack *stack)
{
    printf("Actual space: %zu bytes\n", sizeof(stack->body->data));
    printf("Used space: %zu bytes\n", sizeof(stack->body->data[0]) * stack->body->n);
    for (int i = stack->body->n - 1; i >= 0; i--)
        printf("%p\n", stack->body->data[i]);
}

void process_sa_stack_clear(sa_stack *stack)
{
    stack->body->n = 0;
}

return_code process_da_stack_push(da_stack *stack)
{
    item_t val;
    input_ptr("Enter ptr: ", &val);
    return da_stack_push(val, stack);
}

void process_da_stack_pop(da_stack *stack)
{
    const item_t val = da_stack_pop(stack);

    if (val)
        printf("%p\n", val);
    else
        printf("[!] Stack is empty\n");
}

void process_da_stack_show(const da_stack *stack)
{
    printf("Actual space: %zu bytes\n", sizeof(stack->body->data[0]) * stack->body->n_reserved);
    printf("Used space: %zu bytes\n", sizeof(stack->body->data[0]) * stack->body->n);

    for (int i = stack->body->n - 1; i >= 0; i--)
        printf("%p\n", stack->body->data[i]);
}

void process_da_stack_clear(da_stack *stack)
{
    stack->body->n = 0;
}

return_code process_ll_stack_push(ll_stack *stack)
{
    return ll_stack_push(stack);
}

void process_ll_stack_pop(ll_stack *stack, dyn_arr *freed_ptrs)
{
    const item_t val = ll_stack_pop(stack);

    if (val)
    {
        if (!is_in(freed_ptrs->data, sizeof(item_t), freed_ptrs->n, &val))
            da_append(val, freed_ptrs);
        printf("%p\n", val);
    }
    else
        printf("[!] Stack is empty\n");
}

void process_ll_stack_show(const ll_stack *stack, const dyn_arr *freed_ptrs)
{
    if (stack->head == NULL)
    {
        printf("[!] Stack is empty\n");
        return;
    }

    int i = 0;
    ll_node *cursor = stack->head;
    while (cursor || i < freed_ptrs->n)
    {
        if (!cursor)
        {
            printf("               "ANSI_COLOR_RED"%p\n"ANSI_COLOR_RESET, freed_ptrs->data[i]);
            i++;
        }
        else if (i >= freed_ptrs->n)
        {
            printf(ANSI_COLOR_CYAN"%p\n"ANSI_COLOR_RESET, cursor);
            cursor = cursor->next;
        }
        else
        {
            if (freed_ptrs->data[i] > cursor->val)
            {
                printf("               "ANSI_COLOR_RED"%p\n"ANSI_COLOR_RESET, freed_ptrs->data[i]);
                i++;
            }
            else
            {
                printf(ANSI_COLOR_CYAN"%p\n"ANSI_COLOR_RESET, cursor);
                cursor = cursor->next;
            }
        }
    }
}

void process_ll_stack_clear(ll_stack *stack, dyn_arr *freed_ptrs)
{
    item_t val;
    while (val = ll_stack_pop(stack))
        if (!is_in(freed_ptrs->data, sizeof(item_t), freed_ptrs->n, &val))
            da_append(val, freed_ptrs);
}

void process_show_stat(sa_stack *sa_stack, da_stack *da_stack, ll_stack *ll_stack)
{
    process_sa_stack_clear(sa_stack);
    process_da_stack_clear(da_stack);
    process_ll_stack_clear(ll_stack, NULL);

    const int n = 100;

    nsec_t sa_strat = nanoseconds_now();
    for (int i = 0; i < n; i++)
        sa_stack_push(1, sa_stack);
    nsec_t sa_end = nanoseconds_now();

    nsec_t da_strat = nanoseconds_now();
    for (int i = 0; i < n; i++)
        da_stack_push(1, da_stack);
    nsec_t da_end = nanoseconds_now();

    nsec_t ll_strat = nanoseconds_now();
    for (int i = 0; i < n; i++)
        ll_stack_push(ll_stack);
    nsec_t ll_end = nanoseconds_now();

    const nsec_t sa_push = (sa_end - sa_strat) / n;
    const nsec_t da_push = (da_end - da_strat) / n;
    const nsec_t ll_push = (ll_end - ll_strat) / n;

    sa_strat = nanoseconds_now();
    for (int i = 0; i < n; i++)
        sa_stack_pop(sa_stack);
    sa_end = nanoseconds_now();

    da_strat = nanoseconds_now();
    for (int i = 0; i < n; i++)
        da_stack_pop(da_stack);
    da_end = nanoseconds_now();

    ll_strat = nanoseconds_now();
    for (int i = 0; i < n; i++)
        ll_stack_pop(ll_stack);
    ll_end = nanoseconds_now();

    const nsec_t sa_pop = (sa_end - sa_strat) / n;
    const nsec_t da_pop = (da_end - da_strat) / n;
    const nsec_t ll_pop = (ll_end - ll_strat) / n;

    printf(
        "                [PUSH]               \n"\
        "-------------------------------------\n"\
        "       Type        Time (nanoseconds)\n"
        "------------------ ------------------\n"\
        "Static array       %18zu\n"\
        "Dynamic array      %18zu\n"\
        "Linked list        %18zu\n",
        sa_push, da_push, ll_push
    );
    printf("\n");
    printf(
        "               [MEMORY]              \n"\
        "-------------------------------------\n"\
        "       Type          Memory (bytes)  \n"
        "------------------ ------------------\n"\
        "Static array       %18zu\n"\
        "Dynamic array      %18zu\n"\
        "Linked list        %18zu\n",
        sizeof(sa_stack) + sizeof(*sa_stack->body),
        sizeof(da_stack) + sizeof(*da_stack->body) + sizeof(da_stack->body->data[0]) * da_stack->body->n_reserved,
        sizeof(ll_stack) + sizeof(*ll_stack->head) * n
    );
    printf("\n");
    printf(
        "                [POP]                \n"\
        "-------------------------------------\n"\
        "       Type        Time (nanoseconds)\n"
        "------------------ ------------------\n"\
        "Static array       %18zu\n"\
        "Dynamic array      %18zu\n"\
        "Linked list        %18zu\n",
        sa_pop, da_pop, ll_pop
    );
    printf("\n");
}
