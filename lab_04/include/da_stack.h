#ifndef DA_STACK_H
#define DA_STACK_H

#include <stddef.h>

#include "return_codes.h"
#include "types.h"

#define DA_STEP 2
#define DA_INIT_SIZE 16

typedef struct
{
    size_t n;
    size_t n_reserved;
    item_t *data;
} dyn_arr;

typedef struct
{
    dyn_arr *body;
    item_t *head;
} da_stack;

dyn_arr *da_create(void);
void da_destroy(dyn_arr *parr);

return_code da_append(const item_t val, dyn_arr *parr);
item_t da_pop(dyn_arr *parr);

return_code da_stack_push(const item_t val, da_stack *stack);
item_t da_stack_pop(da_stack *stack);

da_stack *da_stack_create(void);
void da_stack_destroy(da_stack *stack);
#endif //DA_STACK_H
