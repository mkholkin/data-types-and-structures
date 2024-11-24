#include "HashMap.h"

#include <math.h>
#include <stdlib.h>

static void HasMap_rehash(HashMap hashMap);
static int getNextPrime(long long num);
static List* createBody(size_t size);

Hash hash(const int key, const int div)
{
    return key % div;
}

HashMap HashMap_create(void)
{
    HashMap hashMap = malloc(sizeof(struct HashMap_));
    if (hashMap)
    {
        hashMap->nItems = 0;
        hashMap->avgCmp = 0;
        hashMap->bodySize = BODY_INIT_SIZE;
        hashMap->hashSecret = getNextPrime(hashMap->bodySize);
        hashMap->body = createBody(BODY_INIT_SIZE);
        if (!hashMap->body)
            HashMap_destroy(&hashMap);
    }
    return hashMap;
}

void HashMap_destroy(HashMap* hashMap)
{
    if ((*hashMap)->body)
    {
        for (int i = 0; i < (*hashMap)->bodySize; i++)
            List_destroy((*hashMap)->body + i);
        free((*hashMap)->body);
    }
    free(*hashMap);
    *hashMap = NULL;
}

ListItem* HashMap_find(HashMap hashMap, ListItem key)
{
    int index = hash(key, hashMap->hashSecret) % hashMap->bodySize;

    for (Node node = hashMap->body[index]->head; node; node = node->next)
        if (node->val == key)
            return &node->val;

    return NULL;
}

void HashMap_insert(HashMap hashMap, ListItem key)
{
    int index = hash(key, hashMap->hashSecret) % hashMap->bodySize;
    List list = hashMap->body[index];

    size_t listLen = 1; // +1 because of new (inserted) node
    for (Node node = list->head; node; node = node->next)
    {
        listLen++;
        if (node->val == key)
            return;
    }

    // Adjsut comparisons per key
    List_addTail(list, key);
    hashMap->avgCmp = (hashMap->avgCmp * hashMap->nItems + listLen) / (hashMap->nItems + 1);
    hashMap->nItems++;

    // Rehash
    if (hashMap->avgCmp > MAX_AVG_CMP)
        HasMap_rehash(hashMap);
}

void HashMap_remove(HashMap hashMap, ListItem key)
{
    int index = hash(key, hashMap->hashSecret) % hashMap->bodySize;
    List_remove(hashMap->body[index], key);
}

static void HasMap_rehash(HashMap hashMap)
{
    size_t newBodySize = hashMap->bodySize * BODY_INC_STEP;
    int newHashSecret = getNextPrime(newBodySize);
    List* newBody = createBody(newBodySize);

    // Rehash all keys from old body
    size_t comparisons = 0;
    for (int i = 0; i < hashMap->bodySize; i++)
    {
        List list = hashMap->body[i];
        while (!List_isEmpty(list))
        {
            Node node = NULL;
            List_NodePopHead(list, &node);

            int index = hash(node->val, newHashSecret) % newBodySize;
            List newList = newBody[index];
            List_NodeAddTail(newList, node);
            comparisons += List_length(newList);
        }
    }

    // Set new body for hasMap
    free(hashMap->body);
    hashMap->body = newBody;
    hashMap->bodySize = newBodySize;
    hashMap->avgCmp = (double)hashMap->nItems / comparisons;
    hashMap->hashSecret = newHashSecret;
}

int getNextPrime(long long num)
{
    bool isPrime;
    do
    {
        isPrime = true;
        num++;
        for (int i = 2; i < sqrt(num) + 1; i++)
            if (num % i == 0)
            {
                isPrime = false;
                break;
            }
    }
    while (!isPrime);

    return num;
}

static List* createBody(const size_t size)
{
    List* body = calloc(size, sizeof(List));
    if (!body)
        return NULL;

    for (int i = 0; i < size; i++)
    {
        body[i] = List_create();
        if (!body[i])
            goto destroy;
    }

    return body;

destroy:
    for (int i = 0; i < size; i++)
        List_destroy(&body[i]);
    free(body);
    return NULL;
}
