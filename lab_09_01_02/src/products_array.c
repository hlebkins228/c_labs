#include "products_array.h"
#include "exitcodes.h"

#include <stdlib.h>
#include <string.h>

int get_products_count(FILE *file, size_t *array_len)
{
    struct product_t current_product = { NULL, 0, 0 };
    size_t current_products_count = 0;
    int rc = OK;

    while ((rc = product_read_from_file(file, &current_product)) == OK)
    {
        current_products_count++;
        product_free_content(&current_product);
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


int products_array_memory_alloc(FILE *file, struct product_t **products_array, size_t *array_len)
{
    int rc = OK;

    rc = get_products_count(file, array_len);
    if (rc != OK)
    {
        return rc;
    }

    *products_array = calloc(*array_len, sizeof(struct product_t));
    if (!products_array)
    {
        return MEMORY_ERROR;
    }
    else
    {
        return OK;
    }
}


int products_read_to_array(FILE *file, struct product_t *products_array, size_t array_len)
{
    int rc = OK;

    for (size_t i = 0; i < array_len && rc == OK; i++)
    {
        rc = product_read_from_file(file, products_array + i);
    }

    if (rc == EOF)
    {
        rc = OK;
    }

    return rc;
}


void products_array_print(struct product_t *products_array, size_t array_len)
{
    for (size_t i = 0; i < array_len; i++)
    {
        product_print_content(products_array + i);
    }
}


int products_array_free(struct product_t *products_array, size_t array_len)
{
    if (products_array == NULL)
    {
        return FUNCTION_ARGS_ERROR;
    }
    
    for (size_t i = 0; i < array_len; i++)
    {
        product_free_content(products_array + i);
    }

    free(products_array);

    return OK;
}


int print_special_products(struct product_t *products_array, size_t array_len, char *substring)
{
    int is_found = 0;
    
    for (size_t i = 0; i < array_len; i++)
    {
        char *current_name = (products_array + i)->name;

        if (strstr(current_name, substring) == current_name)
        {
            product_print_content(products_array + i);
            is_found = 1;
        }
    }
    
    if (!is_found)
    {
        return NO_SUBSTRING_FOUND_ERROR;
    }
    else
    {
        return OK;
    }
}