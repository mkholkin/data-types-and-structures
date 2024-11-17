#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

#include "types.h"
#include "return_codes.h"

typedef struct list_ list_t;

list_t *list_create(void);
void    list_destroy(list_t *list);

bool        list_is_empty(const list_t *list);
return_code list_add_head(list_t *list, item_t value);
return_code list_add_tail(list_t *list, item_t value);
return_code list_remove_head(list_t *list);
item_t *    list_get_head(const list_t *list);
item_t *    list_get_tail(const list_t *list);
void        list_clear(list_t *list);
void        list_print(const list_t *list, const char *sep, const char *end);
size_t      list_sizeof(const list_t *list);

#endif //LIST_H
