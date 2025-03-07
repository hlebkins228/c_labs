#include "node.h"
#include "exitcodes.h"

#include <stdlib.h>
#include <stdio.h>


node_t *node_create(int power, int k)
{
    node_t *new_node = malloc(sizeof(struct node));
    if (!new_node)
    {
        return NULL;
    }
    else
    {
        new_node->power = power;
        new_node->k = k;
        new_node->next = NULL;
    }

    return new_node;
}


void node_print(const node_t *node)
{
    if (node)
    {
        printf("%d %d", node->k, node->power);
    }
}


void node_free(node_t *node)
{
    free(node);
}
