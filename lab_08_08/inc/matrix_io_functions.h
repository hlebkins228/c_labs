#ifndef IO_FUNCTIONS_H__

#define IO_FUNCTIONS_H__

#include <stdio.h>

int matrices_power_input(int *a, int *b);
int get_matrix(int ***data, size_t *rows_count, size_t *columns_count);
int matrix_read(int **data, size_t rows_count, size_t columns_count);
int matrix_print(int **matrix, size_t rows_count, size_t columns_count);

#endif