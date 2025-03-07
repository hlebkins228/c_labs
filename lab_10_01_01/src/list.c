#include "list.h"
#include "product.h"
#include "exitcodes.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPS 1e-7

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


void list_print(node_t *head, data_print_func data_print)
{
    for (node_t *current_node = head; current_node != NULL; current_node = current_node->next)
    {
        node_print(current_node, data_print);
    }
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


int list_read_from_array(node_t **head, void **data_array, size_t data_array_len)
{
    int rc = OK;
    node_t *new_node = NULL;

    for (size_t i = 0; i < data_array_len && rc == OK; i++)
    {
        new_node = node_create(data_array[i]);
        if (!new_node)
        {
            list_free(*head);
            rc = NODE_CREATE_ERROR;
        }
        else
        {
            *head = list_add_tail(*head, new_node);
        }
    }

    return rc;
}


node_t *find(node_t *head, const void *data, comparator_func cmp)
{
    if (head == NULL || data == NULL || cmp == NULL)
    {
        return NULL;
    }

    for (node_t *current_node = head; current_node != NULL; current_node = current_node->next)
    {
        if (cmp(current_node->data, data) == 0)
        {
            return current_node;
        }
    }

    return NULL;
}


void *pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
    {
        return NULL;
    }
    
    node_t *old_head = *head;
    void *head_data = (*head)->data;

    *head = (*head)->next;
    node_free(old_head);

    return head_data;
}


void insert(node_t **head, node_t *elem, node_t *before)
{
    if (head == NULL || *head == NULL || elem == NULL || before == NULL)
    {
        return;
    }

    if (*head == before)
    {
        elem->next = *head;
        *head = elem;

        return;
    }

    node_t *previous_node = *head;

    for (node_t *current_node = (*head)->next; current_node != NULL; current_node = current_node->next)
    {
        if (current_node == before)
        {
            previous_node->next = elem;
            elem->next = current_node;
        }

        previous_node = current_node;
    }
}


void remove_duplicates(node_t **head, comparator_func cmp)
{
    if (head == NULL || *head == NULL || cmp == NULL)
    {
        return;
    }
    
    for (node_t *current_node = *head; current_node != NULL; current_node = current_node->next)
    {
        node_t *previous_node = current_node; 

        for (node_t *node_for_compare = current_node->next; node_for_compare != NULL;)
        {
            if (cmp(current_node->data, node_for_compare->data) == 0)
            {
                previous_node->next = node_for_compare->next;
                node_free(node_for_compare);
                node_for_compare = previous_node->next;
            }
            else
            {
                previous_node = node_for_compare;
                node_for_compare = node_for_compare->next;
            }
        }
    }
}


node_t *sort(node_t *head, comparator_func cmp)
{
    if (head == NULL || cmp == NULL)
    {
        return NULL;
    }

    node_t *sorted_list_head = NULL;
    node_t *new_node = NULL;
    
    for (node_t *current_node = head; current_node != NULL; current_node = current_node->next)
    {
        new_node = node_copy(current_node);
        if (!new_node)
        {
            list_free(sorted_list_head);
            return NULL;
        }
        sorted_insert(&sorted_list_head, new_node, cmp);
    }

    return sorted_list_head;
}


void sorted_insert(node_t **head, node_t *element, comparator_func cmp)
{
    if (head == NULL || element == NULL || cmp == NULL)
    {
        return;
    }

    if (*head == NULL)
    {
        *head = element;
    }
    else
    {
        node_t *previous_node = NULL;
        int is_inserted = 0;

        for (node_t *current_node = *head; current_node != NULL && !is_inserted; current_node = current_node->next)
        {
            if (cmp(current_node->data, element->data) > 0)
            {
                if (current_node == *head)
                {
                    element->next = *head;
                    *head = element;
                }
                else
                {
                    previous_node->next = element;
                    element->next = current_node;
                }

                is_inserted = 1;
            }
            
            previous_node = current_node;
        }

        if (!is_inserted)
        {
            previous_node->next = element;
        }
    }
}


node_t *node_copy(node_t *dst_node)
{
    node_t *new_node = node_create(dst_node->data);
    if (!new_node)
    {
        return NULL;
    }
    else
    {
        return new_node;
    }
}


int data_comparator(const void *data_1, const void *data_2)
{
    const product_t *product_1 = data_1;
    const product_t *product_2 = data_2;

    if (strcmp(product_1->name, product_2->name) == 0)
    {
        if ((fabs(product_1->volume - product_1->volume) < EPS) && (fabs(product_1->weight - product_2->weight) < EPS))
        {
            return 1;
        }
    }

    return 0;
}


int density_comparator(const void *data_1, const void *data_2)
{
    const product_t *product_1 = data_1;
    const product_t *product_2 = data_2;
    
    return (product_1->weight / product_1->volume > product_2->weight / product_2->volume);
}
