#ifndef LL_QUEUE_H
#define LL_QUEUE_H

#include <stdbool.h>

#include "return_codes.h"
#include "types.h"

typedef struct ll_queue_ ll_queue_t;

ll_queue_t *ll_queue_create(void);
void        ll_queue_destroy(ll_queue_t *queue);

bool        ll_queue_is_empty(const ll_queue_t *queue);
bool        ll_queue_is_full(const ll_queue_t *queue);
return_code ll_queue_enqueue(ll_queue_t *queue, const item_t value);
return_code ll_queue_dequeue(item_t *val, ll_queue_t *queue);
void        ll_queue_clear(ll_queue_t *queue);
void        ll_queue_print(const ll_queue_t *queue, const char *sep, const char *end);
item_t *    ll_queue_get_first(const ll_queue_t *queue);
item_t *    ll_queue_get_last(const ll_queue_t *queue);
size_t      ll_queue_sizeof(const ll_queue_t *queue);

#endif //LL_QUEUE_H
