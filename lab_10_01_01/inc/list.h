#ifndef LIST_H__

#define LIST_H__

#include <stdio.h>
#include "node.h"

typedef int (*data_read_func)(FILE *file, void *data);
typedef int (*comparator_func)(const void *, const void *);

int list_read_from_array(node_t **head, void **data_array, size_t data_array_len);
node_t *list_add_tail(node_t *head, node_t *new_node);
void list_print(node_t *head, data_print_func data_print);
void list_free(node_t *head);

node_t *find(node_t *head, const void *data, comparator_func cmp);
void *pop_front(node_t **head);
void insert(node_t **head, node_t *elem, node_t *before);
void remove_duplicates(node_t **head, comparator_func cmp);

node_t *sort(node_t *head, comparator_func cmp);
void sorted_insert(node_t **head, node_t *element, comparator_func cmp);
node_t *node_copy(node_t *dst_node);

int data_comparator(const void *data_1, const void *data_2);
int density_comparator(const void *data_1, const void *data_2);

#endif
