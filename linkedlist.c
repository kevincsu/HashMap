#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linkedlist.h"

char *strdup(const char *s);

node *linkedlist_create(const char *key, int value) {
    node *new_node = malloc(sizeof(node));

    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

node *linkedlist_add(node *list, const char *key, int value) {
    node *new_node = malloc(sizeof(node));

    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = list;

    return new_node;
}

node *linkedlist_add_to_tail(node *list, const char *key, int value) {
    node *new_node = malloc(sizeof(node));

    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = NULL;    

    if (list == NULL) {
        return new_node;
    }

    node *cur_node = list;
    while (cur_node->next != NULL) {
        cur_node = cur_node->next;
    }

    cur_node->next = new_node;

    return list;
}

void linkedlist_destroy(node *list) {
    node *cur = list;
    node *next = cur->next;

    while (cur != NULL) {
        next = cur->next;
        free(cur->key);
        free(cur);
        cur = next;
    }
}

int linkedlist_dump(node *list, const char *filename) {
    truncate(filename, 0);

    // Open file for writing
    FILE * file = fopen(filename, "w+");
    if (file == NULL) {
        printf("Could not open %s\n", filename);
        return -1;
    }

    // Write every entry into file
    node *cur_node = list; 
    while (cur_node != NULL) {
        fprintf(file, "%s\n", cur_node->key);
        fprintf(file, "%d\n", cur_node->value);

        cur_node = cur_node->next;
    }

    fclose(file);
    return 0;
}


node *linkedlist_read(const char *filename) {
    node *list = NULL;

    FILE *file = fopen(filename, "r");

    // TODO variable length buffer
    char key[4096];
    int value;

    while ((fscanf(file, "%s\n", key) > 0)
            && (fscanf(file, "%d\n", &value) > 0)) {
        list = linkedlist_add_to_tail(list, key, value);
    }

    return list;
}
