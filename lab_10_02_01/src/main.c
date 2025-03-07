#include "list.h"
#include "polynomial_funtcions.h"
#include "exitcodes.h"

#include <string.h>


int main(void)
{
    int rc = OK;

    char buffer[128];

    if (scanf("%s", buffer) != 1)
    {
        rc = INVALID_INPUT_ERROR;
    }
    else
    {
        buffer[4] = '\0';
    }

    node_t *list_head = NULL;
    double x = 0;
    
    if (rc == OK && !strcmp(buffer, "val"))
    {
        rc = list_input(&list_head);
        if (rc != OK)
        {
            return rc;
        }

        if (scanf("%lf", &x) != 1)
        {
            rc = INVALID_INPUT_ERROR;
        }
        else
        {
            double result = 0;
            
            result = polynomial_value(list_head, x);
            if (rc == OK)
            {
                printf("%lf\n", result);
            }
        }
    }
    else if (rc == OK && !strcmp(buffer, "ddx"))
    {
        rc = list_input(&list_head);
        if (rc != OK)
        {
            return rc;
        }
        
        node_t *derivative_head = NULL;
        rc = polynomial_derivative(list_head, &derivative_head);
        if (rc == OK)
        {
            list_print(derivative_head);
        }

        list_free(derivative_head);
    }
    else if (rc == OK && !strcmp(buffer, "sum"))
    {
        rc = list_input(&list_head);
        if (rc != OK)
        {
            return rc;
        }

        node_t *second_list_head = NULL;

        rc = list_input(&second_list_head);
        if (rc != OK)
        {
            list_free(list_head);

            return rc;
        }

        node_t *result_list_head = NULL;
        rc = polynomial_sum(list_head, second_list_head, &result_list_head);
        if (rc == OK)
        {
            list_print(result_list_head);
        }

        list_free(second_list_head);
        list_free(result_list_head);
    }
    else if (rc == OK && !strcmp(buffer, "dvd"))
    {
        rc = list_input(&list_head);
        if (rc != OK)
        {
            return rc;
        }
    
        node_t *even_list_head = NULL;
        node_t *odd_list_head = NULL;
        rc = polynomial_split(list_head, &even_list_head, &odd_list_head);
        if (rc == OK)
        {
            list_print(even_list_head);
            list_print(odd_list_head);
        }

        list_free(even_list_head);
        list_free(odd_list_head);
    }
    else if (rc == OK)
    {
        rc = INVALID_ACTION_ERROR;
    }

    list_free(list_head);

    return rc;
}
