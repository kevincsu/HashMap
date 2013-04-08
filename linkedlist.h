#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

typedef struct node_t {
    char *key;
    int value;
    struct node_t *next;
} node;

node *linkedlist_create(const char *key, int value);

node *linkedlist_add(node *list, const char *key, int value);

node *linkedlist_add_to_tail(node *list, const char *key, int value);

void linkedlist_destroy(node *list);

#endif
