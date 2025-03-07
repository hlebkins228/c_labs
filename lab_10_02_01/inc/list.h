#ifndef LIST_H__

#define LIST_H__

#include <stdio.h>
#include "node.h"

int list_input(node_t **head);
node_t *list_add_tail(node_t *head, node_t *new_node);
void list_print(node_t *head);
void list_free(node_t *head);

#endif
