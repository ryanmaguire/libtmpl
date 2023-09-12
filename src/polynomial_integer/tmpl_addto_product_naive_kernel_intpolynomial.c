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
 *                tmpl_addto_product_naive_kernel_intpolynomial               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Multiply two polynomials with integer coefficients.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Multiply_Naive_Kernel                              *
 *  Purpose:                                                                  *
 *      Computes P += A*B where A*B is performed the naive way. This is used  *
 *      as a utility function for the more efficient Karatsuba algorithm.     *
 *  Arguments:                                                                *
 *      P (tmpl_IntPolynomial *):                                             *
 *          A pointer to a polynomial. The result is stored here.             *
 *      A (const tmpl_IntPolynomial *):                                       *
 *          A pointer to a polynomial.                                        *
 *      B (consttmpl_IntPolynomial *):                                        *
 *          Another pointer to a polynomial.                                  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      tmpl_polynomial_integer.h:                                            *
 *          tmpl_IntPolynomial_Multiply_Naive_Kernel:                         *
 *              Multiply two polynomials without error checking or shrinking. *
 *          tmpl_IntPolynomial_Shrink:                                        *
 *              Shrinks a polynomial by removing all terms past the largest   *
 *              non-zero coefficient.                                         *
 *      tmpl_string.h:                                                        *
 *          tmpl_String_Duplicate:                                            *
 *              Duplicates a string. Equivalent to the POSIX function strdup. *
 *  Method:                                                                   *
 *      Naive polynomial multiply is performed by using the distributive law. *
 *      The complexity is thus O(deg(P) * deg(Q)). That is, if we have:       *
 *                                                                            *
 *                   N                       M                                *
 *                 -----                   -----                              *
 *                 \          n            \          m                       *
 *          A(x) = /      a  x      B(x) = /      b  x                        *
 *                 -----   n               -----   m                          *
 *                 n = 0                   m = 0                              *
 *                                                                            *
 *      The product is defined by:                                            *
 *                                                                            *
 *                          N     M                                           *
 *                        ----- -----                                         *
 *                        \     \               n + m                         *
 *          A(x) * B(x) = /     /      a  * b  x                              *
 *                        ----- -----   n    m                                *
 *                        n = 0 m = 0                                         *
 *                                                                            *
 *      This is "rectangular" product. We can also compute the "diagonal"     *
 *      product using the Cauchy method.                                      *
 *                                                                            *
 *                        N + M   n                                           *
 *                        ----- -----                                         *
 *                        \     \                    n                        *
 *          A(x) * B(x) = /     /      a      *  b  x                         *
 *                        ----- -----   {n-m}     m                           *
 *                        n = 0 m = 0                                         *
 *                                                                            *
 *      Where we pad a_n and b_m with zeros for indices beyond deg(A) and     *
 *      deg(B), respectively. Since P has data already initialized, we add    *
 *      these values to the contents of P and return.                         *
 *  Notes:                                                                    *
 *      There are several possible ways for an error to occur.                *
 *          1.) The "prod" variable is NULL, or has error_occurred = true.    *
 *          2.) An input polynomial (P or Q) has error_occurred = true.       *
 *          3.) realloc fails to resize the coefficient array.                *
 *      One can safely handle all cases by inspecting "prod" after using this *
 *      function. First check if it is NULL, then if error_occurred = true.   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_string.h:                                                        *
 *          Header file where tmpl_String_Duplicate is declared.              *
 *  3.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 21, 2023                                                  *
 ******************************************************************************/

/*  realloc found here.                                                       */
#include <stdlib.h>

/*  Boolean given here.                                                       */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_String_Duplicate function provided here.                             */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Two algorithms, both O(n*m) where n and m are the degrees of P and Q,     *
 *  respectively, are provided. One is the "rectangular" method, and the      *
 *  other uses the diagonal Cauchy product method.                            *
 *      1 = Rectangle.                                                        *
 *      2 = Diagonal (Cauchy Product)                                         */
#ifndef TMPL_INTPOLY_MUL_ALG
#define TMPL_INTPOLY_MUL_ALG 2
#endif

/*  Rectangular method.                                                       */
#if TMPL_INTPOLY_MUL_ALG == 1

