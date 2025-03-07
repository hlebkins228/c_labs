#ifndef FUNC_CHECK_H__

#define FUNC_CHECK_H__

#include <stdlib.h>
#include <stdio.h>
#include <check.h>

int matrix_compare(int **matrix_a, int **matrix_b, size_t n, size_t m);
Suite* unit_tests_suite(void);

#endif