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
 *      That is, given polynomials p, q in Z[x], computes p + q.              *
 *  Arguments:                                                                *
 *      sum (tmpl_IntPolynomial * const):                                     *
 *          A pointer to a polynomial. The sum is stored here.                *
 *      p (const tmpl_IntPolynomial * const):                                 *
 *          One of the polynomials being added.                               *
 *      q (const tmpl_IntPolynomial * const):                                 *
 *          The polynomial being added to p.                                  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      src/polynomial_integer/                                               *
 *          tmpl_IntPolynomial_Add_Kernel:                                    *
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
 *              a.) The "sum" variable is NULL, or has error_occurred = true. *
 *              b.) An input polynomial (p or q) has error_occurred = true.   *
 *              c.) realloc fails to resize the coefficient array.            *
 *          One can safely handle all cases by inspecting "sum" after using   *
 *          this function. First check if it is NULL, then if                 *
 *          error_occurred = true.                                            *
 *                                                                            *
 *      2.) It does not matter if p = q, p = sum, or if q = sum. realloc does *
 *          not overwrite data when enlarging an array. However it is faster  *
 *          to call tmpl_IntPolynomial_Scale when p = q or                    *
 *          tmpl_IntPolynomial_AddTo when p = sum or q = sum.                 *
 *                                                                            *
 *      3.) If p or q are the empty polynomial, tmpl_IntPolynomial_Copy is    *
 *          called instead. That is, if p is the empty polynomial, q is       *
 *          copied to sum. Similarly if q is the empty polynomial, p is       *
 *          copied to sum.                                                    *
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
 *  Date:       February 8, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/25: Ryan Maguire                                                  *
 *      Added doc-string and comments.                                        *
 *  2023/05/18: Ryan Maguire                                                  *
 *      Changed behavior so that a NULL summand is treated as zero.           *
 *  2025/12/03: Ryan Maguire                                                  *
 *      Changed order of function call, sum is now first. This mimics the     *
 *      behavior of many C libraries (memcpy, for example), dest is first.    *
 ******************************************************************************/

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Integer polynomial typedef provided here.                                 */
#include <libtmpl/include/types/tmpl_polynomial_int.h>

/*  Polynomial functions provided here, as is the function prototype.         */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for adding two polynomials over Z[x].                            */
void
tmpl_IntPolynomial_Add(tmpl_IntPolynomial * const sum,
                       const tmpl_IntPolynomial * const p,
                       const tmpl_IntPolynomial * const q)
{
    /*  If the output pointer is NULL there's nothing to be done.             */
    if (!sum)
        return;

    /*  If an error occurred before this function was called, abort.          */
    if (sum->error_occurred)
        return;

    /*  If p is NULL treat it as a zero polynomial. The sum is thus q.        */
    if (!p)
    {
        /*  Copy the data in q to sum and then remove the redundant terms.    */
        tmpl_IntPolynomial_Copy(sum, q);
        tmpl_IntPolynomial_Shrink(sum);
        return;
    }

    /*  Similarly if q is NULL the sum is then p.                             */
    if (!q)
    {
        /*  Copy the data in p to sum and then shrink the redundant terms.    */
        tmpl_IntPolynomial_Copy(sum, p);
        tmpl_IntPolynomial_Shrink(sum);
        return;
    }

    /*  If either p or q have an error, abort the computation. Treat this as  *
     *  an error, set the Boolean and an error message.                       */
    if (p->error_occurred || q->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message =
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Add\n\n"
            "Input polynomial has error_occurred set to true.\n\n";

        return;
    }

    /*  Special case. If the coefficients of p are NULL we have an empty      *
     *  polynomial, which can be treated as the zero polynomial. Return q.    */
    if (!p->coeffs)
        tmpl_IntPolynomial_Copy(sum, q);

    /*  Same idea if q is an empty polynomial.                                */
    else if (!q->coeffs)
        tmpl_IntPolynomial_Copy(sum, p);

    /*  Otherwise we have a computation to do. The Add_Kernel function deals  *
     *  with the majority of the work, use it to compute sum = p + q.         */
    else
        tmpl_IntPolynomial_Add_Kernel(sum, p, q);

    /*  Remove all terms past the largest non-zero entry.                     */
    tmpl_IntPolynomial_Shrink(sum);
}
/*  End of tmpl_IntPolynomial_Add.                                            */
