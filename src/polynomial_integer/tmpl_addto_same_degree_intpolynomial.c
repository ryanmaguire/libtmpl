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
 *                    tmpl_addto_same_degree_intpolynomial                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds two polynomials with integer coefficients of the same degree.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_AddTo_Same_Degree                                  *
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
 *          tmpl_IntPolynomial_AddTo_Same_Degree_Kernel:                      *
 *              Adds two polynomials without error checking or shrinking.     *
 *          tmpl_IntPolynomial_Shrink:                                        *
 *              Shrinks a polynomial by removing all terms past the largest   *
 *              non-zero coefficient.                                         *
 *  Method:                                                                   *
 *      Polynomial addition is performed term-by-term. The complexity is thus *
 *      O(N), N being the degree of p and q. That is, if we have:             *
 *                                                                            *
 *                   N                       N                                *
 *                 -----                   -----                              *
 *                 \          n            \          n                       *
 *          p(x) = /      a  x      q(x) = /      b  x                        *
 *                 -----   n               -----   n                          *
 *                 n = 0                   n = 0                              *
 *                                                                            *
 *      The sum is defined by:                                                *
 *                                                                            *
 *                          N                                                 *
 *                        -----                                               *
 *                        \                 n                                 *
 *          p(x) + q(x) = /      (a  + b ) x                                  *
 *                        -----    n    n                                     *
 *                        n = 0                                               *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) There are a few possible ways for an error to occur.              *
 *              a.) The "p" variable is NULL, or has error_occurred = true.   *
 *              b.) The input polynomial (q) has error_occurred = true.       *
 *          One can safely handle these cases by inspecting "p" after using   *
 *          this function. First check if it is NULL, then if                 *
 *          error_occurred = true.                                            *
 *      2.) It does not matter if p = q.                                      *
 *      3.) This function assumes deg(p) = deg(q).                            *
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
 *  Date:       May 19, 2023                                                  *
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
tmpl_IntPolynomial_AddTo_Same_Degree(tmpl_IntPolynomial * const p,
                                     const tmpl_IntPolynomial * const q)
{
    /*  If p is NULL there is nothing to do.                                  */
    if (!p)
        return;

    /*  If p had an error occur previously, abort.                            */
    if (p->error_occurred)
        return;

    /*  Since we assume p and q are the same degree, if q is empty, then p    *
     *  must be empty as well. Check if q is empty, and return if so.         */
    if (!q)
        return;

    /*  If q has an error, abort the computation. Treat this as an error.     */
    if (q->error_occurred)
    {
        p->error_occurred = tmpl_True;
        p->error_message =
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_AddTo_Same_Degree\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n";

        return;
    }

    /*  Similar check for the coeffs array. If NULL, there's nothing to do.   */
    if (!q->coeffs)
        return;

    /*  Add the polynomials term-by-term.                                     */
    tmpl_IntPolynomial_AddTo_Same_Degree_Kernel(p, q);

    /*  Remove all terms past the largest non-zero entry.                     */
    tmpl_IntPolynomial_Shrink(p);
}
/*  End of tmpl_IntPolynomial_AddTo_Same_Degree.                              */
