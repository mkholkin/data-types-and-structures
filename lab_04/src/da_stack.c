#include "da_stack.h"

#include <stdlib.h>

return_code da_stack_push(const item_t val, da_stack *stack)
{
    const return_code rc = da_append(val, stack->body);

    if (rc == OK)
        stack->head = stack->body->data + stack->body->n - 1;

    return rc;
}

item_t da_stack_pop(da_stack *stack)
{
    if (!stack->body->n)
        return 0;

    stack->head -= 1;

    return da_pop(stack->body);
}

return_code da_append(const item_t val, dyn_arr *parr)
{
    if (parr->data == NULL)
    {
        parr->data = calloc(DA_INIT_SIZE, sizeof(item_t));
        if (parr->data == NULL)
            return ERR_MEMORY;
    }

    if (parr->n == parr->n_reserved)
    {
        item_t *tmp = realloc(parr->data, parr->n_reserved * DA_STEP * sizeof(item_t));
        if (tmp == NULL)
            return ERR_MEMORY;

        parr->data = tmp;
        parr->n_reserved *= DA_STEP;
    }

    parr->data[parr->n++] = val;

    return OK;
}

item_t da_pop(dyn_arr *parr)
{
    if (!parr->n)
        return 0;

    return parr->data[--parr->n];
}

dyn_arr *da_create(void)
{
    dyn_arr *parr = calloc(1, sizeof(dyn_arr));
    if (parr == NULL)
        return NULL;

    parr->data = calloc(DA_INIT_SIZE, sizeof(item_t));
    if (parr->data == NULL)
    {
        da_destroy(parr);
        return NULL;
    }

    parr->n_reserved = DA_INIT_SIZE;
    parr->n = 0;

    return parr;
}

void da_destroy(dyn_arr *parr)
{
    free(parr->data);
    free(parr);
}

da_stack *da_stack_create(void)
{
    da_stack *stack = calloc(1, sizeof(da_stack));

    if (!stack)
        return NULL;

    stack->body = da_create();
    if (!stack->body)
    {
        da_stack_destroy(stack);
        return NULL;
    }

    stack->head = stack->body->data;

    return stack;
}

void da_stack_destroy(da_stack *stack)
{
    da_destroy(stack->body);
    free(stack);
}
