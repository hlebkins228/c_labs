#ifndef POLYNOMIAL_FUNCTIONS_H__

#define POLYNOMIAL_FUNCTIONS_H__

#include "node.h"

double polynomial_value(node_t *polynomial_head, double x);
int polynomial_derivative(node_t *polynomial_head, node_t **derivative_head);
int polynomial_sum(node_t *first_polynomial_head, node_t *second_polynomial_head, node_t **result_polynomial_head);
int polynomial_split(node_t *src_polynomial_head, node_t **even_polynomial_head, node_t **odd_polynomial_head);

#endif
