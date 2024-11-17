#ifndef LL_STACK_H
#define LL_STACK_H

#include "types.h"
#include "return_codes.h"

struct ll_node
{
    item_t val;
    struct ll_node *next;
};

typedef struct ll_node ll_node;

typedef struct
{
    ll_node *head;
} ll_stack;

ll_node *ll_node_create(item_t val, ll_node *next);
void ll_node_destroy(ll_node *node);

return_code ll_stack_push(ll_stack *stack);
item_t ll_stack_pop(ll_stack *stack);

ll_stack *ll_stack_create(void);
void ll_stack_destroy(ll_stack *stack);

#endif //LL_STACK_H
