#include "ll_queue.h"

#include <stdlib.h>

#include "list.h"

struct ll_queue_
{
    list_t *body;
};

ll_queue_t *ll_queue_create(void)
{
    ll_queue_t *queue = calloc(1, sizeof(struct ll_queue_));
    if (!queue)
        return NULL;

    queue->body = list_create();
    if (!queue->body)
    {
        ll_queue_destroy(queue);
        return NULL;
    }

    return queue;
}

void ll_queue_destroy(ll_queue_t *queue)
{
    list_destroy(queue->body);
    free(queue);
}

bool ll_queue_is_empty(const ll_queue_t *queue)
{
    return list_is_empty(queue->body);
}

bool ll_queue_is_full(const ll_queue_t *queue)
{
    return false;
}

return_code ll_queue_enqueue(ll_queue_t *queue, const item_t value)
{
    return list_add_tail(queue->body, value);
}

return_code ll_queue_dequeue(item_t *val, ll_queue_t *queue)
{
    if (val)
        *val = *list_get_head(queue->body);
    const return_code rc = list_remove_head(queue->body);

    return rc;
}

void ll_queue_clear(ll_queue_t *queue)
{
    list_clear(queue->body);
}

item_t *ll_queue_get_first(const ll_queue_t *queue)
// get first element to dequeue
{
    return list_get_head(queue->body);
}

item_t *ll_queue_get_last(const ll_queue_t *queue)
// get last element to dequeue
{
    return list_get_tail(queue->body);
}

void ll_queue_print(const ll_queue_t *queue, const char *sep, const char *end)
{
    list_print(queue->body, sep, end);
}

size_t ll_queue_sizeof(const ll_queue_t *queue)
{
    return sizeof(struct ll_queue_) + list_sizeof(queue->body);
}