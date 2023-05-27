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
 *                  tmpl_multiply_naive_kernel_intpolynomial                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Multiply two polynomials with integer coefficients.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Multiply_Naive_Kernel                              *
 *  Purpose:                                                                  *
 *      Computes the product of two polynomials over Z[x] with 'int'          *
 *      coefficients. That is, given polynomials P, Q in Z[x], computes P * Q.*
 *      The naive / classical algorithm is used that is O(deg(P)*deg(Q)) in   *
 *      complexity. For large degree polynomials the Karatsuba and FFT        *
 *      algorithms are much more efficient.                                   *
 *  Arguments:                                                                *
 *      P (const tmpl_IntPolynomial *):                                       *
 *          A pointer to a polynomial.                                        *
 *      Q (const tmpl_IntPolynomial *):                                       *
 *          Another pointer to a polynomial.                                  *
 *      prod (tmpl_IntPolynomial *):                                          *
 *          A pointer to a polynomial. The product is stored here.            *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          realloc:                                                          *
 *              Resizes an array.                                             *
 *      tmpl_string.h:                                                        *
 *          tmpl_strdup:                                                      *
 *              Duplicates a string. Equivalent to the POSIX function strdup. *
 *  Method:                                                                   *
 *      Naive polynomial multiply is performed by using the distributive law. *
 *      The complexity is thus O(deg(P) * deg(Q)). That is, if we have:       *
 *                                                                            *
 *                   N                       M                                *
 *                 -----                   -----                              *
 *                 \          n            \          m                       *
 *          P(x) = /      a  x      Q(x) = /      b  x                        *
 *                 -----   n               -----   m                          *
 *                 n = 0                   m = 0                              *
 *                                                                            *
 *      The product is defined by:                                            *
 *                                                                            *
 *                          N     M                                           *
 *                        ----- -----                                         *
 *                        \     \               n + m                         *
 *          P(x) * Q(x) = /     /      a  * b  x                              *
 *                        ----- -----   n    m                                *
 *                        n = 0 m = 0                                         *
 *                                                                            *
 *      This is "rectangular" product. We can also compute the "diagonal"     *
 *      product using the Cauchy method.                                      *
 *                                                                            *
 *                        N + M   n                                           *
 *                        ----- -----                                         *
 *                        \     \                    n                        *
 *          P(x) * Q(x) = /     /      a      *  b  x                         *
 *                        ----- -----   {n-m}     m                           *
 *                        n = 0 m = 0                                         *
 *                                                                            *
 *      Where we pad a_n and b_m with zeros for indices beyond deg(P) and     *
 *      deg(Q), respectively.                                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_string.h:                                                        *
 *          Header file where tmpl_strdup is declared.                        *
 *  3.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 8, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/05/19: Ryan Maguire                                                  *
 *      Added doc-string and comments.                                        *
 *  2023/05/19: Ryan Maguire                                                  *
 *      Changed behavior so that a NULL product is treated as zero.           *
 ******************************************************************************/

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
tmpl_IntPolynomial_Multiply_Naive_Kernel(const tmpl_IntPolynomial *P,
                                         const tmpl_IntPolynomial *Q,
                                         tmpl_IntPolynomial *prod)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t m, n;

    /*  The degree of the product is the sum of the two degrees.              */
    const size_t deg = P->degree + Q->degree;

    /*  Check if prod needs to be resized.                                    */
    if (prod->degree != deg)
    {
        /*  The number of elements is 1 plus degree (const terms included).   */
        const size_t len = deg + (size_t)1;

        /*  Try to allocate memory for the product.                           */
        void *tmp = realloc(prod->coeffs, sizeof(*prod->coeffs)*len);

        /*  Check if realloc failed. Abort the computation if it did.         */
        if (!tmp)
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Multiply_Naive_Kernel\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }

        /*  Otherwise reset the coefficient pointer.                          */
        prod->coeffs = tmp;
        prod->degree = deg;
    }

    /*  Initialize all of the coefficients to zero so we can loop over them.  */
    for (n = (size_t)0; n <= prod->degree; ++n)
        prod->coeffs[n] = 0;

    /*  Perform the rectangular sum of the product.                           */
    for (m = (size_t)0; m <= P->degree; ++m)
        for (n = (size_t)0; n <= Q->degree; ++n)
            prod->coeffs[m + n] += P->coeffs[m] * Q->coeffs[n];
}
/*  End of tmpl_IntPolynomial_Multiply_Naive.                                 */

