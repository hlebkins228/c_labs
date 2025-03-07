#include "func_check.h"
#include "matrix_alloc_functions.h"
#include "matrix_calc_functions.h"
#include "exitcodes.h"


// функция сравнения матриц
int matrix_compare(int **matrix_a, int **matrix_b, size_t n, size_t m)
{
    int equal = 1;

    for (size_t i = 0; i < n && equal; i++)
    {
        for (size_t j = 0; j < m  && equal; j++)
        {
            if (matrix_a[i][j] != matrix_b[i][j])
            {
                equal = 0;
            }
        }
    }

    return equal;
}


// позитивный тест для функции find_min_elem
START_TEST(find_min_elem_pos_test)
{
    int **matrix = NULL;
    size_t n = 3, m = 3;

    matrix_alloc(&matrix, n, m);

    matrix[0][0] = -1;
    matrix[0][1] = 5;
    matrix[0][2] = 2;
    matrix[1][0] = 4;
    matrix[1][1] = -1;
    matrix[1][2] = -1;
    matrix[2][0] = 7;
    matrix[2][1] = -1;
    matrix[2][2] = 4;

    ck_assert_int_eq(find_min_elem(matrix, n, m, FIND_COLUMN_INDEX), 2);
    ck_assert_int_eq(find_min_elem(matrix, n, m, FIND_ROW_INDEX), 1);

    matrix_free(matrix, n);
}
END_TEST


// позитивный тест для функции matrix_alloc
START_TEST(matrix_alloc_pos_test)
{
    int rc;
    int **matrix = NULL;

    rc = matrix_alloc(&matrix, 2, 2);

    ck_assert_int_eq(rc, OK);

    matrix_free(matrix, 2);
}
END_TEST


// негативные тесты для функции matrix_alloc
START_TEST(matrix_alloc_with_zero_rows_count)
{
    int rc;
    int **matrix = NULL;
    size_t rows_count = 0;
    size_t columns_count = 2;

    rc = matrix_alloc(&matrix, rows_count, columns_count);

    ck_assert_int_eq(rc, ARGS_ERROR);
}
END_TEST


START_TEST(matrix_alloc_with_zero_columns_count)
{
    int rc;
    int **matrix = NULL;
    size_t rows_count = 2;
    size_t columns_count = 0;

    rc = matrix_alloc(&matrix, rows_count, columns_count);

    ck_assert_int_eq(rc, ARGS_ERROR);
}
END_TEST


// позитивный тест для функции add_row
START_TEST(add_row_pos_test)
{
    int rc;
    int **matrix_a = NULL, **matrix_b = NULL;
    size_t n = 3, m = 4;
    matrix_alloc(&matrix_a, n, m);
    matrix_alloc(&matrix_b, n + 1, m);

    matrix_a[0][0] = 2;
    matrix_a[0][1] = 5;
    matrix_a[0][2] = -3;
    matrix_a[0][3] = 10;
    matrix_a[1][0] = 4;
    matrix_a[1][1] = 10;
    matrix_a[1][2] = -3;
    matrix_a[1][3] = 0;
    matrix_a[2][0] = 8;
    matrix_a[2][1] = 3;
    matrix_a[2][2] = -3;
    matrix_a[2][3] = 7;

    matrix_deepcopy(matrix_b, matrix_a, n, m);

    rc = matrix_add_row(&matrix_a, &n, m);

    matrix_b[3][0] = 4;
    matrix_b[3][1] = 5;
    matrix_b[3][2] = 3;
    matrix_b[3][3] = 0;

    ck_assert_int_eq(rc, OK);
    ck_assert_uint_eq(n, 4);
    ck_assert_int_eq(matrix_compare(matrix_a, matrix_b, n, m), 1);
    
    matrix_free(matrix_a, n);
    matrix_free(matrix_b, n);
}
END_TEST


// негагивные тесты для функции add_row
START_TEST(add_row_null_matrix)
{
    int rc;
    size_t n = 2, m = 2; 

    rc = matrix_add_row(NULL, &n, m);

    ck_assert_int_eq(rc, ARGS_ERROR);
}
END_TEST


START_TEST(add_row_zero_rows_count)
{
    int **matrix = NULL;
    int rc;
    size_t n = 0, m = 2; 

    rc = matrix_add_row(&matrix, &n, m);

    ck_assert_int_eq(rc, ARGS_ERROR);
}
END_TEST


