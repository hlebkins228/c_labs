#ifndef IO_FUNCTIONS_H__

#define IO_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_numbers_count(FILE *file, size_t *numbers_count);
int array_alloc(int **array, size_t array_len);
int read_numbers_to_array(FILE *file, int *array_start_pointer, int *array_end_pointer);
int write_numbers_to_file(FILE *file, int *array_start_pointer, int *array_end_pointer);

#endif