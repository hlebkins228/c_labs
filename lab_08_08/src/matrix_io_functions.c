#include "matrix_io_functions.h"
#include "matrix_alloc_functions.h"
#include "exitcodes.h"


int get_matrix(int ***data, size_t *rows_count, size_t *columns_count)
{
	int rc;
	int temp_n = 0, temp_m = 0;

	if (scanf("%d %d", &temp_n, &temp_m) != 2)
	{
		return INVALID_NUMBERS_ERROR;
	}
	else
	{
		if (temp_n <= 0 || temp_m <= 0)
		{
			return INCORRECT_NUMBERS_INPUTED;
		}
	}
	*rows_count = (size_t) temp_n;
	*columns_count = (size_t) temp_m;

	int **temp_matrix = NULL;
	*data = NULL;

	rc = matrix_alloc(&temp_matrix, *rows_count, *columns_count);
	if (rc != OK)
	{
		return rc;
	}
	else
	{
		rc = matrix_read(temp_matrix, *rows_count, *columns_count);
		if (rc != OK)
		{
			matrix_free(temp_matrix, *rows_count);
			return rc;
		}
	}

	*data = temp_matrix;
	
	return OK;
}


int matrix_read(int **data, size_t rows_count, size_t columns_count)
{
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < columns_count; j++)
		{
			if (scanf("%d", data[i] + j) != 1)
			{
				return MATRIX_READ_ERROR;
			}
		}
	}
	
	return OK;
}


int matrices_power_input(int *a, int *b)
{
	if (scanf("%d %d", a, b) != 2)
	{
		return INVALID_NUMBERS_ERROR;
	}
	else
	{
		if (*a < 0 || *b < 0)
		{
			return INCORRECT_NUMBERS_INPUTED;
		}
	}

	return OK;
}


int matrix_print(int **matrix, size_t rows_count, size_t columns_count)
{
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < columns_count; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	return OK;
}
