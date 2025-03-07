#ifndef MEASUREMENT_FUNCTIONS_H__

#define MEASUREMENT_FUNCTIONS_H__

#include "array_sort_functions.h"

int get_sort_time(int *sort_time, void *array, size_t n, size_t elem_size, comparator cmp);
int write_time_to_file(FILE *file, int sort_time);

#endif