#define _GNU_SOURCE

#include "associative_array.h"

#include <stdlib.h>
#include <string.h>

struct assoc_array_type
{
    char *key;
    int value;
    assoc_array_t next;
};

static void node_free(assoc_array_t node);


assoc_array_t assoc_array_create(void)
{
    assoc_array_t new_dict = malloc(sizeof(struct assoc_array_type));
    if (!new_dict)
    {
        return NULL;
    }

    new_dict->key = NULL;
    new_dict->value = 0;
    new_dict->next = NULL;

    return new_dict;
}


void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL || *arr == NULL)
    {
        return;
    }
    
    assoc_array_t next_node = NULL;
    for (assoc_array_t current_node = *arr; current_node != NULL;)
    {
        next_node = current_node->next;
        node_free(current_node);
        current_node = next_node;
    } 

    *arr = NULL;
}


assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    assoc_array_t last_node = arr;
    for (assoc_array_t current_node = arr; current_node != NULL; current_node = current_node->next)
    {
        if (current_node->key && (strcmp(current_node->key, key) == 0))
        {
            return ASSOC_ARRAY_KEY_EXISTS;
        }

        last_node = current_node;
    }
    
    assoc_array_t new_node = assoc_array_create();
    if (!new_node)
    {
        return ASSOC_ARRAY_MEM;
    }

    new_node->key = strdup(key);
    if (!new_node->key)
    {
        return ASSOC_ARRAY_MEM;
    }

    new_node->value = num;

    last_node->next = new_node;

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (arr == NULL || key == NULL || num == NULL || strlen(key) == 0)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    for (assoc_array_t current_node = arr->next; current_node != NULL; current_node = current_node->next)
    {
        if (strcmp(current_node->key, key) == 0)
        {
            *num = &(current_node->value);

            return ASSOC_ARRAY_OK;
        }
    }

    return ASSOC_ARRAY_NOT_FOUND;
}


assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    assoc_array_t previous_node = arr;
    for (assoc_array_t current_node = arr->next; current_node != NULL; current_node = current_node->next)
    {
        if (strcmp(current_node->key, key) == 0)
        {
            previous_node->next = current_node->next;
            node_free(current_node);

            return ASSOC_ARRAY_OK;
        }

        previous_node = current_node;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}


assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    assoc_array_t next_node = NULL;

    for (assoc_array_t current_node = arr->next; current_node != NULL;)
    {
        next_node = current_node->next;
        node_free(current_node);
        current_node = next_node;
    }

    arr->next = NULL;

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || action == NULL)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    for (assoc_array_t current_node = arr->next; current_node != NULL; current_node = current_node->next)
    {
        action(current_node->key, &(current_node->value), param);
    }

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    if (arr->next == NULL)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }

    char *min_key = (arr->next)->key;
    int *min_key_value_pointer = &((arr->next)->value);

    for (assoc_array_t current_node = arr->next; current_node != NULL; current_node = current_node->next)
    {   
        if (strcmp(min_key, current_node->key) > 0)
        {
            min_key = current_node->key;
            min_key_value_pointer = &(current_node->value);
        }
    }

    *num = min_key_value_pointer;
        
    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    if (arr->next == NULL)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }

    char *max_key = (arr->next)->key;
    int *max_key_value_pointer = &((arr->next)->value);

    for (assoc_array_t current_node = arr->next; current_node != NULL; current_node = current_node->next)
    {   
        if (strcmp(max_key, current_node->key) < 0)
        {
            max_key = current_node->key;
            max_key_value_pointer = &(current_node->value);
        }
    }

    *num = max_key_value_pointer;
        
    return ASSOC_ARRAY_OK;
}


static void node_free(assoc_array_t node)
{
    if (node)
    {
        free(node->key);
        free(node);   
    }
}