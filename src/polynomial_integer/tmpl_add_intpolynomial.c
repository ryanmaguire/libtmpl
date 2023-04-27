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
 *                           tmpl_add_intpolynomial                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds two polynomials with integer coefficients.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Add                                                *
 *  Purpose:                                                                  *
 *      Computes the sum of two polynomials over Z[x] with 'int' coefficients.*
 *      That is, given polynomials P, Q in Z[x], computes P + Q.              *
 *  Arguments:                                                                *
 *      P (const tmpl_IntPolynomial *):                                       *
 *          A pointer to a polynomial.                                        *
 *      Q (const tmpl_IntPolynomial *):                                       *
 *          Another pointer to a polynomial.                                  *
 *      sum (tmpl_IntPolynomial *):                                           *
 *          A pointer to a polynomial. The sum is stored here.                *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      tmpl_IntPolynomial_Add_Kernel (tmpl_polynomial_int.h):                *
 *          Adds two polynomials without error checking or shrinking.         *
 *      tmpl_IntPolynomial_Shrink (tmpl_polynomial_int.h):                    *
 *          Shrinks a polynomial by removing all terms past the largest       *
 *          non-zero coefficient.                                             *
 *      tmpl_strdup (tmpl_string.h):                                          *
 *          Duplicates a string. Equivalent to the POSIX function strdup.     *
 *  Method:                                                                   *
 *      Polynomial addition is performed term-by-term. The complexity is thus *
 *      O(max(deg(P), deg(Q)). That is, if we have:                           *
 *                                                                            *
 *                   N                       M                                *
 *                 -----                   -----                              *
 *                 \          n            \          m                       *
 *          P(x) = /      a  x      Q(x) = /      b  x                        *
 *                 -----   n               -----   m                          *
 *                 n = 0                   m = 0                              *
 *                                                                            *
 *      The sum is defined by:                                                *
 *                                                                            *
 *                          K                                                 *
 *                        -----                                               *
 *                        \                 k                                 *
 *          P(x) + Q(x) = /      (a  + b ) x                                  *
 *                        -----    k    k                                     *
 *                        k = 0                                               *
 *                                                                            *
 *      Where K = max(N, M) and we pad either a_k or b_k with zeros to make   *
 *      the terms valid. We perform this by computing the sum a_k + b_k for   *
 *      0 <= k <= min(N, M) and then copy the coefficients of the larger      *
 *      degree polynomial for min(N, M) < k <= max(N, M).                     *
 *  Notes:                                                                    *
 *      There are several possible ways for an error to occur.                *
 *          1.) The "sum" variable is NULL, or has error_occurred = true.     *
 *          2.) An input polynomial (P or Q) is NULL.                         *
 *          3.) An input polynomial (P or Q) has error_occurred = true.       *
 *          4.) realloc fails to resize the coefficient array.                *
 *      One can safely handle all cases by inspecting "sum" after using this  *
 *      function. First check if it is NULL, then if error_occurred = true.   *
 *                                                                            *
 *      It does not matter if P = Q, P = sum, or if Q = sum. realloc does not *
 *      overwrite data when enlarging an array. However it is faster to call  *
 *      tmpl_IntPolynomial_Scale when P = Q or tmpl_IntPolynomial_AddTo when  *
 *      P = sum or Q = sum.                                                   *
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
 *  2023/04/25: Ryan Maguire                                                  *
 *      Added doc-string and comments.                                        *
 ******************************************************************************/

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup function provided here.                                       */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for adding two polynomials over Z[x].                            */
void
tmpl_IntPolynomial_Add(const tmpl_IntPolynomial *P,
                       const tmpl_IntPolynomial *Q,
                       tmpl_IntPolynomial *sum)
{
    /*  If the output pointer is NULL there's nothing to be done.             */
    if (!sum)
        return;

    /*  If an error occurred before this function was called, abort.          */
    if (sum->error_occurred)
        return;

    /*  If either P or Q are NULL, set an error and return.                   */
    if (!P || !Q)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Add\n\n"
            "Input polynomial is NULL. Aborting.\n\n"
        );
        return;
    }

    /*  Similarly if either P or Q have an error.                             */
    if (P->error_occurred || Q->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Add\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n"
        );
        return;
    }

    /*  Add the polynomials and store the result in sum.                      */
    tmpl_IntPolynomial_Add_Kernel(P, Q, sum);

    /*  Remove all terms past the largest non-zero entry.                     */
    tmpl_IntPolynomial_Shrink(sum);
}
/*  End of tmpl_IntPolynomial_Add.                                            */
