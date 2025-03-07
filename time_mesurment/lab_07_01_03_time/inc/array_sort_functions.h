#ifndef SORT_FUNCTIONS_H__

#define SORT_FUNCTIONS_H__

#include <stdio.h>
#include <math.h>

typedef int (*comparator)(const void *, const void *);

int key(int *src_array_start_pointer, int *src_array_end_pointer, int **dst_array_start_pointer, int **dst_array_end_pointer);
int mysort(void *array, size_t n, size_t elem_size, comparator cmp);

int int_cmp(const void *left, const void *right);
int double_cmp(const void *left, const void *right);
int char_cmp(const void *left, const void *right);

void swap(void *elem_1, void *elem_2, size_t elem_size);

#endif