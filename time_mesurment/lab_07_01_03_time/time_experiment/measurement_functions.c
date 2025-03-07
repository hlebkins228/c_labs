#include "measurement_functions.h"
#include "array_sort_functions.h"
#include "exitcodes.h"

#include <sys/time.h>
#include <stdlib.h>


// получает время работы сортировки для заданного массива в милисекундах
int get_sort_time(int *sort_time, void *array, size_t n, size_t elem_size, comparator cmp)
{
        int rc = OK;
        struct timeval start_time;
        struct timeval end_time;

        gettimeofday(&start_time, NULL);
        qsort(array, n, elem_size, cmp);
        gettimeofday(&end_time, NULL);

        if (rc != OK)
        {
            return rc;
        }
        else
        {
            *sort_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
            return OK;
        }
}


int write_time_to_file(FILE *file, int sort_time)
{
    if (fprintf(file, "%d\n", sort_time) == 1)
    {
        return FILE_WRITE_ERROR;
    }
    else
    {
        return OK;
    }
}