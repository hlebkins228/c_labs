#include "list.h"
#include "exitcodes.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NEXT_STRING 100


int list_input(node_t **head)
{
    int rc = OK;

    node_t *new_list = NULL;
    node_t *new_node = NULL;
    int temp_k = 0;
    int temp_power = 0;
    char next_symbol = '\0';
    int readed_entities_count = 0;

    while (rc == OK && (readed_entities_count = scanf("%d%d%c", &temp_k, &temp_power, &next_symbol)) == 3)
    {
        if (next_symbol == ' ' || next_symbol == '\n')
        {
            new_node = node_create(temp_power, temp_k);
            if (!new_node)
            {
                rc = NODE_CREATE_ERROR;
            }
            else
            {
                new_list = list_add_tail(new_list, new_node);
            }
        }

        if (rc == OK)
        {
            if (next_symbol == ' ')
            {
                rc = OK;
            }
            else
            {
                rc = NEXT_STRING;
            }
        }
        else
        {
            rc = INVALID_INPUT_ERROR;
        }
    }

    if (readed_entities_count != 3)
    {
        rc = INVALID_INPUT_ERROR;
    }

    if (rc == NEXT_STRING)
    {
        rc = OK;
    }

    if (rc != OK)
    {
        list_free(new_list);
    }
    else
    {
        *head = new_list;
    }

    return rc;
}


node_t *list_add_tail(node_t *head, node_t *new_node)
{
    if (head == NULL)
    {
        return new_node;
    }
    else
    {
        node_t *current_node = head;
        for (; current_node->next != NULL; current_node = current_node->next);
        current_node->next = new_node;
        
        return head;
    }
}


void list_print(node_t *head)
{
    for (node_t *current_node = head; current_node != NULL; current_node = current_node->next)
    {
        if (current_node->k != 0)
        {
            node_print(current_node);
            printf(" ");
        }
    }
    printf("L\n");
}


void list_free(node_t *head)
{
    node_t *next_node = NULL;

    for (node_t *current_node = head; current_node != NULL;)
    {
        next_node = current_node->next;
        node_free(current_node);
        current_node = next_node;
    }
}
