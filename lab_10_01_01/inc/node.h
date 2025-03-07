#ifndef NODE_H__

#define NODE_H__

typedef struct node node_t;
typedef void (*data_print_func)(void *data);

struct node
{
    void *data;
    node_t *next;
};


node_t *node_create(void *data);
void node_print(const node_t *node, data_print_func data_print);
void node_free(node_t *node);

#endif
