#include "check_func_1.h"
#include "associative_array.h"

static void number_increase(const char *key, int *num, void *param);


static void number_increase(const char *key, int *num, void *param)
{
    (void) key;
    
    int *factor = param;

    *num *= *factor;
}


// позитивные тесты для функции assoc_array_insert

// обычный тест
START_TEST(assoc_array_insert_common_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_error_t rc = assoc_array_insert(dict, "misha", 19);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&dict);
}
END_TEST


// негативные тесты для функции assoc_array_insert

// нулевой указатель вместо массива
START_TEST(assoc_array_insert_null_array_pointer_test)
{
    assoc_array_error_t rc = assoc_array_insert(NULL, "lena", 10);

    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

// нулевой указатель вместо ключа
START_TEST(assoc_array_insert_null_key_pointer_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_error_t rc = assoc_array_insert(dict, NULL, 10);

    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&dict);
}
END_TEST

// ключ уже существует
START_TEST(assoc_array_insert_key_already_exists_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 10);

    assoc_array_error_t rc = assoc_array_insert(dict, "misha", 20);

    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&dict);
}
END_TEST

// пустая строка в качестве ключа
START_TEST(assoc_array_insert_empty_string_key_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_error_t rc = assoc_array_insert(dict, "", 10);

    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&dict);
}
END_TEST


// позитивные тесты для функции assoc_array_find

// обычный тест
START_TEST(assoc_array_find_common_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 19);
    assoc_array_insert(dict, "sasha", 15);
    assoc_array_insert(dict, "dasha", 24);
    assoc_array_insert(dict, "pasha", 13);

    int *number = NULL;

    assoc_array_error_t rc = assoc_array_find(dict, "dasha", &number);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*number, 24);

    assoc_array_destroy(&dict);
}
END_TEST

// обычный тест (интересующий нас ключ находится в конце массива)
START_TEST(assoc_array_find_special_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 19);
    assoc_array_insert(dict, "sasha", 15);
    assoc_array_insert(dict, "dasha", 24);
    assoc_array_insert(dict, "pasha", 13);

    int *number = NULL;

    assoc_array_error_t rc = assoc_array_find(dict, "pasha", &number);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*number, 13);

    assoc_array_destroy(&dict);
}
END_TEST


// негативные тесты для функции assoc_array_find

// нулевой указатель вместо указателя на указатель на число
START_TEST(assoc_array_find_null_number_pointer_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 19);
    assoc_array_insert(dict, "sasha", 15);
    assoc_array_insert(dict, "dasha", 24);
    assoc_array_insert(dict, "pasha", 13);

    assoc_array_error_t rc = assoc_array_find(dict, "pasha", NULL);

    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&dict);
}
END_TEST

// попытка найти значение по несуществующему ключу
START_TEST(assoc_array_find_fake_key_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 19);
    assoc_array_insert(dict, "sasha", 15);
    assoc_array_insert(dict, "dasha", 24);
    assoc_array_insert(dict, "pasha", 13);

    int *number = NULL;

    assoc_array_error_t rc = assoc_array_find(dict, "roma", &number);

    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&dict);
}
END_TEST

// пустая строка в качестве ключа
START_TEST(assoc_array_find_empty_string_key_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 19);
    assoc_array_insert(dict, "sasha", 15);
    assoc_array_insert(dict, "dasha", 24);
    assoc_array_insert(dict, "pasha", 13);

    int *number = NULL;

    assoc_array_error_t rc = assoc_array_find(dict, "", &number);

    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&dict);
}
END_TEST


// позитивные тесты для функции assoc_array_remove

// обычный тест
START_TEST(assoc_array_remove_common_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 19);
    assoc_array_insert(dict, "sasha", 15);
    assoc_array_insert(dict, "dasha", 24);
    assoc_array_insert(dict, "pasha", 13);

    int *number = NULL;

    assoc_array_error_t remove_rc = assoc_array_remove(dict, "sasha");
    assoc_array_error_t find_rc = assoc_array_find(dict, "sasha", &number); 

    ck_assert_int_eq(remove_rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(find_rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&dict);
}
END_TEST


// негативные тесты для функции assoc_array_remove

