
#include <stdlib.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_string.h>
#include <libtmpl/include/tmpl_polynomial_integer.h>

void
tmpl_IntPolynomial_Multiply_Monomial(const tmpl_IntPolynomial *poly, size_t deg,
                                     int coeff, tmpl_IntPolynomial *prod)
{
    if (!prod)
        return;

    if (prod->error_occurred)
        return;

    /*  If poly is NULL set an error and return.                              */
    if (!poly)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Multiply_Monomial\n\n"
            "Input polynomial is NULL. Aborting.\n\n"
        );
        return;
    }

    /*  Similarly if poly has an error set.                                   */
    if (poly->error_occurred)
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
    if (!poly->coeffs)
    {
        tmpl_IntPolynomial_Make_Empty(prod);
        return;
    }

    /*  If the coefficient is zero the result is the zero polynomial.         */
    if (coeff == 0)
    {
        tmpl_IntPolynomial_Make_Zero(prod);
        return;
    }

    /*  Legal inputs, use the kernel function to perform the main computation.*/
    tmpl_IntPolynomial_Multiply_Monomial_Kernel(poly, deg, coeff, prod);
}
/*  End of tmpl_IntPolynomial_Multiply_Monomial.                              */
