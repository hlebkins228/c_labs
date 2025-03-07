#include "matrix_calc_functions.h"
#include "matrix_alloc_functions.h"
#include "matrix_io_functions.h"
#include "exitcodes.h"


int find_min_elem(int **matrix, size_t rows_count, size_t columns_count, int ans_type)
{
    int current_min = matrix[0][0];
    int ans_index = 0;
    
    for (size_t j = 0; j < columns_count; j++)
    {
        for (size_t i = 0; i < rows_count; i++)
        {
            if (matrix[i][j] <= current_min)
            {
                current_min = matrix[i][j];

                if (ans_type == FIND_ROW_INDEX)
                {
                    ans_index = i;
                }
                else if (ans_type == FIND_COLUMN_INDEX)
                {
                    ans_index = j;
                }
            }
        }
    }

    return ans_index;
}


int get_column_geometric_mean(int **matrix, size_t rows_count, size_t column_index)
{   
    int elems_multiply = 1;

    for (size_t i = 0; i < rows_count; i++)
    {
        elems_multiply *= abs(matrix[i][column_index]);
    }

    return (int) floor(pow((double) elems_multiply, 1.0 / rows_count) + EPS);
}


int get_row_min_elem(int *row, size_t columns_count)
{
    int current_min = row[0];

    for (size_t i = 0; i < columns_count; i++)
    {
        if (row[i] < current_min)
        {
            current_min = row[i];
        }
    }

    return current_min;
}


int matrix_raise_to_power(int **matrix, size_t n, int power)
{
    if (power == 0)
    {
        matrix_turn_to_identity(matrix, n);
        return OK;
    }
    
    int rc;
    int **temp_matrix_1 = NULL, **temp_matrix_2 = NULL;
    
    rc = matrix_alloc(&temp_matrix_1, n, n);
    if (rc != OK)
    {
        return rc;
    }

    rc = matrix_alloc(&temp_matrix_2, n, n);
    if (rc != OK)
    {
        return rc;
    }
    
    // вычисляем сколько раз матрицу надо возвести в квадрат
    int intermediate_power = -1;
    int temp = power;
    while (temp)
    {
        temp /= 2;
        intermediate_power++;
    }

    matrix_deepcopy(temp_matrix_1, matrix, n, n);
    for (int i = 0; i < intermediate_power; i++)
    {
        rc = matrix_multiply(temp_matrix_1, temp_matrix_1, temp_matrix_2, n);
        if (rc != OK)
        {
            return rc;
        }
        matrix_deepcopy(temp_matrix_1, temp_matrix_2, n, n);
    }

    int iter_count = power - (int) pow(2.0, (double) intermediate_power);

    for (int i = 0; i < iter_count; i++)
    {
        rc = matrix_multiply(temp_matrix_1, matrix, temp_matrix_2, n);
        if (rc != OK)
        {
            return rc;
        }
        matrix_deepcopy(temp_matrix_1, temp_matrix_2, n, n);
    }

    matrix_deepcopy(matrix, temp_matrix_1, n, n);
    matrix_free(temp_matrix_1, n);
    matrix_free(temp_matrix_2, n);

    return OK;
}


int matrix_multiply(int **matrix_a, int **matrix_b, int **result_matrix, size_t n)
{
    if (matrix_a == NULL || matrix_b == NULL || result_matrix == NULL || n == 0)
    {
        return ARGS_ERROR;
    }
    
    int rc;
    int **transpose_matrix;

    rc = matrix_alloc(&transpose_matrix, n, n);
    if (rc != OK)
    {
        return rc;
    }

    matrix_transpose(matrix_b, transpose_matrix, n);
    int current_elem = 0;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            for (size_t k = 0; k < n; k++)
            {
                current_elem += matrix_a[j][k] * transpose_matrix[i][k];
            }

            result_matrix[j][i] = current_elem;
            current_elem = 0;
        }
    }

    matrix_free(transpose_matrix, n);

    return OK;
}


void matrix_transpose(int **matrix, int **transposed_matrix, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            transposed_matrix[i][j] = matrix[j][i];
        }
    }
}


void matrix_turn_to_identity(int **matrix, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
}