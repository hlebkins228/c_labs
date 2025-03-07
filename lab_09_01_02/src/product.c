#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "exitcodes.h"


int product_read_from_file(FILE *file, struct product_t *product_pointer)
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
            rc = product_init_content(product_pointer, buffer, temp_weight, temp_volume);
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


int product_init_content(struct product_t *product_pointer, const char *title, double weight, double volume)
{
    char *temp_string_pointer = strdup(title);

    if (!temp_string_pointer)
    {
        return MEMORY_ERROR;
    }
    else
    {
        product_free_content(product_pointer);
        product_pointer->name = temp_string_pointer;
        product_pointer->weight = weight;
        product_pointer->volume = volume;
    }
    
    return OK;
}


void product_print_content(struct product_t *product_pointer)
{
    printf("%s%lf\n%lf\n", product_pointer->name, product_pointer->weight, product_pointer->volume);
}


void product_free_content(struct product_t *product_pointer)
{
    free(product_pointer->name);
    product_pointer->name = NULL;
    product_pointer->weight = -1;
    product_pointer->volume = -1;
}
