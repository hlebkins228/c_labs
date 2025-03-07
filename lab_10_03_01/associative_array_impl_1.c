#define _GNU_SOURCE

#include "associative_array.h"

#include <stdlib.h>
#include <string.h>

#define MAX_ASSOC_ARRAY_SIZE    64

struct assoc_array_type
{
    char **key;
    int *value;
    int array_length;
    int max_size;
};


assoc_array_t assoc_array_create(void)
{
    assoc_array_t new_dict = malloc(sizeof(struct assoc_array_type));

    if (!new_dict)
    {
        return NULL;
    }

    new_dict->key = calloc(MAX_ASSOC_ARRAY_SIZE, sizeof(char *));
    if (!new_dict->key)
    {
        free(new_dict);
        
        return NULL;
    }

    new_dict->value = calloc(MAX_ASSOC_ARRAY_SIZE, sizeof(int));
    if (!new_dict->value)
    {
        free(new_dict->key);
        free(new_dict);
        
        return NULL;
    }

    new_dict->array_length = 0;
    new_dict->max_size = MAX_ASSOC_ARRAY_SIZE;

    return new_dict;
}


assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{   
    if (arr == NULL || key == NULL || strlen(key) == 0)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }
    
    for (int i = 0; i < arr->array_length; i++)
    {
        if (strcmp(arr->key[i], key) == 0)
        {
            return ASSOC_ARRAY_KEY_EXISTS;       
        }
    }
    
    if (arr->array_length >= arr->max_size)
    {
        void *new_key_array;
        void *new_value_array;

        new_key_array = realloc(arr->key, sizeof(char *) * arr->max_size * 2); 
        if (!new_key_array)
        {
            return ASSOC_ARRAY_MEM;
        }
        
        new_value_array = realloc(arr->value, sizeof(int) * arr->max_size * 2);
        if (!new_key_array)
        {
            free(new_key_array);
            
            return ASSOC_ARRAY_MEM;
        }

        arr->key = new_key_array;
        arr->value = new_value_array;
        arr->max_size *= 2;
    }

    char *new_key = strdup(key);
    if (!new_key)
    {
        return ASSOC_ARRAY_MEM;
    }

    (arr->key)[arr->array_length] = new_key;
    (arr->value)[arr->array_length] = num;
    (arr->array_length)++;

    return ASSOC_ARRAY_OK;
}


void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL || *arr == NULL)
    {
        return;
    }
    
    for (int i = 0; i < (*arr)->array_length; i++)
    {
        if (((*arr)->key)[i])
        {
            free(((*arr)->key)[i]);
        }
    }

    free((*arr)->key);
    free((*arr)->value);
    free(*arr);

    *arr = NULL;
}


assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (arr == NULL || num == NULL || key == NULL || strlen(key) == 0)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    for (int i = 0; i < arr->array_length; i++)
    {
        if (strcmp(arr->key[i], key) == 0)
        {
            *num = arr->value + i; 

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
    
    int has_found = 0; 
    
    for (int i = 0; i < arr->array_length && !has_found; i++)
    {
        if (strcmp(arr->key[i], key) == 0)
        {
            has_found = 1;
            free(arr->key[i]);
            
            for (int j = i; j < arr->array_length - 1; j++)
            {
                arr->key[j] = arr->key[j + 1];
                arr->value[j] = arr->value[j + 1];
            }
        }
    }
    
    if (!has_found)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }
    else
    {
        (arr->array_length)--;

        return ASSOC_ARRAY_OK;
    }
}


assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    for (int i = 0; i < arr->array_length; i++)
    {
        free(arr->key[i]);
        arr->key[i] = NULL;
        arr->value[i] = 0;
    }

    arr->array_length = 0;

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || action == NULL)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    for (int i = 0; i < arr->array_length; i++)
    {
        action(arr->key[i], arr->value + i, param);
    }

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    if (arr->array_length <= 0)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }
    
    char *min_key = arr->key[0];
    int *min_key_value = arr->value + 0;

    for (int i = 1; i < arr->array_length; i++)
    {        
        if (strcmp(min_key, arr->key[i]) > 0)
        {
            min_key = arr->key[i];
            min_key_value = arr->value + i;
        }
    }

    *num = min_key_value;

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    if (arr->array_length <= 0)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }
    
    char *max_key = arr->key[0];
    int *max_key_value = arr->value + 0;

    for (int i = 1; i < arr->array_length; i++)
    {
        if (strcmp(max_key, arr->key[i]) < 0)
        {
            max_key = arr->key[i];
            max_key_value = arr->value + i;
        }
    }

    *num = max_key_value;

    return ASSOC_ARRAY_OK;
}