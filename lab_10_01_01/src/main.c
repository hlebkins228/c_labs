#include "list.h"
#include "product.h"
#include "exitcodes.h"


int main(int args_count, char **argv)
{
    if (args_count != 2)
    {
        return ARGS_COUNT_ERROR;
    }
    
    int rc = OK;
    node_t *list_head = NULL;

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return FILE_OPEN_ERROR;
    }
    
    void **array_of_product_pointers = NULL;
    size_t array_of_product_pointers_len = 0;

    rc = products_array_memory_alloc(file, &array_of_product_pointers, &array_of_product_pointers_len);
    if (rc == OK)
    {
        rewind(file);
        rc = products_read_to_array(file, array_of_product_pointers, array_of_product_pointers_len);
    }
    if (rc == OK)
    {
        rc = list_read_from_array(&list_head, array_of_product_pointers, array_of_product_pointers_len);
    }
    
    if (rc == OK)
    {
        remove_duplicates(&list_head, data_comparator);
    }
    if (rc == OK)
    {
        node_t *sorted_list_head = sort(list_head, density_comparator);
        if (sorted_list_head == NULL)
        {
            rc = MEMORY_ERROR;
        }
        else
        {
            list_print(sorted_list_head, product_print_content);
        }

        list_free(sorted_list_head);
    }

    list_free(list_head);
    products_array_free(array_of_product_pointers, array_of_product_pointers_len);
    fclose(file);

    return rc;
}
