#ifndef PRODUCT_H__

#define PRODUCT_H__

#include <stdio.h>

struct product_t
{
    char *name;
    double weight;
    double volume;
};

int product_read_from_file(FILE *file, struct product_t *product_pointer);
int product_init_content(struct product_t *product_pointer, const char *title, double weight, double volume);
void product_print_content(struct product_t *product_pointer);
void product_free_content(struct product_t *product_pointer);

#endif


