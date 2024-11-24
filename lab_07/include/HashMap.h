#ifndef HASHMAP_H
#define HASHMAP_H

#include "list.h"

#define BODY_INIT_SIZE 16
#define BODY_INC_STEP 2

#define MAX_AVG_CMP 3

typedef struct HashMap_
{
    List *body; // array of Lists
    size_t bodySize;
    size_t nItems;
    double avgCmp;
    int hashSecret;
} *HashMap;

typedef size_t Hash;

Hash hash(int key, int div);

HashMap    HashMap_create(void);
void       HashMap_destroy(HashMap *hashMap);

ListItem*  HashMap_find(HashMap hashMap, ListItem key);
void       HashMap_insert(HashMap hashMap, ListItem key);
void       HashMap_remove(HashMap hashMap, ListItem key);

#endif //HASHMAP_H
