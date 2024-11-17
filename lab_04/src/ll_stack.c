#include "ll_stack.h"

#include <stddef.h>
#include <stdlib.h>

return_code ll_stack_push(ll_stack *stack)
{
    ll_node *node = ll_node_create(0, stack->head);
    if (node == NULL)
        return ERR_MEMORY;

    node->val = (uintptr_t)node;
    stack->head = node;

    return OK;
}

item_t ll_stack_pop(ll_stack *stack)
{
    if (!stack->head)
        return 0;

    const item_t val = stack->head->val;
    ll_node *new_head = stack->head->next;

    ll_node_destroy(stack->head);
    stack->head = new_head;

    return val;
}

ll_node *ll_node_create(const item_t val, ll_node *next)
{
    ll_node *node = calloc(1, sizeof(ll_node));

    if (node == NULL)
        return NULL;

    node->val = val;
    node->next = next;

    return node;
}

void ll_node_destroy(ll_node *node)
{
    free(node);
}


ll_stack *ll_stack_create(void)
{
    ll_stack *stack = calloc(1, sizeof(ll_stack));
    if (!stack)
        return NULL;

    return stack;
}

void ll_stack_destroy(ll_stack *stack)
{
    for (ll_node *cursor = stack->head; cursor; cursor = cursor->next)
        ll_node_destroy(cursor);

    free(stack);
}