#ifndef SA_QUE_H
#define SA_QUE_H

#include <stdbool.h>

#include "types.h"
#include "return_codes.h"

#define MAX_SIZE 1000

typedef struct sa_queue_ sa_queue_t;

sa_queue_t *sa_queue_create(void);
void        sa_queue_destroy(sa_queue_t *queue);

bool        sa_queue_is_empty(const sa_queue_t *queue);
bool        sa_queue_is_full(const sa_queue_t *queue);
return_code sa_queue_enqueue(sa_queue_t *queue, const item_t value);
return_code sa_queue_dequeue(item_t *val, sa_queue_t *queue);
void        sa_queue_clear(sa_queue_t *queue);
void        sa_queue_print(const sa_queue_t *queue, const char *sep, const char *end);
item_t *    sa_queue_get_first(const sa_queue_t *queue);
item_t *    sa_queue_get_last(const sa_queue_t *queue);
size_t      sa_queue_sizeof(const sa_queue_t *queue);

#endif //SA_QUE_H
