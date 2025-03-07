#include "func_check.h"
#include "list.h"
#include "exitcodes.h"

#include <stdio.h>

static node_t *create_test_list(int array[], int array_len);
static int test_comparator(const void *data_1, const void *data_2);
static int sort_comparator(const void *data_1, const void *data_2);
static int list_comparator(node_t *head_1, node_t *head_2);


// вспомогательная функция для создания списка для тестирования функций
static node_t *create_test_list(int array[], int array_len)
{
    node_t *list_head = NULL;
    node_t *new_node = NULL;
    
    for (int i = 0; i < array_len; i++)
    {
        new_node = node_create(array + i);
        if (!new_node)
        {
            list_free(list_head);

            return NULL;
        }

        list_head = list_add_tail(list_head, new_node);
    }

    return list_head;
}


static int test_comparator(const void *data_1, const void *data_2)
{
    const int *number_1 = data_1;
    const int *number_2 = data_2;

    return *number_1 - *number_2;
}


static int sort_comparator(const void *data_1, const void *data_2)
{
    const int *number_1 = data_1;
    const int *number_2 = data_2;

    return (*number_1 > *number_2);
}


static int list_comparator(node_t *head_1, node_t *head_2)
{
    int lists_equal = 1;

    node_t *node_1 = head_1;
    node_t *node_2 = head_2;
    
    for (;node_1 != NULL && node_2 != NULL && lists_equal; node_1 = node_1->next, node_2 = node_2->next)
    {
        if (test_comparator(node_1->data, node_2->data))
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


// позитивные тесты для функции find

// обычный тест (все числа в списке различны)
START_TEST(find_common_test)
{
    int src_array[] = {4, 5, 8, 10, 50, 7};
    int src_array_len = sizeof(src_array) / sizeof(int);

    node_t *list_head = create_test_list(src_array, src_array_len);

    int target_number = 8;
    
    node_t *found_node = find(list_head, &target_number, test_comparator);

    ck_assert_ptr_eq((list_head->next)->next, found_node);

    list_free(list_head);
}
END_TEST

// в списке повторяется число, узел с которым мы ищем
START_TEST(find_same_data_nodes_test)
{
    int src_array[] = {4, -5, 8, 10, -5, -5};
    int src_array_len = sizeof(src_array) / sizeof(int);

    node_t *list_head = create_test_list(src_array, src_array_len);

    int target_number = -5;
    
    node_t *found_node = find(list_head, &target_number, test_comparator);

    ck_assert_ptr_eq(list_head->next, found_node);

    list_free(list_head);
}
END_TEST


// негативные тесты для функции find

// указатель на NULL вместо головы списка
START_TEST(find_null_head_pointer_test)
{
    int src_array[] = {4, 5, 8, 10, 50, 7};
    
    node_t *list_head = NULL;

    node_t *found_node = find(list_head, src_array + 2, test_comparator);

    ck_assert_ptr_eq(found_node, NULL);
}
END_TEST

// указатель на NULL вместо указателя на данные
START_TEST(find_null_data_pointer_test)
{
    int src_array[] = {4, -5, 8, 10, -5, -5};
    int src_array_len = sizeof(src_array) / sizeof(int);

    node_t *list_head = create_test_list(src_array, src_array_len);
    
    node_t *found_node = find(list_head, NULL, test_comparator);

    ck_assert_ptr_eq(found_node, NULL);

    list_free(list_head);
}
END_TEST


// позитивные тесты для функции remove_duplicates

// обычный тест (дублируется только одно число)
START_TEST(remove_duplicates_common_test)
{
    int src_array[] = {4, -5, 8, 10, -5, -5};
    int src_array_len = sizeof(src_array) / sizeof(int);
    node_t *src_list_head = create_test_list(src_array, src_array_len);

    int correct_array[] = {4, -5, 8, 10};
    int correct_array_len = sizeof(correct_array) / sizeof(int);
    node_t *correct_list_head = create_test_list(correct_array, correct_array_len);
    

    remove_duplicates(&src_list_head, test_comparator);

    ck_assert_int_eq(list_comparator(src_list_head, correct_list_head), 1);

    list_free(src_list_head);
    list_free(correct_list_head);
}
END_TEST

// несколько разных дубликатов
START_TEST(remove_duplicates_some_duplicates_test)
{
    int src_array[] = {8, 8, 8, 4, -5, 7, 8, 10, 4, -5};
    int src_array_len = sizeof(src_array) / sizeof(int);
    node_t *src_list_head = create_test_list(src_array, src_array_len);

    int correct_array[] = {8, 4, -5, 7, 10};
    int correct_array_len = sizeof(correct_array) / sizeof(int);
    node_t *correct_list_head = create_test_list(correct_array, correct_array_len);
    

    remove_duplicates(&src_list_head, test_comparator);

    ck_assert_int_eq(list_comparator(src_list_head, correct_list_head), 1);

    list_free(src_list_head);
    list_free(correct_list_head);
}
END_TEST

// все числа уникальны
START_TEST(remove_duplicates_all_unique_numbers_test)
{
    int src_array[] = {1, -10, 3, 0};
    int src_array_len = sizeof(src_array) / sizeof(int);
    node_t *src_list_head = create_test_list(src_array, src_array_len);

    int correct_array[] = {1, -10, 3, 0};
    int correct_array_len = sizeof(correct_array) / sizeof(int);
    node_t *correct_list_head = create_test_list(correct_array, correct_array_len);
    

    remove_duplicates(&src_list_head, test_comparator);

    ck_assert_int_eq(list_comparator(src_list_head, correct_list_head), 1);
    
    list_free(src_list_head);
    list_free(correct_list_head);
}
END_TEST


// негативные тесты для функции remove_duplicates

// NULL вместо адреса указателя на голову списка
START_TEST(remove_duplicates_null_argument_test)
{
    remove_duplicates(NULL, test_comparator);
}
END_TEST

// нулевой указатель вместо головы списка
START_TEST(remove_duplicates_null_head_pointer_test)
{
    node_t *src_list_head = NULL;
    
    remove_duplicates(&src_list_head, test_comparator);
}
END_TEST


// позитивные тесты для функции sort

// все числа в сортируемом списке одинаковы
START_TEST(sort_all_unique_numbers_test)
{
    int src_array[] = {4, -8, 10, -5, 6};
    int src_array_len = sizeof(src_array) / sizeof(int);

    int sorted_array[] = {-8, -5, 4, 6, 10};
    int sorted_array_len = sizeof(sorted_array) / sizeof(int);

    node_t *src_list_head = create_test_list(src_array, src_array_len);

    node_t *sorted_list_head = create_test_list(sorted_array, sorted_array_len);
    
    node_t *new_list_head = sort(src_list_head, sort_comparator);

    ck_assert_int_eq(list_comparator(new_list_head, sorted_list_head), 1);

    list_free(src_list_head);
    list_free(sorted_list_head);
    list_free(new_list_head);
}
END_TEST

// в сортируемом списке есть повторяющиеся числа
START_TEST(sort_duplicates_numbers_test)
{
    int src_array[] = {10, 4, -8, 10, 10, 10, -5, 4, -8, 6};
    int src_array_len = sizeof(src_array) / sizeof(int);

    int sorted_array[] = {-8, -8, -5, 4, 4, 6, 10, 10, 10, 10};
    int sorted_array_len = sizeof(sorted_array) / sizeof(int);

    node_t *src_list_head = create_test_list(src_array, src_array_len);

    node_t *sorted_list_head = create_test_list(sorted_array, sorted_array_len);
    
    node_t *new_list_head = sort(src_list_head, sort_comparator);

    ck_assert_int_eq(list_comparator(new_list_head, sorted_list_head), 1);

    list_free(src_list_head);
    list_free(sorted_list_head);
    list_free(new_list_head);
}
END_TEST

// в сортируемом списке только одно число, которое повторяется несколько раз
START_TEST(sort_one_number_duplicates_test)
{
    int src_array[] = {7, 7, 7, 7};
    int src_array_len = sizeof(src_array) / sizeof(int);

    int sorted_array[] = {7, 7, 7, 7};
    int sorted_array_len = sizeof(sorted_array) / sizeof(int);

    node_t *src_list_head = create_test_list(src_array, src_array_len);

    node_t *sorted_list_head = create_test_list(sorted_array, sorted_array_len);
    
    node_t *new_list_head = sort(src_list_head, sort_comparator);

    ck_assert_int_eq(list_comparator(new_list_head, sorted_list_head), 1);

    list_free(src_list_head);
    list_free(sorted_list_head);
    list_free(new_list_head);
}
END_TEST

// в сортируемом списке только одно число
START_TEST(sort_only_one_number_test)
{
    int src_array[] = {7};
    int src_array_len = sizeof(src_array) / sizeof(int);

    int sorted_array[] = {7};
    int sorted_array_len = sizeof(sorted_array) / sizeof(int);

    node_t *src_list_head = create_test_list(src_array, src_array_len);

    node_t *sorted_list_head = create_test_list(sorted_array, sorted_array_len);
    
    node_t *new_list_head = sort(src_list_head, sort_comparator);

    ck_assert_int_eq(list_comparator(new_list_head, sorted_list_head), 1);

    list_free(src_list_head);
    list_free(sorted_list_head);
    list_free(new_list_head);
}
END_TEST


// негативные тесты для функции sort

// нулевой указатель вместо головы списка
START_TEST(sort_null_head_pointer_test)
{
    node_t *src_list_head = NULL;
    
    node_t *new_list_head = sort(src_list_head, sort_comparator);

    ck_assert_ptr_eq(new_list_head, NULL);
}
END_TEST


// создание набора тестов
Suite* unit_tests_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("list_unit_tests");
    
    // ПОЗИТИВНЫЕ ТЕСТЫ

    tc_pos = tcase_create("positives");

    // тесты для функции find
    tcase_add_test(tc_pos, find_common_test);
    tcase_add_test(tc_pos, find_same_data_nodes_test);
    // тесты для функции remove_duplicates
    tcase_add_test(tc_pos, remove_duplicates_common_test);
    tcase_add_test(tc_pos, remove_duplicates_some_duplicates_test);
    tcase_add_test(tc_pos, remove_duplicates_all_unique_numbers_test);
    // тесты для функции sort
    tcase_add_test(tc_pos, sort_all_unique_numbers_test);
    tcase_add_test(tc_pos, sort_duplicates_numbers_test);
    tcase_add_test(tc_pos, sort_one_number_duplicates_test);
    tcase_add_test(tc_pos, sort_only_one_number_test);
    
    suite_add_tcase(s, tc_pos);

    // НЕГАТИВНЫЕ ТЕСТЫ

    tc_neg = tcase_create("negatives");

    // тесты для функции find
    tcase_add_test(tc_neg, find_null_head_pointer_test);
    tcase_add_test(tc_neg, find_null_data_pointer_test);
    // тесты для функции remove_duplicates
    tcase_add_test(tc_neg, remove_duplicates_null_argument_test);
    tcase_add_test(tc_neg, remove_duplicates_null_head_pointer_test);
    // тесты для функции sort
    tcase_add_test(tc_neg, sort_null_head_pointer_test);

    suite_add_tcase(s, tc_neg);

    return s;
}
