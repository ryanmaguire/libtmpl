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
 *      That is, given polynomials p, q in Z[x], computes p += q.             *
 *  Arguments:                                                                *
 *      p (tmpl_IntPolynomial * const):                                       *
 *          A pointer to a polynomial. The sum is stored here.                *
 *      q (const tmpl_IntPolynomial * const):                                 *
 *          The polynomial being added to p.                                  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      src/polynomial_integer/                                               *
 *          tmpl_IntPolynomial_AddTo_Kernel:                                  *
 *              Adds two polynomials without error checking or shrinking.     *
 *          tmpl_IntPolynomial_Copy:                                          *
 *              Copies the data in one polynomial to another.                 *
 *          tmpl_IntPolynomial_Shrink:                                        *
 *              Shrinks a polynomial by removing all terms past the largest   *
 *              non-zero coefficient.                                         *
 *  Method:                                                                   *
 *      Polynomial addition is performed term-by-term. The complexity is thus *
 *      O(max(deg(p), deg(q)). That is, if we have:                           *
 *                                                                            *
 *                   N                       M                                *
 *                 -----                   -----                              *
 *                 \          n            \          m                       *
 *          p(x) = /      a  x      q(x) = /      b  x                        *
 *                 -----   n               -----   m                          *
 *                 n = 0                   m = 0                              *
 *                                                                            *
 *      The sum is defined by:                                                *
 *                                                                            *
 *                          K                                                 *
 *                        -----                                               *
 *                        \                 k                                 *
 *          p(x) + q(x) = /      (a  + b ) x                                  *
 *                        -----    k    k                                     *
 *                        k = 0                                               *
 *                                                                            *
 *      Where K = max(N, M) and we pad either a_k or b_k with zeros to make   *
 *      the terms valid. We perform this by computing the sum a_k + b_k for   *
 *      0 <= k <= min(N, M) and then copy the coefficients of the larger      *
 *      degree polynomial for min(N, M) < k <= max(N, M).                     *
 *  Notes:                                                                    *
 *      1.) There are several possible ways for an error to occur.            *
 *              a.) The "p" variable is NULL, or has error_occurred = true.   *
 *              b.) q has error_occurred = true.                              *
 *              c.) realloc fails to resize the coefficient array.            *
 *          One can safely handle all cases by inspecting "p" after using     *
 *          this function. First check if it is NULL, then if                 *
 *          error_occurred = true.                                            *
 *                                                                            *
 *      2.) It does not matter if p = q. In this case realloc is not needed.  *
 *          Note, it is faster to use tmpl_IntPolynomial_ScaleBy in this case *
 *          since p += p is equivalent to p *= 2.                             *
 *                                                                            *
 *      3.) If p is NULL or p->error_occurred is true, nothing is done.       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_polynomial_int.h:                                                *
 *          Header where the tmpl_IntPolynomial typedef is given.             *
 *  3.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 18, 2023                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/12/04: Ryan Maguire                                                  *
 *      Removed tmpl_String_Duplicate call, error_message is now const.       *
 ******************************************************************************/

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Integer polynomial typedef provided here.                                 */
#include <libtmpl/include/types/tmpl_polynomial_int.h>

/*  Polynomial functions provided here, as is the function prototype.         */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for adding two polynomials over Z[x], p += q.                    */
void
tmpl_IntPolynomial_AddTo(tmpl_IntPolynomial * const p,
                         const tmpl_IntPolynomial * const q)
{
    /*  If p is NULL there is nothing to be done. Return.                     */
    if (!p)
        return;

    /*  Similarly if p had an error occur previously.                         */
    if (p->error_occurred)
        return;

    /*  If q is NULL there is nothing to add.                                 */
    if (!q)
    {
        /*  Remove redundant zero terms and return.                           */
        tmpl_IntPolynomial_Shrink(p);
        return;
    }

    /*  If q has an error, abort the computation. Treat this as an error.     */
    if (q->error_occurred)
    {
        p->error_occurred = tmpl_True;
        p->error_message =
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_AddTo\n\n"
            "Input polynomial has error_occurred set to true.\n\n";

        return;
    }

    /*  Special case. If p is the empty polynomial copy q to p.               */
    if (!p->coeffs)
        tmpl_IntPolynomial_Copy(p, q);

    /*  If q is empty we don't need to add anything and can skip the sum.     */
    else if (q->coeffs)
        tmpl_IntPolynomial_AddTo_Kernel(p, q);

    /*  Remove all terms past the largest non-zero entry.                     */
    tmpl_IntPolynomial_Shrink(p);
}
/*  End of tmpl_IntPolynomial_AddTo.                                          */
