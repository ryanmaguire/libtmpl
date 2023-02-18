/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 8, 2023                                              *
 ******************************************************************************/

/*  TODO: Add "doc-string" above, description of function, etc.               */

/*  realloc found here.                                                       */
#include <stdlib.h>

/*  Boolean given here.                                                       */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup function provided here.                                       */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Two algorithms, both O(n*m) where n and m are the degrees of P and Q,     *
 *  respectively, are provided. One is the "rectangular" method, and the      *
 *  other uses the diagonal Cauchy product method. The Cauchy product has     *
 *  the benefit of requiring fewer initializations and additions.             *
 *      1 = Rectangle.                                                        *
 *      2 = Diagonal (Cauchy Product)                                         */
#ifndef TMPL_INTPOLY_MUL_ALG
#define TMPL_INTPOLY_MUL_ALG 2
#endif

/*  Rectangular method.                                                       */
#if TMPL_INTPOLY_MUL_ALG == 1

/*  Function for multiplying two polynomials.                                 */
void
tmpl_IntPolynomial_Naive_Multiply(const tmpl_IntPolynomial *P,
                                  const tmpl_IntPolynomial *Q,
                                  tmpl_IntPolynomial *prod)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t m, n;

    /*  If the output pointer is NULL there's nothing to be done.             */
    if (!prod)
        return;

    /*  If an error occurred before this function was called, abort.          */
    if (prod->error_occurred)
        return;

    /*  If either P or Q are NULL, set an error and return.                   */
    if (!P || !Q)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Multiply\n\n"
            "Input polynomial is NULL. Aborting.\n\n"
        );
        return;
    }

    /*  Similarly if either P or Q have an error.                             */
    if (P->error_occurred || Q->error_occurred)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Naive_Multiply\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n"
        );
        return;
    }

    /*  Check if prod needs to be resized.                                    */
    if (prod->degree != P->degree + Q->degree)
    {
        /*  The degree of the product is the sum of the two degrees.          */
        const size_t deg = P->degree + Q->degree;

        /*  The number of elements is 1 plus degree (const terms included).   */
        const size_t len = deg + (size_t)1;

        /*  Try to allocate memory for the product.                           */
        void *tmp = realloc(prod->coeffs, sizeof(*prod->coeffs)*len);

        /*  If realloc succeeds, reset the pointer.                           */
        if (tmp)
        {
            prod->coeffs = tmp;
            prod->degree = deg;
        }

        /*  Otherwise abort with an error.                                    */
        else
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Naive_Multiply\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }
    }

    /*  Initialize all of the coefficients to zero so we can loop over them.  */
    for (n = (size_t)0; n <= prod->degree; ++n)
        prod->coeffs[n] = 0;

    /*  Perform the rectangular sum of the product.                           */
    for (m = (size_t)0; m <= P->degree; ++m)
        for (n = (size_t)0; n <= Q->degree; ++n)
            prod->coeffs[m + n] += P->coeffs[m] * Q->coeffs[n];

    tmpl_IntPolynomial_Shrink(prod);
}
/*  End of tmpl_IntPolynomial_Naive_Multiply.                                 */

#else
/*  Else for #if TMPL_INTPOLY_MUL_ALG == 1. Cauchy diagonal method below.     */

void
tmpl_IntPolynomial_Naive_Multiply(const tmpl_IntPolynomial *P,
                                  const tmpl_IntPolynomial *Q,
                                  tmpl_IntPolynomial *prod)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t m, n;
    const tmpl_IntPolynomial *first, *second;

    /*  If the output pointer is NULL there's nothing to be done.             */
    if (!prod)
        return;

    /*  If an error occurred before this function was called, abort.          */
    if (prod->error_occurred)
        return;

    /*  If either P or Q are NULL, set an error and return.                   */
    if (!P || !Q)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Multiply\n\n"
            "Input polynomial is NULL. Aborting.\n\n"
        );
        return;
    }

    /*  Similarly if either P or Q have an error.                             */
    if (P->error_occurred || Q->error_occurred)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Naive_Multiply\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n"
        );
        return;
    }

    /*  Check if prod needs to be resized.                                    */
    if (prod->degree != P->degree + Q->degree)
    {
        /*  The degree of the product is the sum of the two degrees.          */
        const size_t deg = P->degree + Q->degree;

        /*  The number of elements is 1 plus degree (const terms included).   */
        const size_t len = deg + (size_t)1;

        /*  Try to allocate memory for the product.                           */
        void *tmp = realloc(prod->coeffs, sizeof(*prod->coeffs)*len);

        /*  If realloc succeeds, reset the pointer.                           */
        if (tmp)
        {
            prod->coeffs = tmp;
            prod->degree = deg;
        }

        /*  Otherwise abort with an error.                                    */
        else
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Naive_Multiply\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }
    }

    /*  Sort the polynomials in terms of degree.                              */
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

    /*  Perform the Cauchy product on P and Q.                                */
    for (n = (size_t)0; n < first->degree; ++n)
    {
        prod->coeffs[n] = first->coeffs[n] * second->coeffs[0];
        for (m = (size_t)1; m <= n; ++m)
            prod->coeffs[n] += first->coeffs[n-m] * second->coeffs[m];
    }

    for (n = first->degree; n < second->degree; ++n)
    {
        prod->coeffs[n] = (size_t)0;
        for (m = n - first->degree; m <= n; ++m)
            prod->coeffs[n] += first->coeffs[n-m] * second->coeffs[m];
    }

    for (n = second->degree; n <= prod->degree; ++n)
    {
        prod->coeffs[n] = (size_t)0;
        for (m = n - first->degree; m <= second->degree; ++m)
            prod->coeffs[n] += first->coeffs[n-m] * second->coeffs[m];
    }

    tmpl_IntPolynomial_Shrink(prod);
}
/*  End of tmpl_IntPolynomial_Naive_Multiply.                                 */

#endif
/*  End of #if TMPL_INTPOLY_MUL_ALG == 1.                                     */
