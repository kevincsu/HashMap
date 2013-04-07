#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

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
