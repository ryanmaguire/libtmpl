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
 *                   tmpl_addto_product_naive_intpolynomial                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs the operation P += A*B for polynomials A, B, and P.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_AddTo_Product_Naive                                *
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
 *          tmpl_IntPolynomial_AddTo_Product_Naive_Kernel:                    *
 *              Performs P += A*B without error checking or shrinking.        *
 *          tmpl_IntPolynomial_Shrink:                                        *
 *              Shrinks a polynomial by removing all terms past the largest   *
 *              non-zero coefficient.                                         *
 *      tmpl_string.h:                                                        *
 *          tmpl_String_Duplicate:                                            *
 *              Duplicates a string. Equivalent to the POSIX function strdup. *
 *  Method:                                                                   *
 *      Naive polynomial multiplication is performed using the distributive   *
 *      law. The complexity is thus O(deg(P) * deg(Q)). That is, if we have:  *
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
 *          1.) The "P" variable is NULL, or has error_occurred = true.       *
 *          2.) An input polynomial (A or B) has error_occurred = true.       *
 *          3.) realloc fails to resize the coefficient array.                *
 *      One can safely handle all cases by inspecting "P" after using this    *
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

/*  Boolean given here.                                                       */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_String_Duplicate function provided here.                             */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for computing P += A*B for integer polynomials.                  */
void
tmpl_IntPolynomial_AddTo_Product_Naive(tmpl_IntPolynomial *P,
                                       const tmpl_IntPolynomial *A,
                                       const tmpl_IntPolynomial *B)
{
    /*  If the output pointer is NULL there's nothing to be done.             */
    if (!P)
        return;

    /*  If an error occurred before this function was called, abort.          */
    if (P->error_occurred)
        return;

    /*  Treat NULL polynomials as zero. Product with a zero polyomial is zero.*/
    if (!A || !B)
        return;

    /*  Abort if either P or Q have an error.                                 */
    if (A->error_occurred || B->error_occurred)
    {
        P->error_occurred = tmpl_True;
        P->error_message = tmpl_String_Duplicate(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_AddTo_Product_Naive\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n"
        );

        return;
    }

    /*  If either polynomial is empty do nothing. P + 0 = P.                  */
    if (!A->coeffs || !B->coeffs)
        return;

    /*  Multiply the polynomials using the classical algorithm.               */
    tmpl_IntPolynomial_AddTo_Product_Naive_Kernel(P, A, B);

    /*  Shrink the result by removing redundant terms.                        */
    tmpl_IntPolynomial_Shrink(P);
}
/*  End of tmpl_IntPolynomial_AddTo_Product_Naive.                            */
