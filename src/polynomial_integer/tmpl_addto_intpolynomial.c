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
 *                          tmpl_addto_intpolynomial                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds two polynomials with integer coefficients.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_AddTo                                              *
 *  Purpose:                                                                  *
 *      Computes the sum of two polynomials over Z[x] with 'int' coefficients.*
 *      That is, given polynomials P, Q in Z[x], computes P += Q.             *
 *  Arguments:                                                                *
 *      P (tmpl_IntPolynomial *):                                             *
 *          A pointer to a polynomial. The sum is stored here.                *
 *      Q (const tmpl_IntPolynomial *):                                       *
 *          Another pointer to a polynomial.                                  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      tmpl_polynomial_integer.h:                                            *
 *          tmpl_IntPolynomial_AddTo_Kernel:                                  *
 *              Adds two polynomials without error checking or shrinking.     *
 *          tmpl_IntPolynomial_Copy:                                          *
 *              Copies the data in a polynomial to another.                   *
 *          tmpl_IntPolynomial_Shrink:                                        *
 *              Shrinks a polynomial by removing all terms past the largest   *
 *              non-zero coefficient.                                         *
 *      tmpl_string.h:                                                        *
 *          tmpl_String_Duplicate:                                            *
 *              Duplicates a string. Equivalent to the POSIX function strdup. *
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
 *          1.) The "P" variable is NULL, or has error_occurred = true.       *
 *          2.) Q has error_occurred = true.                                  *
 *          3.) realloc fails to resize the coefficient array.                *
 *      One can safely handle all cases by inspecting "P" after using this    *
 *      function. First check if it is NULL, then if error_occurred = true.   *
 *                                                                            *
 *      It does not matter if P = Q. In this case realloc is not needed.      *
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
 *  Date:       May 18, 2023                                                  *
 ******************************************************************************/

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_String_Duplicate function provided here.                             */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for adding two polynomials over Z[x].                            */
void
tmpl_IntPolynomial_AddTo(tmpl_IntPolynomial *P, const tmpl_IntPolynomial *Q)
{
    /*  If P is NULL there is nothing to be done. Return.                     */
    if (!P)
        return;

    /*  Similarly if P had an error occur previously.                         */
    if (P->error_occurred)
        return;

    /*  If Q is NULL there is nothing to add.                                 */
    if (!Q)
    {
        /*  Remove redundant zero terms and return.                           */
        tmpl_IntPolynomial_Shrink(P);
        return;
    }

    /*  If Q has an error abort the computation.                              */
    if (Q->error_occurred)
    {
        P->error_occurred = tmpl_True;
        P->error_message = tmpl_String_Duplicate(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_AddTo\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n"
        );
        return;
    }

    /*  Special case. If P is the empty polynomial copy Q to P.               */
    if (!P->coeffs)
        tmpl_IntPolynomial_Copy(P, Q);

    /*  If Q is empty we don't need to add anything and can skip the sum.     */
    else if (Q->coeffs)
        tmpl_IntPolynomial_AddTo_Kernel(P, Q);

    /*  Remove all terms past the largest non-zero entry.                     */
    tmpl_IntPolynomial_Shrink(P);
}
/*  End of tmpl_IntPolynomial_AddTo.                                          */
