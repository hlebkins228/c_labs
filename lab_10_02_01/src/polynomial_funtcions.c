#include "list.h"
#include "polynomial_funtcions.h"
#include "exitcodes.h"

#include <math.h>
#include <stdio.h>

static int polynomial_add_members(node_t **first_src_polynomial, node_t **second_src_polynomial, node_t **dst_polynomial);
static int polynomial_add_tail(node_t *src_polynomial, node_t **dst_polynomial);


double polynomial_value(node_t *polynomial_head, double x)
{
    double result = 0;

    for (node_t *current_node = polynomial_head; current_node != NULL; current_node = current_node->next)
    {
        result += current_node->k * pow(x, current_node->power);
    }

    return result;
}


int polynomial_derivative(node_t *polynomial_head, node_t **derivative_head)
{
    if (polynomial_head == NULL)
    {
        return FUNC_ARGS_ERROR;
    }
    
    node_t *new_node = NULL;
    node_t *temp_derivative_head = NULL;

    for (node_t *current_node = polynomial_head; current_node != NULL; current_node = current_node->next)
    {
        if (current_node->power > 0)
        {
            new_node = node_create(current_node->power - 1, current_node->power * current_node->k);
            if (!new_node)
            {
                list_free(temp_derivative_head);

                return MEMORY_ERROR;
            }

            temp_derivative_head = list_add_tail(temp_derivative_head, new_node);
        }
    }

    *derivative_head = temp_derivative_head;

    return OK;
}


int polynomial_sum(node_t *first_polynomial_head, node_t *second_polynomial_head, node_t **result_polynomial_head)
{
    int rc = OK;
    
    node_t *first_current_node = first_polynomial_head;
    node_t *second_current_node = second_polynomial_head;
    node_t *temp_result_polynomial_head = NULL;

    while (rc == OK && (first_current_node != NULL && second_current_node != NULL))
    {
        if (first_current_node->power >= second_current_node->power)
        {
            rc = polynomial_add_members(&first_current_node, &second_current_node, &temp_result_polynomial_head);
        }
        else if (first_current_node->power < second_current_node->power)
        {
            rc = polynomial_add_members(&second_current_node, &first_current_node, &temp_result_polynomial_head);
        }
    }

    if (rc == OK)
    {
        if (first_current_node == NULL && second_current_node != NULL)
        {
            rc = polynomial_add_tail(second_current_node, &temp_result_polynomial_head);
        }
        else if (second_current_node == NULL && first_current_node != NULL)
        {
            rc = polynomial_add_tail(first_current_node, &temp_result_polynomial_head);
        }
    }

    if (rc == OK)
    {
        *result_polynomial_head = temp_result_polynomial_head;
    }
    else
    {
        list_free(temp_result_polynomial_head);
    }

    return rc;
}


// вспомогательная функция для polynomial_sum
static int polynomial_add_members(node_t **first_src_polynomial, node_t **second_src_polynomial, node_t **dst_polynomial)
{
    node_t *new_node = NULL;
    
    while (*first_src_polynomial != NULL && ((*first_src_polynomial)->power > (*second_src_polynomial)->power))
    {
        new_node = node_create((*first_src_polynomial)->power, (*first_src_polynomial)->k);
        if (!new_node)
        {
            list_free(*dst_polynomial);

            return MEMORY_ERROR;
        }

        *dst_polynomial = list_add_tail(*dst_polynomial, new_node);

        *first_src_polynomial = (*first_src_polynomial)->next;
    }

    if (*first_src_polynomial != NULL && ((*first_src_polynomial)->power == (*second_src_polynomial)->power))
    {
        new_node = node_create((*first_src_polynomial)->power, (*first_src_polynomial)->k + (*second_src_polynomial)->k);
        if (!new_node)
        {
            list_free(*dst_polynomial);
                
            return MEMORY_ERROR;
        }
        
        *dst_polynomial = list_add_tail(*dst_polynomial, new_node);

        *first_src_polynomial = (*first_src_polynomial)->next;
        *second_src_polynomial = (*second_src_polynomial)->next;
    }

    return OK;
}


// еще одна вспомогательная функция для polynomial_sum
static int polynomial_add_tail(node_t *src_polynomial, node_t **dst_polynomial)
{
    node_t *new_node = NULL;
    node_t *temp_tail = NULL;
    
    for (node_t *current_node = src_polynomial; current_node != NULL; current_node = current_node->next)
    {
        new_node = node_create(current_node->power, current_node->k);
        if (!new_node)
        {
            list_free(temp_tail);
            
            return MEMORY_ERROR;
        }

        temp_tail = list_add_tail(temp_tail, new_node);
    }

    *dst_polynomial = list_add_tail(*dst_polynomial, temp_tail);

    return OK;
}


// функция разделяет многочлен на полиномы четных и нечетных степеней
int polynomial_split(node_t *src_polynomial_head, node_t **even_polynomial_head, node_t **odd_polynomial_head)
{
    node_t *new_node = NULL;
    node_t *temp_even_polynomial_head = NULL;
    node_t *temp_odd_polynomial_head = NULL;

    for (node_t *current_node = src_polynomial_head; current_node != NULL; current_node = current_node->next)
    {
        new_node = node_create(current_node->power, current_node->k);
        if (!new_node)
        {
            list_free(temp_odd_polynomial_head);
            list_free(temp_even_polynomial_head);
                
            return MEMORY_ERROR;
        }

        if (current_node->power % 2 == 0)
        {
            temp_even_polynomial_head = list_add_tail(temp_even_polynomial_head, new_node);
        }
        else
        {
            temp_odd_polynomial_head = list_add_tail(temp_odd_polynomial_head, new_node);
        }
    }

    *even_polynomial_head = temp_even_polynomial_head;
    *odd_polynomial_head = temp_odd_polynomial_head;

    return OK;
}
