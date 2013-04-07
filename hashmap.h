#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "linkedlist.h"

#define HASHMAP_DEFAULT_SLOTS 31

// Struct
typedef struct hashmap_t {
    // Number of slots in array
    int slots;

    // Array of linked lists
    node **array;
} hashmap;

// Functions
hashmap *hashmap_create(int slots);

void hashmap_put(hashmap *hm, char *key, int value);

int hashmap_get(hashmap *hm, char *key);

// Persistence functions
int hashmap_dump(hashmap *hm, const char *filename);

hashmap *hashmap_read(const char *filename, int slots);

// Helper functions
static int get_slot(char *key, int slots);

#endif
