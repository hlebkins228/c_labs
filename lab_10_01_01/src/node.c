#include "node.h"
#include "exitcodes.h"

#include <stdlib.h>


node_t *node_create(void *data)
{
    node_t *new_node = malloc(sizeof(struct node));
    if (!new_node)
    {
        return NULL;
    }
    else
    {
        new_node->data = data;
        new_node->next = NULL;
    }

    return new_node;
}


void node_print(const node_t *node, data_print_func data_print)
{
    if (node)
    {
        data_print(node->data);
    }
}


void node_free(node_t *node)
{
    free(node);
}
