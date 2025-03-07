#ifndef SORT_FUNCTIONS_H__

#define SORT_FUNCTIONS_H__

#include "product.h"

int bubble_sort(struct product_t *products_array, size_t array_len);
void swap(struct product_t *product_1, struct product_t *product_2);
int comparator(struct product_t *product_1, struct product_t *product_2);

#endif