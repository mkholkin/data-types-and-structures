#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef enum
{
    LIST_OK,
    LIST_MEM,
    LIST_EMPTY,
    LIST_FULL,
} ListRC;

typedef int ListItem;
#define LIST_ITEM_FMT "%d"

typedef struct Node_ *Node;
typedef struct List_ *List;

struct Node_
{
    ListItem val;
    struct Node_ *next;
};

struct List_
{
    Node head; // least recent added emlement
    Node tail; // most recent added element
};


List        List_create(void);
void        List_destroy(List *list);

bool        List_isEmpty(const List list);
ListRC      List_addHead(List list, ListItem value);
ListRC      List_addTail(List list, ListItem value);
ListRC      List_NodeAddTail(List list, Node node);
ListRC      List_removeHead(List list);
ListRC      List_remove(List list, ListItem value);
ListRC      List_NodePopHead(List list, Node *node);
ListItem*   List_getHead(const List list);
ListItem*   List_getTail(const List list);
void        List_clear(List list);
void        List_print(const List list, const char *sep, const char *end);
size_t      List_length(const List list);
size_t      List_sizeof(const List list);

#endif //LIST_H
