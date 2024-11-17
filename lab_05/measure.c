#include <stdio.h>

#include "ll_queue.h"
#include "sa_queue.h"

int main()
{
    sa_queue_t *a = sa_queue_create();
    FILE *f = fopen("../data/sa_queue.txt", "a");
    for (int i = 0; i <= MAX_SIZE; i++)
        fprintf(f, "%d, %zu\n", i, sa_queue_sizeof(a));
    fclose(f);
    sa_queue_destroy(a);

    ll_queue_t *queue = ll_queue_create();
    f = fopen("../data/ll_queue.txt", "a");
    for (int i = 0; i <= MAX_SIZE; i++)
    {
        ll_queue_enqueue(queue, (item_t) {1});
        fprintf(f, "%d %zu\n", i, ll_queue_sizeof(queue));
    }
    fclose(f);
    ll_queue_destroy(queue);
}
