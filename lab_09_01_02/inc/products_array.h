#ifndef PRODUCTS_ARRAY__

#define PRODUCTS_ARRAY__

#include <stdio.h>
#include "product.h"

int get_products_count(FILE *file, size_t *array_len);
int products_array_memory_alloc(FILE *file, struct product_t **products_array, size_t *array_len);
int products_read_to_array(FILE *file, struct product_t *products_array, size_t array_len);
void products_array_print(struct product_t *products_array, size_t array_len);
int products_array_free(struct product_t *products_array, size_t array_len);
int print_special_products(struct product_t *products_array, size_t array_len, char *substring);

#endif