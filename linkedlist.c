#include <stdlib.h>
#include <string.h>

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