#include "func_check.h"
#include "array_sort_functions.h"
#include "exitcodes.h"


// позитивные тесты для функции mysort

// обычный тест для массива целых чисел
START_TEST(common_int_mysort_test)
{
    int rc;
    
    size_t n = 6;
    int src_array[] = {1, 4, 2, -1, 0, 5};
    int dst_array[] = {-1, 0, 1, 2, 4, 5};
    
    rc = mysort(src_array, n, sizeof(int), int_cmp);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(src_array, dst_array, n * sizeof(int)), 0);
}
END_TEST


// все числа в массиве одинаковые
START_TEST(equal_int_numbers_test)
{
    int rc;
    
    size_t n = 6;
    int src_array[] = {5, 5, 5, 5, 5, 5};
    int dst_array[] = {5, 5, 5, 5, 5, 5};
    
    rc = mysort(src_array, n, sizeof(int), int_cmp);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(src_array, dst_array, n * sizeof(int)), 0);
}
END_TEST


// в массиве только одно число
START_TEST(only_one_int_number_in_array_test)
{
    int rc;
    
    size_t n = 1;
    int src_array[] = {2};
    int dst_array[] = {2};
    
    rc = mysort(src_array, n, sizeof(int), int_cmp);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(src_array, dst_array, n * sizeof(int)), 0);
}
END_TEST


// обычный тест для массива вещественных чисел
START_TEST(common_double_mysort_test)
{
    int rc;
    
    size_t n = 6;
    double src_array[] = {1.2, 4.33, 2, -1.11, 0, 5.89};
    double dst_array[] = {-1.11, 0, 1.2, 2, 4.33, 5.89};
    
    rc = mysort(src_array, n, sizeof(double), double_cmp);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(src_array, dst_array, n * sizeof(double)), 0);
}
END_TEST


// все числа в массиве одинаковые
START_TEST(equal_double_numbers_test)
{
    int rc;
    
    size_t n = 4;
    double src_array[] = {6.66, 6.66, 6.66, 6.66};
    double dst_array[] = {6.66, 6.66, 6.66, 6.66};
    
    rc = mysort(src_array, n, sizeof(double), double_cmp);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(src_array, dst_array, n * sizeof(double)), 0);
}
END_TEST


// в массиве только одно число
START_TEST(only_one_double_number_in_array_test)
{
    int rc;
    
    size_t n = 1;
    double src_array[] = {2.1};
    double dst_array[] = {2.1};
    
    rc = mysort(src_array, n, sizeof(double), double_cmp);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(src_array, dst_array, n * sizeof(double)), 0);
}
END_TEST


// обычный тест для массива символов
START_TEST(common_char_mysort_test)
{
    int rc;
    
    size_t n = 6;
    char src_array[] = {'x', 'r', 'd', 'a', 'b', 'a'};
    char dst_array[] = {'a', 'a', 'b', 'd', 'r', 'x'};
    
    rc = mysort(src_array, n, sizeof(char), char_cmp);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(src_array, dst_array, n * sizeof(char)), 0);
}
END_TEST


// все символы в массиве одинаковые
START_TEST(equal_char_elements_test)
{
    int rc;
    
    size_t n = 5;
    char src_array[] = {'f', 'f', 'f', 'f', 'f'};
    char dst_array[] = {'f', 'f', 'f', 'f', 'f'};
    
    rc = mysort(src_array, n, sizeof(char), char_cmp);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(src_array, dst_array, n * sizeof(char)), 0);
}
END_TEST


// в массиве только один символ
START_TEST(only_one_char_element_in_array_test)
{
    int rc;
    
    size_t n = 1;
    double src_array[] = {'t'};
    double dst_array[] = {'t'};
    
    rc = mysort(src_array, n, sizeof(char), char_cmp);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(src_array, dst_array, n * sizeof(char)), 0);
}
END_TEST


// негативные тесты для функции mysort

// нулевой указатель вместо массива
START_TEST(array_null_pointer_test)
{
    int rc;
    
    size_t n = 6;
    int *array = NULL;
    rc = mysort(array, n, sizeof(int), int_cmp);
    
    ck_assert_int_eq(rc, INVALID_FUNC_ARGS_ERROR);
}
END_TEST


// нулевой размер массива
START_TEST(zero_array_len_test)
{
    int rc;
    
    size_t n = 0;
    int array[] = {4, 1, 4};
    rc = mysort(array, n, sizeof(int), int_cmp);
    
    ck_assert_int_eq(rc, INVALID_FUNC_ARGS_ERROR);
}
END_TEST


// нулевой размер элемента
START_TEST(zero_elem_size_test)
{
    int rc;
    
    size_t n = 3;
    int array[] = {4, 1, 4};
    rc = mysort(array, n, 0, int_cmp);
    
    ck_assert_int_eq(rc, INVALID_FUNC_ARGS_ERROR);
}
END_TEST


// позитивные тесты для функции key

// обычный тест
START_TEST(common_key_test)
{
    int rc;

    int src_array[] = {4, 1, -4, 2, -5, 10};
    int dst_array[] = {4, 1, -4, 2};
    int *new_array_start_pointer = NULL;
    int *new_array_end_pointer = NULL;

    rc = key(src_array, src_array + 6, &new_array_start_pointer, &new_array_end_pointer);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(dst_array, new_array_start_pointer, 4 * sizeof(int)), 0);

    free(new_array_start_pointer);
}
END_TEST


// в массиве нет отрицательных чисел
START_TEST(no_negative_numbers_in_array)
{
    int rc;

    int src_array[] = {4, 1, 2, 9, 10};
    int dst_array[] = {4, 1, 2, 9, 10};
    int *new_array_start_pointer = NULL;
    int *new_array_end_pointer = NULL;

    rc = key(src_array, src_array + 5, &new_array_start_pointer, &new_array_end_pointer);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(dst_array, new_array_start_pointer, 5 * sizeof(int)), 0);

    free(new_array_start_pointer);
}
END_TEST


