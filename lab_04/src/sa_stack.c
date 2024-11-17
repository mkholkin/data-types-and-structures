#include "sa_stack.h"

#include <stdlib.h>

array *arr_create(void)
{
    return calloc(1, sizeof(array));
}

void arr_destroy(array *parr)
{
    free(parr);
}

return_code arr_append(const item_t val, array *parr)
{
    if (parr->n == MAX_LENGTH)
        return ERR_STACK_OVERFLOW;

    parr->data[parr->n++] = val;
    return OK;
}

item_t arr_pop(array *parr)
{
    if (!parr->n)
        return 0;

    return parr->data[--parr->n];
}

return_code sa_stack_push(const item_t val, sa_stack *stack)
{
    const return_code rc = arr_append(val, stack->body);

    if (rc == OK)
        stack->head = stack->body->data + stack->body->n - 1;

    return rc;
}

item_t sa_stack_pop(sa_stack *stack)
{
    if (!stack->body->n)
        return 0;

    stack->head -= 1;

    return arr_pop(stack->body);
}

sa_stack *sa_stack_create(void)
{
    sa_stack *stack = calloc(1, sizeof(sa_stack));

    if (!stack)
        return NULL;

    stack->body = calloc(1, sizeof(*stack->body));
    if (!stack->body)
    {
        sa_stack_destroy(stack);
        return NULL;
    }

    stack->head = stack->body->data;

    return stack;
}

void sa_stack_destroy(sa_stack *stack)
{
    free(stack->body);
    free(stack);
}
