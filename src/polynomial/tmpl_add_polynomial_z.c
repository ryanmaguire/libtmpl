

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_stdup function declared here.                                        */
#include <libtmpl/include/tmpl_string.h>

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc and calloc are found here.                                         */
#include <stdlib.h>

void
tmpl_PolynomialZ_Add(tmpl_PolynomialZ *P,
                     tmpl_PolynomialZ *Q,
                     tmpl_PolynomialZ *sum)
{
    /*  Declare a variable for indexing.                                      */
    unsigned long int n;

    /*  Two polynomial pointers for ordering the inputs in terms of degree.   */
    tmpl_PolynomialZ *first, *second;

    /*  Temporary variable used in case realloc is needed.                    */
    signed long int *tmp;

    /*  If sum is NULL, nothing can be done.                                  */
    if (sum == NULL)
        return;

    /*  If either P or Q are NULL, nothing can be done. Store an error        *
     *  message in sum.                                                       */
    if ((P == NULL) || (Q == NULL))
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Add\n\n"
            "One of the input polynomials is NULL. Aborting.\n"
        );
        return;
    }

    /*  If either P or Q has a NULL coeffs pointer, nothing can be done.      */
    if ((P->coeffs == NULL) || (Q->coeffs == NULL))
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Add\n\n"
            "One of the inputs has a NULL coeffs pointer. Aborting.\n"
        );
        return;
    }

    /*  Lastly, if one of the inputs has error_occurred set to true it may    *
     *  not be safe to proceed. Check for this.                               */
    if ((P->error_occurred) || (Q->error_occurred))
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Add\n\n"
            "One of the inputs has its error_occurred Boolean set to true.\n"
        );
        return;   
    }

    if (P->degree <= Q->degree)
    {
        first = P;
        second = Q;
    }
    else
    {
        first = Q;
        second = P;
    }

    /*  If the sum coeffs pointer is NULL, allocate memory for it.            */
    if (sum->coeffs == NULL)
    {
        sum->degree = second->degree;
        sum->coeffs = malloc(sizeof(*sum->coeffs) * sum->degree + 1UL);

        /*  Check if malloc failed.                                           */
        if (sum->coeffs == NULL)
        {
            sum->error_occurred = tmpl_True;
            sum->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Add\n\n"
                "malloc failed to allocate memory for sum->coeffs.\n"
            );
            return;  
        }
    }

    /*  If sum does not have the correct size for it's degree, reallocate     *
     *  the coeffs pointer to be the sum of the two others.                   */
    else if (sum->degree != second->degree)
    {
        sum->degree = second->degree;
        tmp = realloc(sum->coeffs, sizeof(*sum->coeffs) * sum->degree + 1UL);

        /*  Check if realloc failed.                                          */
        if (tmp == NULL)
        {
            sum->error_occurred = tmpl_True;
            sum->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Multiply\n\n"
                "realloc failed to allocate memory for sum->coeffs.\n"
            );
            return;
        }
        sum->coeffs = tmp;
    }

    for (n = 0UL; n <= first->degree; ++n)
        sum->coeffs[n] = first->coeffs[n] + second->coeffs[n];

    for (n = first->degree + 1UL; n <= second->degree; ++n)
        sum->coeffs[n] = second->coeffs[n];

    return;
}
