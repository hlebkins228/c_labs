#include "array_io_functions.h"
#include "exitcodes.h"


int get_numbers_count(FILE *file, size_t *numbers_count)
{
    int rc;
    int temp = 0;
    size_t current_count = 0;

    while ((rc = fscanf(file, "%d\n", &temp)) == 1)
    {
        current_count++;
    }

    if (rc != EOF)
    {
        rc = FILE_READ_ERROR;
    }
    else if (current_count == 0)
    {
        rc = EMPTY_FILE_ERROR;
    }
    else
    {
        *numbers_count = current_count;
        rc = OK;
    }

    return rc;
}


int array_alloc(int **array, size_t array_len)
{
    *array = malloc(array_len * sizeof(int));
    if (!(*array))
    {
        return MEM_ALLOC_ERROR;
    }
    else
    {
        return OK;
    }
}


int read_numbers_to_array(FILE *file, int *array_start_pointer, int *array_end_pointer)
{
    int rc = 1;
    int *current_number_pointer = array_start_pointer;

    while (current_number_pointer < array_end_pointer && rc == 1)
    {
        rc = fscanf(file, "%d\n", current_number_pointer);
        if (rc == 1)
        {
            current_number_pointer++;
        }
    }

    if (rc != 1)
    {
        return FILE_READ_ERROR;
    }
    else
    {
        return OK;
    }
}


int write_numbers_to_file(FILE *file, int *array_start_pointer, int *array_end_pointer)
{
    int rc = 1;
    int *current_elem_pointer = array_start_pointer;

    while (current_elem_pointer < array_end_pointer && rc > 0)
    {
        rc = fprintf(file, "%d ", *current_elem_pointer);
        current_elem_pointer++;
    }

    if (rc <= 0)
    {
        return FILE_WRITE_ERROR;
    }
    else
    {
        return OK;
    }
}