START_TEST(add_row_zero_columns_count)
{
    int **matrix = NULL;
    int rc;
    size_t n = 2, m = 0; 

    rc = matrix_add_row(&matrix, &n, m);

    ck_assert_int_eq(rc, ARGS_ERROR);
}
END_TEST


// позитивный тест для фунции matrix_multiply
START_TEST(matrix_multiply_pos_test)
{
    int **matrix_a = NULL;
    int **matrix_b = NULL;
    int **result_matrix = NULL;
    int **true_result_matrix = NULL;
    int rc;
    size_t n = 2;

    matrix_alloc(&matrix_a, n, n);
    matrix_alloc(&matrix_b, n, n);
    matrix_alloc(&result_matrix, n, n);
    matrix_alloc(&true_result_matrix, n, n);

    matrix_a[0][0] = 1;
    matrix_a[0][1] = 0;
    matrix_a[1][0] = 3;
    matrix_a[1][1] = -4;

    matrix_b[0][0] = -4;
    matrix_b[0][1] = 2;
    matrix_b[1][0] = 3;
    matrix_b[1][1] = 8;

    true_result_matrix[0][0] = -4;
    true_result_matrix[0][1] = 2;
    true_result_matrix[1][0] = -24;
    true_result_matrix[1][1] = -26;


    rc = matrix_multiply(matrix_a, matrix_b, result_matrix, n);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(matrix_compare(result_matrix, true_result_matrix, n, n), 1);

    matrix_free(matrix_a, n);
    matrix_free(matrix_b, n);
    matrix_free(result_matrix, n);
    matrix_free(true_result_matrix, n);
}
END_TEST


// негативные тесты для фукции matrix_multiply
START_TEST(matrix_multiply_null_matrix_a)
{
    int **matrix_b = NULL;
    int **result_matrix = NULL;
    int rc;
    size_t n = 2;

    matrix_alloc(&matrix_b, n, n);
    matrix_alloc(&result_matrix, n, n);

    rc = matrix_multiply(NULL, matrix_b, result_matrix, n);

    ck_assert_int_eq(rc, ARGS_ERROR);

    matrix_free(matrix_b, n);
    matrix_free(result_matrix, n);
}
END_TEST


START_TEST(matrix_multiply_null_matrix_b)
{
    int **matrix_a = NULL;
    int **result_matrix = NULL;
    int rc;
    size_t n = 2;

    matrix_alloc(&matrix_a, n, n);
    matrix_alloc(&result_matrix, n, n);

    rc = matrix_multiply(matrix_a, NULL, result_matrix, n);

    ck_assert_int_eq(rc, ARGS_ERROR);

    
    matrix_free(matrix_a, n);
    matrix_free(result_matrix, n);
}
END_TEST


START_TEST(matrix_multiply_zero_size)
{
    int **matrix_a = NULL;
    int **matrix_b = NULL;
    int **result_matrix = NULL;
    int rc;
    size_t n = 2;

    matrix_alloc(&matrix_a, n, n);
    matrix_alloc(&matrix_b, n, n);
    matrix_alloc(&result_matrix, n, n);

    rc = matrix_multiply(matrix_a, matrix_b, result_matrix, 0);

    ck_assert_int_eq(rc, ARGS_ERROR);

    matrix_free(matrix_a, n);
    matrix_free(matrix_b, n);
    matrix_free(result_matrix, n);
}
END_TEST


// создание набора тестов
Suite* unit_tests_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("all_functions_suite");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, matrix_alloc_with_zero_rows_count);
    tcase_add_test(tc_neg, matrix_alloc_with_zero_columns_count);

    tcase_add_test(tc_neg, add_row_null_matrix);
    tcase_add_test(tc_neg, add_row_zero_rows_count);
    tcase_add_test(tc_neg, add_row_zero_columns_count);

    tcase_add_test(tc_neg, matrix_multiply_null_matrix_a);
    tcase_add_test(tc_neg, matrix_multiply_null_matrix_b);
    tcase_add_test(tc_neg, matrix_multiply_zero_size);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, matrix_alloc_pos_test);
    tcase_add_test(tc_pos, add_row_pos_test);
    tcase_add_test(tc_pos, matrix_multiply_pos_test);
    tcase_add_test(tc_pos, find_min_elem_pos_test);

    suite_add_tcase(s, tc_pos);

    return s;
}