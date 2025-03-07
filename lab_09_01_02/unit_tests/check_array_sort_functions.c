#include "func_check.h"
#include "array_sort_functions.h"
#include "exitcodes.h"


// позитивные тесты для функции bubble_sort

// обычный тест
START_TEST(common_bubble_sort_test)
{
    int rc;
    char *string = "string";
    size_t array_len = 5;

    struct product_t src_array[5];

    src_array[0].name = string;
    src_array[0].weight = 10;
    src_array[0].volume = 20;
    
    src_array[1].name = string;
    src_array[1].weight = 14;
    src_array[1].volume = 5;
    
    src_array[2].name = string;
    src_array[2].weight = 14.64;
    src_array[2].volume = 1.11;

    src_array[3].name = string;
    src_array[3].weight = 43.23;
    src_array[3].volume = 60.9932;

    src_array[4].name = string;
    src_array[4].weight = 14;
    src_array[4].volume = 5;


    struct product_t dst_array[5];

    dst_array[0].name = string;
    dst_array[0].weight = 10;
    dst_array[0].volume = 20;

    dst_array[1].name = string;
    dst_array[1].weight = 43.23;
    dst_array[1].volume = 60.9932;
    
    dst_array[2].name = string;
    dst_array[2].weight = 14;
    dst_array[2].volume = 5;

    dst_array[3].name = string;
    dst_array[3].weight = 14;
    dst_array[3].volume = 5;

    dst_array[4].name = string;
    dst_array[4].weight = 14.64;
    dst_array[4].volume = 1.11;


    rc = bubble_sort(src_array, array_len);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(memcmp(src_array, dst_array, array_len * sizeof(struct product_t)), 0);
}
END_TEST


// негативные тесты для функции bubble_sort

// нулевой указатель вместо массива
START_TEST(array_null_pointer_test)
{
    int rc;
    
    size_t array_len = 6;
    struct product_t *array = NULL;
    rc = bubble_sort(array, array_len);
    
    ck_assert_int_eq(rc, INVALID_FUNC_ARGS_ERROR);
}
END_TEST


// нулевой размер массива
START_TEST(zero_array_len_test)
{
    int rc;
    
    size_t array_len = 0;
    struct product_t array[6];
    rc = bubble_sort(array, array_len);
    
    ck_assert_int_eq(rc, INVALID_FUNC_ARGS_ERROR);
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

    // тесты для функции bubble_sort
    tcase_add_test(tc_pos, common_bubble_sort_test);
    
    suite_add_tcase(s, tc_pos);

    // НЕГАТИВНЫЕ ТЕСТЫ

    tc_neg = tcase_create("negatives");

    // тесты для функции bubble_sort
    tcase_add_test(tc_neg, array_null_pointer_test);
    tcase_add_test(tc_neg, zero_array_len_test);

    suite_add_tcase(s, tc_neg);

    return s;
}