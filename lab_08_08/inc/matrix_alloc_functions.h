#ifndef ALLOC_FUNCTIONS_H__

#define ALLOC_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>

void matrix_free(int **data, size_t rows_count);
int matrix_alloc(int ***data, size_t rows_count, size_t columns_count);

int matrix_add_column(int ***matrix, size_t rows_count, size_t *columns_count);
int matrix_del_column(int **matrix, size_t rows_count, size_t *columns_count, size_t column_to_del_index);
int matrix_add_row(int ***matrix, size_t *rows_count, size_t columns_count);
int matrix_del_row(int ***matrix, size_t *rows_count, size_t columns_count, size_t row_to_del_index);

void matrix_fetch_to_square_form(int ***matrix, size_t *rows_count, size_t *columns_count);
void matrix_increase_to_new_size(int ***matrix, size_t *rows_count, size_t *columns_count, size_t target_size); 
void matrix_deepcopy(int **dist_matrix, int **src_matrix, size_t n, size_t m);

#endif