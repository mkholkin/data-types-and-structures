#include "list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "simuation.h"
#include "utils.h"

struct list_node
{
    item_t val;
    struct list_node *next;
};

typedef struct list_node list_node;

list_node *list_node_create(const item_t val, list_node *next)
{
    list_node *node = calloc(1, sizeof(list_node));

    if (SHOW_ADDR)
        printf("Reserved: "ANSI_COLOR_RED"%p"ANSI_COLOR_RESET"\n", node);

    if (node)
    {
        node->val = val;
        node->next = next;
    }

    return node;
}

void list_node_destroy(list_node *node)
{
    if (SHOW_ADDR)
        printf("Freed: "ANSI_COLOR_GREEN"%p"ANSI_COLOR_RESET"\n", node);

    free(node);
}

// -------- list ---------

struct list_
{
    list_node *head; // least recent added emlement
    list_node *tail; // most recent added element
};

list_t *list_create(void)
{
    return calloc(1, sizeof(list_t));
}

void list_destroy(list_t *list)
{
    while (!list_is_empty(list))
        list_remove_head(list);
}

bool list_is_empty(const list_t *list)
{
    return list->head == NULL && list->tail == NULL;
}

return_code list_add_tail(list_t *list, item_t value)
{
    assert(list);

    list_node *node = list_node_create(value, NULL);
    if (!node)
        return ERR_MEM;

    if (list_is_empty(list))
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    return OK;
}

return_code list_remove_head(list_t *list)
{
    assert(list);
    if (list_is_empty(list))
        return ERR_EMPTY;

    if (list->head == list->tail)
    {
        list_node_destroy(list->head);
        list->head = NULL;
        list->tail = NULL;
        return OK;
    }

    list_node *old_head = list->head;
    list->head = list->head->next;

    list_node_destroy(old_head);

    return OK;
}

item_t *list_get_head(const list_t *list)
{
    if (list_is_empty(list))
        return NULL;

    return &list->head->val;
}

item_t *list_get_tail(const list_t *list)
{
    if (list_is_empty(list))
        return NULL;

    return &list->tail->val;
}

void list_clear(list_t *list)
{
    while (!list_is_empty(list))
        list_remove_head(list);
}

void list_print(const list_t *list, const char *sep, const char *end)
{
    for (const list_node *cursor = list->tail; cursor; cursor = cursor->next)
        printf(ITEM_FMT "%s", cursor->val, sep);
    printf("%s", end);
}

size_t list_sizeof(const list_t *list)
{
    size_t nodes_size = 0;
    for (list_node *curr = list->head;  curr; curr = curr->next)
    {
        nodes_size += sizeof(*curr);
    }
    return sizeof(struct list_) + nodes_size;
}
