#ifndef SA_STACK_H
#define SA_STACK_H

#define MAX_LENGTH 100

#include <stddef.h>

#include "return_codes.h"
#include "types.h"

typedef struct
{
    size_t n;
    item_t data[MAX_LENGTH];
} array;

typedef struct
{
    array *body;
    item_t *head;
} sa_stack;

array *arr_create(void);
void arr_destroy(array *parr);

return_code arr_append(const item_t val, array *parr);
item_t arr_pop(array *parr);

return_code sa_stack_push(const item_t val, sa_stack *stack);
item_t sa_stack_pop(sa_stack *stack);

sa_stack *sa_stack_create(void);
void sa_stack_destroy(sa_stack *stack);

#endif //SA_STACK_H
