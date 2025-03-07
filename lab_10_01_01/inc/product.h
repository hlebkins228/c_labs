#ifndef PRODUCT_H__

#define PRODUCT_H__

#include <stdio.h>

typedef struct product product_t;

struct product
{
    char *name;
    double weight;
    double volume;
};

int product_read_from_file(FILE *file, product_t **product_pointer);
int product_init_content(product_t *product_pointer, const char *title, double weight, double volume);
void product_print_content(void *data);
void product_free_content(product_t *product_pointer);

int get_products_count(FILE *file, size_t *array_len);
int products_array_memory_alloc(FILE *file, void ***products_array, size_t *array_len);
int products_read_to_array(FILE *file, void **products_array, size_t array_len);
void products_array_free(void **products_array, size_t array_len);

#endif