#else
/*  Else for #if TMPL_INTPOLY_MUL_ALG == 1. Cauchy diagonal method below.     */

/*  Function for multiplying two polynomials.                                 */
void
tmpl_IntPolynomial_Multiply_Naive_Kernel(const tmpl_IntPolynomial *P,
                                         const tmpl_IntPolynomial *Q,
                                         tmpl_IntPolynomial *prod)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t m, n;
    const tmpl_IntPolynomial *first, *second;

    /*  The degree of the product is the sum of the two degrees.              */
    const size_t deg = P->degree + Q->degree;

    /*  Check if prod needs to be resized.                                    */
    if (prod->degree != deg)
    {
        /*  The number of elements is 1 plus degree (const terms included).   */
        const size_t len = deg + (size_t)1;

        /*  Try to allocate memory for the product.                           */
        void *tmp = realloc(prod->coeffs, sizeof(*prod->coeffs)*len);

        /*  Check if realloc failed. Abort the computation if it did.         */
        if (!tmp)
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Multiply_Naive_Kernel\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }

        /*  Otherwise reset the coefficient pointer.                          */
        prod->coeffs = tmp;
        prod->degree = deg;
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

    /*  First part of the Cauchy product.                                     *
     *                                                                        *
     *      |-----------------------|                                         *
     *    2 |   |   |   |   |   |   |                                         *
     *      |-----------------------|                                         *
     *    1 | x |   |   |   |   |   |                                         *
     *      |-----------------------|                                         *
     *    0 | x | x |   |   |   |   |                                         *
     *      |-----------------------|                                         *
     *        0   1   2   3   4   5                                           *
     *                                                                        */
    for (n = (size_t)0; n < first->degree; ++n)
    {
        prod->coeffs[n] = first->coeffs[n] * second->coeffs[0];

        for (m = (size_t)1; m <= n; ++m)
            prod->coeffs[n] += first->coeffs[n - m] * second->coeffs[m];
    }

    /*  Second part of the Cauchy product.                                    *
     *                                                                        *
     *      |-----------------------|                                         *
     *    2 | x | x | x |   |   |   |                                         *
     *      |-----------------------|                                         *
     *    1 |   | x | x | x |   |   |                                         *
     *      |-----------------------|                                         *
     *    0 |   |   | x | x | x |   |                                         *
     *      |-----------------------|                                         *
     *        0   1   2   3   4   5                                           *
     *                                                                        */
    for (n = first->degree; n < second->degree; ++n)
    {
        m = n - first->degree;
        prod->coeffs[n] = first->coeffs[n - m] * second->coeffs[m];

        for (m = m + (size_t)1; m <= n; ++m)
            prod->coeffs[n] += first->coeffs[n-m] * second->coeffs[m];
    }

    /*  Third part of the Cauchy product.                                     *
     *                                                                        *
     *      |-----------------------|                                         *
     *    2 |   |   |   | x | x | x |                                         *
     *      |-----------------------|                                         *
     *    1 |   |   |   |   | x | x |                                         *
     *      |-----------------------|                                         *
     *    0 |   |   |   |   |   | x |                                         *
     *      |-----------------------|                                         *
     *        0   1   2   3   4   5                                           *
     *                                                                        */
    for (n = second->degree; n <= prod->degree; ++n)
    {
        m = n - first->degree;
        prod->coeffs[n] = first->coeffs[n - m] * second->coeffs[m];

        for (m = m + (size_t)1; m <= second->degree; ++m)
            prod->coeffs[n] += first->coeffs[n-m] * second->coeffs[m];
    }
}
/*  End of tmpl_IntPolynomial_Multiply_Naive.                                 */

#endif
/*  End of #if TMPL_INTPOLY_MUL_ALG == 1.                                     */
