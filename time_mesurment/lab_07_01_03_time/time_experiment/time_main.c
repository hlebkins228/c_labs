#include "array_io_functions.h"
#include "array_sort_functions.h"
#include "measurement_functions.h"
#include "exitcodes.h"

void array_print(int *array, size_t array_len);


int main(int args_count, char **argv)
{    
    if (args_count != 3)
    {
        return ARGS_COUNT_ERROR;
    }
    
    int rc = OK;

    int sort_time = 0;

    FILE *file = NULL;
    int file_state = 0;

    size_t numbers_count = 0;
    int *array_start = NULL;
    int *array_end = NULL;

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        rc = FILE_OPEN_ERROR;
    }
    if (rc == OK)
    {
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
    if (rc == OK)
    {
        rc = get_sort_time(&sort_time, array_start, array_end - array_start, sizeof(int), int_cmp);
    }
    if (rc == OK)
    {
        file = fopen(argv[2], "a");
        if (file == NULL)
        {
            rc = FILE_OPEN_ERROR;
        }
    }
    if (rc == OK)
    {
        rc = write_time_to_file(file, sort_time);
        fclose(file);
    }

    free(array_start);

    return rc;
}


void array_print(int *array, size_t array_len)
{
    printf("\nArray: ");
    for (size_t i = 0; i < array_len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}