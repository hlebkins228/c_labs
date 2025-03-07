#include "product.h"
#include "products_array.h"
#include "array_sort_functions.h"
#include "exitcodes.h"

#include <stdio.h>
#include <string.h>

int check_parameter_all(char *string);


int main(int args_count, char **argv)
{
    size_t array_length = 0, rc = OK;
    struct product_t *array_with_products = NULL;
    
    if (args_count != 2 && args_count != 3)
    { 
        return ARGS_COUNT_ERROR;
    }   
    
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return FILE_OPEN_ERROR;
    }

    rc = products_array_memory_alloc(file, &array_with_products, &array_length);
    rewind(file);
    
    if (rc == OK)
    {
        rc = products_read_to_array(file, array_with_products, array_length);
    }
    if (rc == OK)
    {
        if (args_count == 2)
        {
            bubble_sort(array_with_products, array_length);
            products_array_print(array_with_products, array_length);
        }
        else if (args_count == 3)
        {   
            if (check_parameter_all(argv[2]))
            {
                products_array_print(array_with_products, array_length);
            }
            else
            {
                rc = print_special_products(array_with_products, array_length, argv[2]);
            }
        }
    }

    products_array_free(array_with_products, array_length);
    fclose(file);

    return rc;
}


int check_parameter_all(char *string)
{
    int ans_check = 1;

    if (strlen(string) == 3)
    {
        if (string[0] != 'a' && string[0] != 'A')
        {
            ans_check = 0;
        }
        
        if (string[1] != 'l' && string[1] != 'L')
        {
            ans_check = 0;
        }

        if (string[2] != 'l' && string[2] != 'L')
        {
            ans_check = 0;
        }
    }
    else
    {
        ans_check = 0;
    }

    return ans_check;
}