// в массиве только одно отрицательное число
START_TEST(only_one_negative_number_in_array)
{
    int rc;

    int src_array[] = {4, 1, 4, 2, -5, 10};
    int dst_array[] = {4, 1, 4, 2};
    int *new_array_start_pointer = NULL;
    int *new_array_end_pointer = NULL;

    rc = key(src_array, src_array + 6, &new_array_start_pointer, &new_array_end_pointer);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(dst_array, new_array_start_pointer, 4 * sizeof(int)), 0);

    free(new_array_start_pointer);
}
END_TEST


// в массиве несколько отрицательных чисел
START_TEST(several_negative_numbers_in_array)
{
    int rc;

    int src_array[] = {9, 0, 13, -4, 2, -5, -10};
    int dst_array[] = {9, 0, 13, -4, 2, -5};
    int *new_array_start_pointer = NULL;
    int *new_array_end_pointer = NULL;

    rc = key(src_array, src_array + 7, &new_array_start_pointer, &new_array_end_pointer);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(dst_array, new_array_start_pointer, 6 * sizeof(int)), 0);

    free(new_array_start_pointer);
}
END_TEST


// негативные тесты ддя функции key

// указатели на NULL вместо указателя на начало исходного массива
START_TEST(null_src_array_start_pointer)
{
    int rc;

    int src_array[] = {4, 3, 2, 5};

    int *src_array_start_pointer = NULL;
    int *src_array_end_pointer = src_array + 4;
    int *new_array_start_pointer = NULL;
    int *new_array_end_pointer = NULL;

    rc = key(src_array_start_pointer, src_array_end_pointer, &new_array_start_pointer, &new_array_end_pointer);

    ck_assert_int_eq(rc, INVALID_FUNC_ARGS_ERROR);
}
END_TEST


// указатели на NULL вместо указателя на конец исходного массива
START_TEST(null_src_array_end_pointer)
{
    int rc;

    int src_array[] = {4, 3, 2, 5};

    int *src_array_start_pointer = src_array;
    int *src_array_end_pointer = NULL;
    int *new_array_start_pointer = NULL;
    int *new_array_end_pointer = NULL;

    rc = key(src_array_start_pointer, src_array_end_pointer, &new_array_start_pointer, &new_array_end_pointer);

    ck_assert_int_eq(rc, INVALID_FUNC_ARGS_ERROR);
}
END_TEST


// указатели на начало массива больше адреса на конец массива
START_TEST(array_start_pointer_greater_then_array_end_pointer)
{
    int rc;

    int src_array[] = {4, 3, 2, 5};

    int *src_array_start_pointer = src_array + 4;
    int *src_array_end_pointer = src_array;
    int *new_array_start_pointer = NULL;
    int *new_array_end_pointer = NULL;

    rc = key(src_array_start_pointer, src_array_end_pointer, &new_array_start_pointer, &new_array_end_pointer);

    ck_assert_int_eq(rc, INVALID_SRC_ARRAY_POINTERS);
}
END_TEST


// в массиве только одно отрицательное число, причем оно первое
START_TEST(first_number_in_array_is_negative)
{
    int rc;

    int src_array[] = {-10, 3, 5};
    int *new_array_start_pointer = NULL;
    int *new_array_end_pointer = NULL;

    rc = key(src_array, src_array + 3, &new_array_start_pointer, &new_array_end_pointer);

    ck_assert_int_eq(rc, EMPTY_FILTERED_ARRAY_ERROR);
}
END_TEST



// создание набора тестов
Suite* unit_tests_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("sort_functions_unit_tests");
    
    // ПОЗИТИВНЫЕ ТЕСТЫ

    tc_pos = tcase_create("positives");

    // тесты на сортировку массивов целых чисел
    tcase_add_test(tc_pos, common_int_mysort_test);
    tcase_add_test(tc_pos, equal_int_numbers_test);
    tcase_add_test(tc_pos, only_one_int_number_in_array_test);
    // тесты на сортировку массивов вещественных чисел
    tcase_add_test(tc_pos, common_double_mysort_test);
    tcase_add_test(tc_pos, equal_double_numbers_test);
    tcase_add_test(tc_pos, only_one_double_number_in_array_test);
    // тесты на сортировку массивов символов
    tcase_add_test(tc_pos, common_char_mysort_test);
    tcase_add_test(tc_pos, equal_char_elements_test);
    tcase_add_test(tc_pos, only_one_char_element_in_array_test);
    // тесты для функции key
    tcase_add_test(tc_pos, common_key_test);
    tcase_add_test(tc_pos, no_negative_numbers_in_array);
    tcase_add_test(tc_pos, only_one_negative_number_in_array);
    tcase_add_test(tc_pos, several_negative_numbers_in_array);
    
    suite_add_tcase(s, tc_pos);

    // НЕГАТИВНЫЕ ТЕСТЫ

    tc_neg = tcase_create("negatives");

    // для функции mysort
    tcase_add_test(tc_neg, array_null_pointer_test);
    tcase_add_test(tc_neg, zero_array_len_test);
    tcase_add_test(tc_neg, zero_elem_size_test);
    // для функции key
    tcase_add_test(tc_neg, null_src_array_start_pointer);
    tcase_add_test(tc_neg, null_src_array_end_pointer);
    tcase_add_test(tc_neg, array_start_pointer_greater_then_array_end_pointer);
    tcase_add_test(tc_neg, first_number_in_array_is_negative);
    
    suite_add_tcase(s, tc_neg);

    return s;
}