#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hashmap.h"

hashmap *hashmap_create(int slots) {
    hashmap *hm = malloc(sizeof(hashmap));

    hm->slots = slots;
    hm->array = malloc(slots * sizeof(node *));
    int i;
    for (i = 0; i < slots; i++) {
        hm->array[i] = NULL;
    }

    return hm;
}

void hashmap_put(hashmap *hm, char *key, int value) {
    int slot = get_slot(key, hm->slots);

    node *cur_node = hm->array[slot];
    if (cur_node == NULL) {
        hm->array[slot] = linkedlist_create(key, value);
        return;
    }

    // Look for it
    while (cur_node != NULL) {
        if (strcmp(cur_node->key, key) == 0) {
            // Found it
            cur_node->value = value;
            return;
        }

        cur_node = cur_node->next;
    }

    // Did not find it, add it in
    hm->array[slot] = linkedlist_add(hm->array[slot], key, value);
}

int hashmap_get(hashmap *hm, char *key) {
    int slot = get_slot(key, hm->slots);
    int value = 0;

    node *cur_node = hm->array[slot];

    // Look for it
    while (cur_node != NULL) {
        if (strcmp(cur_node->key, key) == 0) {
            value = cur_node->value;
        }

        cur_node = cur_node->next;
    }

    return value;
}

int hashmap_dump(hashmap *hm, const char *filename) {
    // Delete the file if it exists
    unlink(filename);

    // Open file for writing
    FILE * file = fopen(filename, "w+");
    if (file == NULL) {
        printf("Could not open %s\n", filename);
        return -1;
    }

    // Write every entry into file
    int i;
    for (i = 0; i < hm->slots; i++) {
        node *cur_node = hm->array[i];

        while (cur_node != NULL) {
            fprintf(file, "%s\n", cur_node->key);
            fprintf(file, "%d\n", cur_node->value);

            cur_node = cur_node->next;
        }
    }

    fclose(file);
    return 0;
}

hashmap *hashmap_read(const char *filename, int slots) {
    hashmap *hm = hashmap_create(slots);

    FILE *file = fopen(filename, "r");

    // TODO variable length buffer
    char key[4096];
    int value;

    while ((fscanf(file, "%s\n", key) > 0)
            && (fscanf(file, "%d\n", &value) > 0)) {
        hashmap_put(hm, key, value);
    }

    return hm;
}

int get_slot(char *key, int slots) {
    unsigned int i;
    int total = 0;

    for (i = 0; i < strlen(key); i++) {
        total += key[i];
    }

    int slot = total % slots;
    if (slot < 0) {
        slot += slots;
    }

    return slot;
}
