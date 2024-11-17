#include "sa_queue.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "simuation.h"
#include "utils.h"

struct sa_queue_
{
    item_t body[MAX_SIZE];
    size_t n;
    item_t *tail;
    item_t *head;
};

sa_queue_t *sa_queue_create(void)
{
    sa_queue_t *queue = calloc(1, sizeof(struct sa_queue_));
    if (!queue)
        return NULL;

    queue->head = queue->body;
    queue->tail = queue->body - 1;

    return queue;
}

void sa_queue_destroy(sa_queue_t *queue)
{
    free(queue);
}

bool sa_queue_is_empty(const sa_queue_t *queue)
{
    return queue->n == 0;
}

bool sa_queue_is_full(const sa_queue_t *queue)
{
    return queue->n == MAX_SIZE;
}

item_t *sa_queue_get_first(const sa_queue_t *queue)
{
    if (sa_queue_is_empty(queue))
        return NULL;
    return queue->head;
}

item_t *sa_queue_get_last(const sa_queue_t *queue)
{    if (sa_queue_is_empty(queue))
    return NULL;
    return queue->tail;
}

return_code sa_queue_enqueue(sa_queue_t *queue, const item_t value)
{
    if (sa_queue_is_full(queue))
        return ERR_FULL;

    queue->tail = queue->tail < queue->body + MAX_SIZE - 1 ? queue->tail + 1 : queue->body;
    *queue->tail = value;
    queue->n++;

    if (SHOW_ADDR)
        printf("Reserved: "ANSI_COLOR_RED"%p"ANSI_COLOR_RESET"\n", queue->tail);

    return OK;
}

return_code sa_queue_dequeue(item_t *val, sa_queue_t *queue)
{
    if (sa_queue_is_empty(queue))
        return ERR_EMPTY;

    if (val)
        *val = *queue->head;
    queue->head = queue->head < queue->body + MAX_SIZE - 1 ? queue->head + 1 : queue->body;
    queue->n--;

    if (SHOW_ADDR)
        printf("Freed: "ANSI_COLOR_GREEN"%p"ANSI_COLOR_RESET"\n", queue->head);

    return OK;
}

void sa_queue_clear(sa_queue_t *queue)
{
    queue->n = 0;
    queue->tail = queue->body;
    queue->head = queue->body;
}

void sa_queue_print(const sa_queue_t *queue, const char *sep, const char *end)
{
    for (int i = queue->n; i >= 0; i--)
        printf(ITEM_FMT "%s", queue->body[i], sep);
    printf("%s", end);
}

size_t sa_queue_sizeof(const sa_queue_t *queue)
{
    return sizeof(struct sa_queue_);
}
