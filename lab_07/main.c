#include <stdio.h>

#include "HashMap.h"

int main(void)
{
    HashMap hashMap = HashMap_create();
    HashMap_insert(hashMap, 10);
    HashMap_insert(hashMap, 17);
    HashMap_insert(hashMap, 22);
    HashMap_insert(hashMap, 34);
    HashMap_insert(hashMap, 51);
    HashMap_insert(hashMap, 68);
    HashMap_insert(hashMap, 17 * 5);
    HashMap_insert(hashMap, 17 * 6);
    HashMap_insert(hashMap, 17 * 7);

    printf("%d\n", *HashMap_find(hashMap, 10));
    printf("%d\n", *HashMap_find(hashMap, 17));
    printf("%d\n", *HashMap_find(hashMap, 22));
    printf("%d\n", *HashMap_find(hashMap, 34));
    printf("%d\n", *HashMap_find(hashMap, 51));
    printf("%d\n", *HashMap_find(hashMap, 17 * 4));
    printf("%d\n", *HashMap_find(hashMap, 17 * 5));
    printf("%d\n", *HashMap_find(hashMap, 17 * 6));
    printf("%d\n", *HashMap_find(hashMap, 17 * 7));
}
