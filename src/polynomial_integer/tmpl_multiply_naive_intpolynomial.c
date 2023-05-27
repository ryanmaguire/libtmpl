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
 *                      tmpl_multiply_naive_intpolynomial                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Multiply two polynomials with integer coefficients.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Multiply_Naive                                     *
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
 *      tmpl_polynomial_integer.h:                                            *
 *          tmpl_IntPolynomial_Multiply_Naive_Kernel:                         *
 *              Multiply two polynomials without error checking or shrinking. *
 *          tmpl_IntPolynomial_Make_Zero:                                     *
 *              Converts a polynomial into the zero polynomial.               *
 *          tmpl_IntPolynomial_Shrink:                                        *
 *              Shrinks a polynomial by removing all terms past the largest   *
 *              non-zero coefficient.                                         *
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

/*  Boolean given here.                                                       */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup function provided here.                                       */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for multiplying two polynomials.                                 */
void
tmpl_IntPolynomial_Multiply_Naive(const tmpl_IntPolynomial *P,
                                  const tmpl_IntPolynomial *Q,
                                  tmpl_IntPolynomial *prod)
{
    /*  If the output pointer is NULL there's nothing to be done.             */
    if (!prod)
        return;

    /*  If an error occurred before this function was called, abort.          */
    if (prod->error_occurred)
        return;

    /*  Treat NULL polynomials as zero. Product with a zero polyomial is zero.*/
    if (!P || !Q)
    {
        tmpl_IntPolynomial_Make_Zero(prod);
        return;
    }

    /*  Similarly if either P or Q have an error.                             */
    if (P->error_occurred || Q->error_occurred)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Multiply_Naive\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n"
        );

        return;
    }

    /*  If either polynomial is empty return zero.                            */
    if (!P->coeffs || !Q->coeffs)
    {
        tmpl_IntPolynomial_Make_Zero(prod);
        return;
    }

    /*  Multiply the polynomials using the classical algorithm.               */
    tmpl_IntPolynomial_Multiply_Naive_Kernel(P, Q, prod);

    /*  Shrink the result by removing redundant terms.                        */
    tmpl_IntPolynomial_Shrink(prod);
}
/*  End of tmpl_IntPolynomial_Multiply_Naive.                                 */
