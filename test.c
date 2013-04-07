#include <stdio.h>

#include "linkedlist.h"
#include "hashmap.h"

int main() {
    hashmap *hm = hashmap_create(HASHMAP_DEFAULT_SLOTS);

    printf("%d\n", hashmap_get(hm, "hello"));
    hashmap_put(hm, "hello", 1);
    printf("%d\n", hashmap_get(hm, "hello"));
    hashmap_put(hm, "hello", 2);
    printf("%d\n", hashmap_get(hm, "hello"));

    printf("%d\n", hashmap_get(hm, "world"));
    hashmap_put(hm, "world", 3);
    printf("%d\n", hashmap_get(hm, "world"));
    hashmap_put(hm, "world", 4);
    printf("%d\n", hashmap_get(hm, "world"));

    hashmap_dump(hm, "./mapbackup");

    hashmap *hm2 = hashmap_read("./mapbackup", HASHMAP_DEFAULT_SLOTS);

    printf("%d\n", hashmap_get(hm2, "hello"));
    printf("%d\n", hashmap_get(hm2, "world"));

    hashmap_dump(hm2, "./mapbackup2");
    return 0;
}
