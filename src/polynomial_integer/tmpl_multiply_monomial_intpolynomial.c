
#include <stdlib.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_string.h>
#include <libtmpl/include/tmpl_polynomial_integer.h>

void
tmpl_IntPolynomial_Multiply_Monomial(const tmpl_IntPolynomial *P, size_t deg,
                                     int coeff, tmpl_IntPolynomial *prod)
{
    if (!prod)
        return;

    if (prod->error_occurred)
        return;

    /*  If P is NULL set an error and return.                                 */
    if (!P)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Multiply_Monomial\n\n"
            "Input polynomial is NULL. Aborting.\n\n"
        );
        return;
    }

    /*  Similarly if P has an error set.                                      */
    if (P->error_occurred)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Multiply_Monomial\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n"
        );
        return;
    }

    /*  If the polynomial is empty there is nothing to scale.                 */
    if (!P->coeffs)
    {
        /*  Scaling by the empty polynomial should result in an empty         *
         *  polynomial. Avoid memory leaks, check if anything should be freed.*/
        if (prod->coeffs)
            free(prod->coeffs);

        /*  Set the product to the empty polynomial.                          */
        prod->coeffs = NULL;
        prod->degree = (size_t)0;
        return;
    }

    tmpl_IntPolynomial_Multiply_Monomial_Kernel(P, deg, coeff, prod);


}
