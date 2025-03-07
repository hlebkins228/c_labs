#include "matrix_alloc_functions.h"
#include "matrix_calc_functions.h"
#include "exitcodes.h"


void matrix_free(int **data, size_t rows_count)
{
	if (data)
	{
		for (size_t i = 0; i < rows_count; i++)
		{
			free(data[i]);
		}
		free(data);
	}	
}


int matrix_alloc(int ***data, size_t rows_count, size_t columns_count)
{
	if (rows_count == 0 || columns_count == 0)
	{
		return ARGS_ERROR;
	}

	*data = malloc(rows_count * sizeof(int *));

	if (!*data)
	{
		return MEM_ALLOC_ERROR;
	}
	else
	{
		for (size_t i = 0; i < rows_count; i++)
		{
			(*data)[i] = malloc(columns_count * sizeof(int));
			if (!(*data)[i])
			{
				matrix_free(*data, i);
				return MEM_ALLOC_ERROR;
			}
		}
	}

	return OK;
}


int matrix_add_column(int ***matrix, size_t rows_count, size_t *columns_count)
{
	int *current_row = NULL;
	
	for (size_t i = 0; i < rows_count; i++)
	{
		current_row = realloc((*matrix)[i], (*columns_count + 1) * sizeof(int));
		if (!current_row)
		{
			return MEM_REALLOC_ERROR;
		}
		else
		{
			current_row[*columns_count] = get_row_min_elem(current_row, *columns_count);
			(*matrix)[i] = current_row;
		}
	}

	(*columns_count)++;

	return OK;
}


int matrix_del_column(int **matrix, size_t rows_count, size_t *columns_count, size_t column_to_del_index)
{
	if (column_to_del_index >= *columns_count)
	{
		return INDEX_OUT_OF_RANGE_ERROR;
	}
	
	int *temp_row = NULL;
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = column_to_del_index; j < *columns_count - 1; j++)
		{
			matrix[i][j] = matrix[i][j + 1];
		}
		
		temp_row = realloc(matrix[i], (*columns_count - 1) * sizeof(int));
		if (!temp_row)
		{
			return MEM_REALLOC_ERROR;
		}
		else
		{
			matrix[i] = temp_row;
		}
	}

	(*columns_count)--;

	return OK;
}


int matrix_add_row(int ***matrix, size_t *rows_count, size_t columns_count)
{
	if (matrix == NULL || rows_count == NULL || *rows_count == 0 || columns_count == 0)
	{
		return ARGS_ERROR;
	}
	
	int **temp_matrix = NULL;
	
	temp_matrix = realloc(*matrix, (*rows_count + 1) * sizeof(int *));
	if (!temp_matrix)
	{
		return MEM_REALLOC_ERROR;
	}
	else
	{
		*matrix = temp_matrix;

		(*matrix)[*rows_count] = malloc(columns_count * sizeof(int));
		if (!(*matrix)[*rows_count])
		{
			return MEM_ALLOC_ERROR;
		}
	}
	
	for (size_t j = 0; j < columns_count; j++)
	{
		(*matrix)[*rows_count][j] = get_column_geometric_mean(*matrix, *rows_count, j);
	}

	(*rows_count)++;

	return OK;
}


int matrix_del_row(int ***matrix, size_t *rows_count, size_t columns_count, size_t row_to_del_index)
{
	(void) columns_count;
	
	if (row_to_del_index >= *rows_count)
	{
		return INDEX_OUT_OF_RANGE_ERROR;
	}
	
	free((*matrix)[row_to_del_index]);

	for (size_t i = row_to_del_index; i < *rows_count - 1; i++)
	{
		(*matrix)[i] = (*matrix)[i + 1];
	}

	int **temp_matrix = NULL;
	
	temp_matrix = realloc(*matrix, (*rows_count - 1) * sizeof(int *));
	if (!temp_matrix)
	{
		return MEM_REALLOC_ERROR;
	}
	else
	{
		*matrix = temp_matrix;
		(*rows_count)--;
	}	
	
	return OK;
}


void matrix_fetch_to_square_form(int ***matrix, size_t *rows_count, size_t *columns_count)
{
	int index;
	
	if (*rows_count < *columns_count)
	{
		size_t m = *columns_count;

		for (size_t i = 0; i < m - *rows_count; i++)
		{
			index = find_min_elem(*matrix, *rows_count, *columns_count, FIND_COLUMN_INDEX);
			matrix_del_column(*matrix, *rows_count, columns_count, index);
		}
	}
	else if (*rows_count > *columns_count)
	{
		size_t n = *rows_count;
		
		for (size_t i = 0; i < n - *columns_count; i++)
		{
			index = find_min_elem(*matrix, *rows_count, *columns_count, FIND_ROW_INDEX);
			matrix_del_row(matrix, rows_count, *columns_count, index);
		}
	}
}


void matrix_increase_to_new_size(int ***matrix, size_t *rows_count, size_t *columns_count, size_t target_size)
{
	size_t n = *rows_count;
	size_t m = *columns_count;
	
	for (size_t i = 0; i < target_size - n; i++)
	{
		matrix_add_row(matrix, rows_count, *columns_count);
	}

	for (size_t i = 0; i < target_size - m; i++)
	{
		matrix_add_column(matrix, *rows_count, columns_count);
	}
}


void matrix_deepcopy(int **dist_matrix, int **src_matrix, size_t n, size_t m)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			dist_matrix[i][j] = src_matrix[i][j];
		}
	}
}