// попытка удалить значение по несуществующему ключу
START_TEST(assoc_array_remove_fake_key_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 19);
    assoc_array_insert(dict, "sasha", 15);
    assoc_array_insert(dict, "dasha", 24);
    assoc_array_insert(dict, "pasha", 13);

    assoc_array_error_t remove_rc = assoc_array_remove(dict, "duck");

    ck_assert_int_eq(remove_rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&dict);
}
END_TEST

// пустая строка в качестве ключа
START_TEST(assoc_array_remove_empty_string_key_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 19);
    assoc_array_insert(dict, "sasha", 15);
    assoc_array_insert(dict, "dasha", 24);
    assoc_array_insert(dict, "pasha", 13);

    assoc_array_error_t remove_rc = assoc_array_remove(dict, "");

    ck_assert_int_eq(remove_rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&dict);
}
END_TEST


// позитивные тесты для функции assoc_array_each

// обычный тест
START_TEST(assoc_array_each_common_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 19);
    assoc_array_insert(dict, "sasha", 15);
    assoc_array_insert(dict, "dasha", 24);

    int x = 2;

    assoc_array_error_t rc = assoc_array_each(dict, number_increase, &x);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *new_number = NULL;

    assoc_array_find(dict, "misha", &new_number);
    ck_assert_int_eq(*new_number, 19 * 2);
    assoc_array_find(dict, "sasha", &new_number);
    ck_assert_int_eq(*new_number, 15 * 2);
    assoc_array_find(dict, "dasha", &new_number);
    ck_assert_int_eq(*new_number, 24 * 2);

    assoc_array_destroy(&dict);
}
END_TEST


// позитивные тесты для функции assoc_array_max

// обычный тест
START_TEST(assoc_array_max_common_test)
{
    assoc_array_t dict = assoc_array_create();

    assoc_array_insert(dict, "misha", 19);
    assoc_array_insert(dict, "sasha", 15);
    assoc_array_insert(dict, "dasha", 24);
    assoc_array_insert(dict, "pasha", 13);

    int *number = NULL;

    assoc_array_error_t rc = assoc_array_max(dict, &number);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*number, 15);

    assoc_array_destroy(&dict);
}
END_TEST


// создание набора тестов
Suite* unit_tests_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("assoc_array_unit_tests");
    
    // ПОЗИТИВНЫЕ ТЕСТЫ

    tc_pos = tcase_create("positives");

    // тесты для функции assoc_array_insert
    tcase_add_test(tc_pos, assoc_array_insert_common_test);
    // тесты для функции assoc_array_find
    tcase_add_test(tc_pos, assoc_array_find_common_test);
    tcase_add_test(tc_pos, assoc_array_find_special_test);
    // тесты для функции assoc_array_remove
    tcase_add_test(tc_pos, assoc_array_remove_common_test);
    // тесты для функции assoc_array_each
    tcase_add_test(tc_pos, assoc_array_each_common_test);
    // тесты для функции assoc_array_max
    tcase_add_test(tc_pos, assoc_array_max_common_test);
    
    suite_add_tcase(s, tc_pos);

    // НЕГАТИВНЫЕ ТЕСТЫ

    tc_neg = tcase_create("negatives");

    // тесты для функции assoc_array_insert
    tcase_add_test(tc_neg, assoc_array_insert_null_array_pointer_test);
    tcase_add_test(tc_neg, assoc_array_insert_null_key_pointer_test);
    tcase_add_test(tc_neg, assoc_array_insert_key_already_exists_test);
    tcase_add_test(tc_neg, assoc_array_insert_empty_string_key_test);
    // тесты для функции assoc_array_find
    tcase_add_test(tc_neg, assoc_array_find_null_number_pointer_test);
    tcase_add_test(tc_neg, assoc_array_find_fake_key_test);
    tcase_add_test(tc_neg, assoc_array_find_empty_string_key_test);
    // тесты для функции assoc_array_remove
    tcase_add_test(tc_neg, assoc_array_remove_fake_key_test);
    tcase_add_test(tc_neg, assoc_array_remove_empty_string_key_test);

    suite_add_tcase(s, tc_neg);

    return s;
}
