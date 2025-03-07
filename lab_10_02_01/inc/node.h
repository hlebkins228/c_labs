#ifndef NODE_H__

#define NODE_H__

typedef struct node node_t;
typedef void (*data_print_func)(void *data);

struct node
{
    int power;
    int k;
    node_t *next;
};


node_t *node_create(int power, int k);
void node_print(const node_t *node);
void node_free(node_t *node);

#endif
