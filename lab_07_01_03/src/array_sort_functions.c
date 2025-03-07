#include "array_sort_functions.h"
#include "array_io_functions.h"
#include "exitcodes.h"


int key(int *src_array_start_pointer, int *src_array_end_pointer, int **dst_array_start_pointer, int **dst_array_end_pointer)
{
    if (src_array_start_pointer == NULL || src_array_end_pointer == NULL || dst_array_start_pointer == NULL || dst_array_end_pointer == NULL)
    {
        return INVALID_FUNC_ARGS_ERROR;
    }
    else if (src_array_end_pointer <= src_array_start_pointer)
    {
        return INVALID_SRC_ARRAY_POINTERS;
    }

    int *end_of_new_array_pointer = src_array_end_pointer - 1;
    int is_found = 0;
    
    for (; end_of_new_array_pointer >= src_array_start_pointer && !is_found; end_of_new_array_pointer--)
    {
        if (*end_of_new_array_pointer < 0)
        {
            is_found = 1;
        }
    }

    if (!is_found)
    {
        end_of_new_array_pointer = src_array_end_pointer;
    }
    else
    {
        end_of_new_array_pointer++;
    }

    if (end_of_new_array_pointer == src_array_start_pointer)
    {
        return EMPTY_FILTERED_ARRAY_ERROR;
    }

    int rc = array_alloc(dst_array_start_pointer, end_of_new_array_pointer - src_array_start_pointer);
    if (rc != OK)
    {
        return rc;
    }

    int *current_src_elem_pointer = src_array_start_pointer;
    int *current_dst_elem_pointer = *dst_array_start_pointer;
    while (current_src_elem_pointer < end_of_new_array_pointer)
    {
        *current_dst_elem_pointer = *current_src_elem_pointer;
        current_src_elem_pointer++;
        current_dst_elem_pointer++;
    }

    *dst_array_end_pointer = current_dst_elem_pointer;

    return OK;
}


// вариант сортировки номер 5 (Модифицированная сортировка пузырьком I)
int mysort(void *p_data, size_t n, size_t elem_size, comparator cmp)
{
    if (p_data == NULL || n <= 0 || elem_size <= 0)
    {
        return INVALID_FUNC_ARGS_ERROR;
    }
    
    char *p_start = p_data;
    char *p_end = p_start + elem_size * n;
    char *last_swap = p_end;
    int has_swapped = 1;

    while (has_swapped)
    {
        has_swapped = 0;
        for (char *p_cur = p_start; p_cur < p_end - elem_size; p_cur += elem_size)
        {
            if (cmp(p_cur, p_cur + elem_size) > 0)
            {
                swap(p_cur, p_cur + elem_size, elem_size);
                last_swap = p_cur + elem_size;
                has_swapped = 1;
            }
        }

        p_end = last_swap;
    }

    return OK;
}


void swap(void *elem_1, void *elem_2, size_t elem_size)
{
    char tmp;
    char *pointer_elem_1 = elem_1;
    char *pointer_elem_2 = elem_2;

    for (size_t i = 0; i < elem_size; i++)
    {
        tmp = *(pointer_elem_1 + i);
        *(pointer_elem_1 + i) = *(pointer_elem_2 + i);
        *(pointer_elem_2 + i) = tmp;
    }
}


int int_cmp(const void *left, const void *right)
{
    const int *cur_left = left;
    const int *cur_right = right;

    return (*cur_left - *cur_right);
}


int double_cmp(const void *left, const void *right)
{
    const double *cur_left = left;
    const double *cur_right = right;

    return (int) ceil((*cur_left - *cur_right));
}


int char_cmp(const void *left, const void *right)
{
    const char *cur_left = left;
    const char *cur_right = right;

    return (int) (*cur_left - *cur_right);
}