/*  Function for computing P += A*B for integer polynomials.                  */
void
tmpl_IntPolynomial_AddTo_Product_Naive_Kernel(tmpl_IntPolynomial *P,
                                              const tmpl_IntPolynomial *A,
                                              const tmpl_IntPolynomial *B)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t m, n;

    /*  The degree of the product is the sum of the two degrees.              */
    const size_t deg = A->degree + B->degree;

    /*  Useful constants cast to type "size_t".                               */
    const size_t zero = (size_t)0;
    const size_t one = (size_t)1;

    /*  Check if the output needs to be resized.                              */
    if (P->degree < deg)
    {
        /*  The number of elements is 1 plus degree (const terms included).   */
        const size_t len = deg + one;

        /*  Try to allocate memory for the output.                            */
        void *tmp = realloc(P->coeffs, sizeof(*P->coeffs)*len);

        /*  Check if realloc failed. Abort the computation if it did.         */
        if (!tmp)
        {
            P->error_occurred = tmpl_True;
            P->error_message = tmpl_String_Duplicate(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_AddTo_Product_Naive_Kernel\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }

        /*  Otherwise reset the coefficient pointer.                          */
        P->coeffs = tmp;

        /*  Initialize the new coefficients to zero so we can loop over them. */
        for (n = P->degree + one; n < len; ++n)
            P->coeffs[n] = 0;

        /*  Reset the degree to reflect the size of the new array.            */
        P->degree = deg;
    }

    /*  Perform the rectangular sum of the product.                           */
    for (m = zero; m <= A->degree; ++m)
        for (n = zero; n <= B->degree; ++n)
            P->coeffs[m + n] += A->coeffs[m] * B->coeffs[n];
}
/*  End of tmpl_IntPolynomial_Multiply_Naive.                                 */

#else
/*  Else for #if TMPL_INTPOLY_MUL_ALG == 1. Cauchy diagonal method below.     */

/*  Function for multiplying two polynomials.                                 */
void
tmpl_IntPolynomial_AddTo_Product_Naive_Kernel(tmpl_IntPolynomial *P,
                                              const tmpl_IntPolynomial *A,
                                              const tmpl_IntPolynomial *B)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t m, n;
    const tmpl_IntPolynomial *first, *second;

    /*  The degree of the product is the sum of the two degrees.              */
    const size_t deg = A->degree + B->degree;

    /*  Usefule constants cast to type "size_t".                              */
    const size_t zero = (size_t)0;
    const size_t one = (size_t)1;

    /*  Check if P needs to be resized.                                       */
    if (P->degree < deg)
    {
        /*  The number of elements is 1 plus degree (const terms included).   */
        const size_t len = deg + one;

        /*  Try to allocate memory for the product.                           */
        void *tmp = realloc(P->coeffs, sizeof(*P->coeffs)*len);

        /*  Check if realloc failed. Abort the computation if it did.         */
        if (!tmp)
        {
            P->error_occurred = tmpl_True;
            P->error_message = tmpl_String_Duplicate(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_AddTo_Product_Naive_Kernel\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }

        /*  Otherwise reset the coefficient pointer.                          */
        P->coeffs = tmp;

        /*  Initialize the new coefficients to zero so we can loop over them. */
        for (n = P->degree + one; n < len; ++n)
            P->coeffs[n] = 0;

        /*  Reset the degree to reflect the size of the new array.            */
        P->degree = deg;
    }

    /*  Sort the polynomials in terms of degree.                              */
    if (A->degree <= B->degree)
    {
        first = A;
        second = B;
    }
    else
    {
        first = B;
        second = A;
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
    for (n = zero; n < first->degree; ++n)
        for (m = zero; m <= n; ++m)
            P->coeffs[n] += first->coeffs[n - m] * second->coeffs[m];

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
        for (m = n - first->degree; m <= n; ++m)
            P->coeffs[n] += first->coeffs[n - m] * second->coeffs[m];

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
    for (n = second->degree; n <= P->degree; ++n)
        for (m = n - first->degree; m <= second->degree; ++m)
            P->coeffs[n] += first->coeffs[n - m] * second->coeffs[m];
}
/*  End of tmpl_IntPolynomial_Multiply_Naive.                                 */

#endif
/*  End of #if TMPL_INTPOLY_MUL_ALG == 1.                                     */
