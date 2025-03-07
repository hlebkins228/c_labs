#include "array_sort_functions.h"
#include "exitcodes.h"


int bubble_sort(struct product_t *products_array, size_t array_len)
{
    if (products_array == NULL || array_len == 0)
    {
        return INVALID_FUNC_ARGS_ERROR;
    }
    
    int has_swapped = 1;

    while (has_swapped)
    {
        has_swapped = 0;

        for (size_t i = 0; i < array_len - 1; i++)
        {
            if (comparator(products_array + i, products_array + i + 1))
            {
                swap(products_array + i, products_array + i + 1);
                has_swapped = 1;
            } 
        }
    }

    return OK;
}


void swap(struct product_t *product_1, struct product_t *product_2)
{
    struct product_t buffer;

    buffer = *product_1;
    *product_1 = *product_2;
    *product_2 = buffer;
}


int comparator(struct product_t *product_1, struct product_t *product_2)
{
    return (product_1->weight / product_1->volume > product_2->weight / product_2->volume);
}
