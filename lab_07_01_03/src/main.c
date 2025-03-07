#include "array_io_functions.h"
#include "array_sort_functions.h"
#include "exitcodes.h"

#define FILTER_KEY "f"

int main(int args_count, char **argv)
{   
    int is_filter_needed = 0;
    
    if (args_count != 3 && args_count != 4)
    {
        return ARGS_COUNT_ERROR;
    }
    
    if (args_count == 4)
    {
        if (strcmp(argv[3], FILTER_KEY))
        {
            return INVALID_ARGS_ERROR;
        }
        else
        {
            is_filter_needed = 1;
        }
    }

    int rc = OK;

    FILE *file = NULL;
    int file_state = 0;

    size_t numbers_count = 0;
    int *array_start = NULL;
    int *array_end = NULL;

    int *filtered_array_start = NULL;
    int *filtered_array_end = NULL;

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        rc = FILE_OPEN_ERROR;
    }
    if (rc == OK)
    {
        file_state = 1;
        rc = get_numbers_count(file, &numbers_count);
        rewind(file);
    }
    if (rc == OK)
    {
        rc = array_alloc(&array_start, numbers_count);
    }
    if (rc == OK)
    {
        array_end = array_start + numbers_count;
        rc = read_numbers_to_array(file, array_start, array_end);
    }
    if (file_state)
    {
        fclose(file);
    }

    if (is_filter_needed && rc == OK)
    {
        rc = key(array_start, array_end, &filtered_array_start, &filtered_array_end);

        if (rc == OK)
        {
            free(array_start);
            array_start = filtered_array_start;
            array_end = filtered_array_end;
        }
    }
    
    if (rc == OK)
    {
        rc = mysort(array_start, array_end - array_start, sizeof(int), int_cmp);
    }
    if (rc == OK)
    {
        file = fopen(argv[2], "w");
        if (file == NULL)
        {
            rc = FILE_OPEN_ERROR;
        }
    }
    if (rc == OK)
    {
        rc = write_numbers_to_file(file, array_start, array_end);
        fclose(file);
    }

    free(array_start);

    return rc;
}