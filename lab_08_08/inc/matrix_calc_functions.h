#ifndef CALC_FUNCTIONS_H__

#define CALC_FUNCTIONS_H__

#define FIND_ROW_INDEX     1
#define FIND_COLUMN_INDEX  2

#define EPS 1e-7


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int find_min_elem(int **matrix, size_t rows_count, size_t columns_count, int ans_type);
int get_column_geometric_mean(int **matrix, size_t rows_count, size_t column_index);
int get_row_min_elem(int *row, size_t columns_count);

void matrix_transpose(int **matrix, int **transposed_matrix, size_t size);
int matrix_multiply(int **matrix_1, int **matrix_2, int **result_matrix, size_t n);
int matrix_raise_to_power(int **matrix, size_t n, int power);
void matrix_transpose(int **matrix, int **t_matrix, size_t n);
void matrix_turn_to_identity(int **matrix, size_t n);

#endif 