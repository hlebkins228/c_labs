#include "func_check.h"
#include "polynomial_funtcions.h"
#include "list.h"
#include "exitcodes.h"

static node_t *create_test_list(int array[], int array_len);
static int list_comparator(node_t *head_1, node_t *head_2);

static node_t *create_test_list(int array[], int array_len)
{
    node_t *list_head = NULL;
    node_t *new_node = NULL;
    
    for (int i = 0; i < array_len; i+= 2)
    {
        new_node = node_create(array[i + 1], array[i]);
        if (!new_node)
        {
            list_free(list_head);

            return NULL;
        }

        list_head = list_add_tail(list_head, new_node);
    }

    return list_head;
}


static int list_comparator(node_t *head_1, node_t *head_2)
{
    int lists_equal = 1;

    node_t *node_1 = head_1;
    node_t *node_2 = head_2;
    
    for (;node_1 != NULL && node_2 != NULL && lists_equal; node_1 = node_1->next, node_2 = node_2->next)
    {
        if (!(node_1->k == node_2->k && node_1->power == node_2->power))
        {
            lists_equal = 0;
        }
    }

    if (node_1 == NULL && node_2 == NULL && lists_equal)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


// позитивные тесты для функции polynomial_value

// обычный тест
START_TEST(polynomial_value_common_test)
{
    int src_array[] = {4, 5, 3, 3, 1, 0};
    int src_array_len = sizeof(src_array) / sizeof(int);

    node_t *list_head = create_test_list(src_array, src_array_len);
    
    double true_ans = 1054;
    double func_ans = polynomial_value(list_head, 3);

    ck_assert_double_eq(func_ans, true_ans);

    list_free(list_head);
}
END_TEST

// все коэффициенты нулевые
START_TEST(polynomial_value_zero_k_test)
{
    int src_array[] = {0, 5, 0, 3, 0, 2};
    int src_array_len = sizeof(src_array) / sizeof(int);

    node_t *list_head = create_test_list(src_array, src_array_len);
    
    double true_ans = 0;
    double func_ans = polynomial_value(list_head, 5);

    ck_assert_double_eq(func_ans, true_ans);

    list_free(list_head);
}
END_TEST

// все степени нулевые
START_TEST(polynomial_value_zero_power_test)
{
    int src_array[] = {4, 0, 3, 0, 0, 0};
    int src_array_len = sizeof(src_array) / sizeof(int);

    node_t *list_head = create_test_list(src_array, src_array_len);
    
    double true_ans = 7;
    double func_ans = polynomial_value(list_head, 5);

    ck_assert_double_eq(func_ans, true_ans);

    list_free(list_head);
}
END_TEST


// позитивные тесты для функции polynomial_derivative

// обычный тест
START_TEST(polynomial_derivative_common_test)
{
    int rc = OK;
    
    int src_array[] = {4, 5, 3, 3, 1, 0};
    int src_array_len = sizeof(src_array) / sizeof(int);

    int dst_array[] = {20, 4, 9, 2};
    int dst_array_len = sizeof(dst_array) / sizeof(int);

    node_t *dst_list_head = create_test_list(src_array, src_array_len);
    node_t *ddx_list_head = create_test_list(dst_array, dst_array_len);
    node_t *result_list_head = NULL;
    
    rc = polynomial_derivative(dst_list_head, &result_list_head);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(list_comparator(result_list_head, ddx_list_head), 1);

    list_free(dst_list_head);
    list_free(ddx_list_head);
    list_free(result_list_head);
}
END_TEST

// полином нулевой степени
START_TEST(polynomial_derivative_zero_power_test)
{
    int rc = OK;
    
    int src_array[] = {4, 0, 3, 0, 1, 0};
    int src_array_len = sizeof(src_array) / sizeof(int);

    node_t *dst_list_head = create_test_list(src_array, src_array_len);
    node_t *result_list_head = NULL;
    
    rc = polynomial_derivative(dst_list_head, &result_list_head);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_eq(result_list_head, NULL);

    list_free(dst_list_head);
}
END_TEST


// негативные тесты для функции polynomial_derivative

// нулевой указатель вместо головы входного списка
START_TEST(polynomial_derivative_zero_pointer_test)
{
    int rc = OK;

    node_t *dst_list_head = NULL;
    node_t *result_list_head = NULL;
    
    rc = polynomial_derivative(dst_list_head, &result_list_head);

    ck_assert_int_eq(rc, FUNC_ARGS_ERROR);
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

    // тесты для функции polynomial_value
    tcase_add_test(tc_pos, polynomial_value_common_test);
    tcase_add_test(tc_pos, polynomial_value_zero_k_test);
    tcase_add_test(tc_pos, polynomial_value_zero_power_test);
    // тесты для функции polynomial_derivative
    tcase_add_test(tc_pos, polynomial_derivative_common_test);
    tcase_add_test(tc_pos, polynomial_derivative_zero_power_test);
    
    suite_add_tcase(s, tc_pos);

    // НЕГАТИВНЫЕ ТЕСТЫ

    tc_neg = tcase_create("negatives");

    // тесты для функции polynomial_derivative
    tcase_add_test(tc_neg, polynomial_derivative_zero_pointer_test);

    suite_add_tcase(s, tc_neg);

    return s;
}
