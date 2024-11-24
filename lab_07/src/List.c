#include "list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Node Node_create(const ListItem val, Node next)
{
    Node node = calloc(1, sizeof(Node));

    if (node)
    {
        node->val = val;
        node->next = next;
    }

    return node;
}

void Node_destroy(Node node)
{
    free(node);
}

// -------- list ---------

List List_create(void)
{
    return calloc(1, sizeof(List));
}

void List_destroy(List* list)
{
    while (!List_isEmpty(*list))
        List_removeHead(*list);
    free(*list);
    *list = NULL;
}

bool List_isEmpty(const List list)
{
    return list->head == NULL && list->tail == NULL;
}

ListRC List_addTail(List list, ListItem value)
{
    assert(list);

    Node node = Node_create(value, NULL);
    if (!node)
        return LIST_MEM;

    return List_NodeAddTail(list, node);
}

ListRC List_NodeAddTail(List list, Node node)
{
    assert(list);
    if (List_isEmpty(list))
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    return LIST_OK;
}

ListRC List_removeHead(List list)
{
    assert(list);

    Node old_head = NULL;
    ListRC rc = List_NodePopHead(list, &old_head);
    Node_destroy(old_head);

    return rc;
}

ListRC List_remove(List list, ListItem value)
{
    assert(list);
    if (List_isEmpty(list))
        return LIST_EMPTY;

    if (list->head->val == value)
        return List_removeHead(list);

    Node remove = NULL;
    for (Node node = list->head; node->next; node = node->next)
        if (node->next->val == value)
        {
            remove = node->next;
            if (remove == list->tail)
                list->tail = node;
            node->next = node->next->next;
            break;
        }

    Node_destroy(remove);
    return LIST_OK;
}

ListRC List_NodePopHead(List list, Node* node)
{
    assert(list);
    if (List_isEmpty(list))
        return LIST_EMPTY;

    if (list->head == list->tail)
    {
        *node = list->head;
        list->head = NULL;
        list->tail = NULL;
        return LIST_OK;
    }

    *node = list->head;
    list->head = list->head->next;
    return LIST_OK;
}

ListItem* List_getHead(const List list)
{
    if (List_isEmpty(list))
        return NULL;

    return &list->head->val;
}

ListItem* List_getTail(const List list)
{
    if (List_isEmpty(list))
        return NULL;

    return &list->tail->val;
}

void List_clear(List list)
{
    while (!List_isEmpty(list))
        List_removeHead(list);
}

void List_print(const List list, const char* sep, const char* end)
{
    for (Node cursor = list->tail; cursor; cursor = cursor->next)
        printf(LIST_ITEM_FMT "%s", cursor->val, sep);
    printf("%s", end);
}

size_t List_length(const List list)
{
    size_t nodes_count = 0;
    for (Node curr = list->head; curr; curr = curr->next)
        nodes_count++;
    return nodes_count;
}

size_t List_sizeof(const List list)
{
    const size_t nodes_count = List_length(list);
    return sizeof(struct List_) + nodes_count * sizeof(struct Node_);
}
