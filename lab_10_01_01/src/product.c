#define _GNU_SOURCE

#include "product.h"
#include "exitcodes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int product_read_from_file(FILE *file, product_t **product_pointer)
{
    int rc = OK;

    char *buffer = NULL;
    ssize_t read_symbols_count = 0;
    size_t len = 0;
    double temp_weight = 0, temp_volume = 0;

    if ((read_symbols_count = getline(&buffer, &len, file)) == -1)
    {
        free(buffer);
        rc = STRING_READ_ERROR;
    }

    if (rc == OK)
    {        
        if (fscanf(file, "%lf\n%lf\n", &temp_weight, &temp_volume) != 2)
        {
            rc = NUMBER_READ_ERROR;
        }
        else if (temp_volume <= 0 || temp_weight <= 0)
        {
            rc = INVALID_DATA_ERROR;
        }
        else
        {
            *product_pointer = malloc(sizeof(struct product));
            if (!(*product_pointer))
            {
                rc = MEMORY_ERROR;
            }
            else
            {   
                rc = product_init_content(*product_pointer, buffer, temp_weight, temp_volume);
            }   
        }
    }
    
    if (rc != STRING_READ_ERROR)
    {
        free(buffer);
    }
    
    if (rc == STRING_READ_ERROR && feof(file))
    {
        rc = EOF;
    }

    return rc;
}


int product_init_content(product_t *product_pointer, const char *title, double weight, double volume)
{
    char *temp_string_pointer = strdup(title);

    if (!temp_string_pointer)
    {
        return MEMORY_ERROR;
    }
    else
    {
        product_pointer->name = temp_string_pointer;
        product_pointer->weight = weight;
        product_pointer->volume = volume;
    }
    
    return OK;
}


void product_print_content(void *data)
{
    product_t *product_pointer = data;
    
    printf("%s%lf\n%lf\n", product_pointer->name, product_pointer->weight, product_pointer->volume);
}


void product_free_content(product_t *product_pointer)
{
    if (product_pointer)
    {
        free(product_pointer->name);
        free(product_pointer);
    }
}


int get_products_count(FILE *file, size_t *array_len)
{
    product_t *current_product = NULL;
    size_t current_products_count = 0;
    int rc = OK;

    while ((rc = product_read_from_file(file, &current_product)) == OK)
    {
        current_products_count++;
        product_free_content(current_product);
    }

    if (rc == MEMORY_ERROR)
    {
        product_free_content(current_product);
    }

    if (rc == EOF && current_products_count > 0)
    {
        *array_len = current_products_count;
        rc = OK;
    }
    else if (current_products_count == 0)
    {
        rc = EMPTY_FILE_ERROR;
    }

    return rc;
}


int products_array_memory_alloc(FILE *file, void ***products_array, size_t *array_len)
{
    int rc = OK;

    rc = get_products_count(file, array_len);
    if (rc != OK)
    {
        return rc;
    }

    *products_array = calloc(*array_len, sizeof(product_t *));
    if (!products_array)
    {
        return MEMORY_ERROR;
    }
    else
    {
        return OK;
    }
}


int products_read_to_array(FILE *file, void **products_array, size_t array_len)
{
    int rc = OK;
    product_t *current_product = NULL;

    for (size_t i = 0; i < array_len && rc == OK; i++)
    {
        rc = product_read_from_file(file, &current_product);
        if (rc == OK)
        {
            products_array[i] = current_product;
        }
        else
        {
            free(current_product);
        }
    }

    return rc;
}


void products_array_free(void **products_array, size_t array_len)
{
    if (products_array == NULL)
    {
        return;
    }
    
    for (size_t i = 0; i < array_len; i++)
    {
        product_free_content(products_array[i]);
    }

    free(products_array);
}
