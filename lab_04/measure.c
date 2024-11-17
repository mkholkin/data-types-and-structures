#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/sa_stack.h"
#include "include/da_stack.h"
#include "include/ll_stack.h"

int main()
{
    FILE *f = fopen("../data/sa_stack.txt", "a");
    for (int i = 1; i <= MAX_LENGTH; i++)
        fprintf(f, "%d %zu\n", i, sizeof(array) + sizeof(sa_stack));
    fclose(f);

    f = fopen("../data/ll_stack.txt", "a");
    for (int i = 1; i <= MAX_LENGTH; i++)
        fprintf(f, "%d %zu\n", i, sizeof(ll_stack) + sizeof(ll_node) * i);
    fclose(f);

    da_stack *stack = da_stack_create();
    f = fopen("../data/da_stack.txt", "a");
    for (int i = 1; i <= MAX_LENGTH; i++)
    {
        da_stack_push(1, stack);
        fprintf(f, "%d %zu\n", i,
                sizeof(da_stack) + sizeof(*stack->body) + sizeof(stack->body->data[0]) * stack->body->n_reserved);
    }
    fclose(f);
    da_stack_destroy(stack);
}
