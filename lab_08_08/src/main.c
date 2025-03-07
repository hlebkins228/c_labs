#include "matrix_calc_functions.h"
#include "matrix_io_functions.h"
#include "matrix_alloc_functions.h"
#include "exitcodes.h"


int main(void)
{
    int rc = OK;
    int **matrix_a = NULL, **matrix_b = NULL, **ans_matrix = NULL;
    size_t n_1 = 0, m_1 = 0, n_2 = 0, m_2 = 0;
    int power_a = 0, power_b = 0;

    rc = get_matrix(&matrix_a, &n_1, &m_1);
    if (rc == OK)
    {
        rc = get_matrix(&matrix_b, &n_2, &m_2);
    }
    if (rc == OK)
    {   
        rc = matrices_power_input(&power_a, &power_b);
    }
    if (rc == OK)
    {
        matrix_fetch_to_square_form(&matrix_a, &n_1, &m_1);
        matrix_fetch_to_square_form(&matrix_b, &n_2, &m_2);

        if (n_1 < n_2)
        {
            matrix_increase_to_new_size(&matrix_a, &n_1, &m_1, n_2);
        }
        else if (n_2 < n_1)
        {
            matrix_increase_to_new_size(&matrix_b, &n_2, &m_2, n_1);
        }
    }
    if (rc == OK)
    {
        rc = matrix_raise_to_power(matrix_a, n_1, power_a);
    }
    if (rc == OK)
    {
        rc = matrix_raise_to_power(matrix_b, n_2, power_b);
    }
    if (rc == OK)
    {
        rc = matrix_alloc(&ans_matrix, n_1, m_1);
    }
    if (rc == OK)
    {
        rc = matrix_multiply(matrix_a, matrix_b, ans_matrix, n_1);
    }
    if (rc == OK)
    {
        matrix_print(ans_matrix, n_1, m_1);
    }

    matrix_free(matrix_a, n_1);
    matrix_free(matrix_b, n_2);
    matrix_free(ans_matrix, n_1);

    return rc;
}