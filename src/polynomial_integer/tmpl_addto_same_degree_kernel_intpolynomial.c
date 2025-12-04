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
 *      Adds two polynomials with integer coefficients.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_AddTo_Same_Degree_Kernel                           *
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
 *      None.                                                                 *
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
 *      1.) This function does not check for NULL pointers nor shrinks the    *
 *          end result. Use tmpl_IntPolynomial_AddTo_Same_Degree for a safer  *
 *          alternative. That checks the inputs and then uses this function.  *
 *      2.) This function assumes deg(p) = deg(q).                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_polynomial_int.h:                                                *
 *          Header where the tmpl_IntPolynomial typedef is given.             *
 *  2.) stddef.h:                                                             *
 *          Standard library header providing the size_t type.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 19, 2023                                                  *
 ******************************************************************************/

/*  Integer polynomial typedef provided here.                                 */
#include <libtmpl/include/types/tmpl_polynomial_int.h>

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Forward declaration / function prototype.                                 */
extern void
tmpl_IntPolynomial_AddTo_Same_Degree_Kernel(tmpl_IntPolynomial * const p,
                                            const tmpl_IntPolynomial * const q);

/*  Function for adding two polynomials over Z[x], p += q.                    */
void
tmpl_IntPolynomial_AddTo_Same_Degree_Kernel(tmpl_IntPolynomial * const p,
                                            const tmpl_IntPolynomial * const q)
{
    /*  Variable for indexing over the sum.                                   */
    size_t n;

    /*  Perform the addition term-by-term.                                    */
    for (n = 0; n <= p->degree; ++n)
        p->coeffs[n] += q->coeffs[n];
}
/*  End of tmpl_IntPolynomial_AddTo_Same_Degree_Kernel.                       */
