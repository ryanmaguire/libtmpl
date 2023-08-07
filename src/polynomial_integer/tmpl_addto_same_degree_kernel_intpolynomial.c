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
 *      That is, given polynomials P, Q in Z[x], computes P += Q.             *
 *  Arguments:                                                                *
 *      P (tmpl_IntPolynomial *):                                             *
 *          A pointer to a polynomial. The sum is stored here.                *
 *      Q (const tmpl_IntPolynomial *):                                       *
 *          Another pointer to a polynomial.                                  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Polynomial addition is performed term-by-term. The complexity is thus *
 *      O(N), N being the degree of P and Q. That is, if we have:             *
 *                                                                            *
 *                   N                       N                                *
 *                 -----                   -----                              *
 *                 \          n            \          n                       *
 *          P(x) = /      a  x      Q(x) = /      b  x                        *
 *                 -----   n               -----   n                          *
 *                 n = 0                   n = 0                              *
 *                                                                            *
 *      The sum is defined by:                                                *
 *                                                                            *
 *                          N                                                 *
 *                        -----                                               *
 *                        \                 n                                 *
 *          P(x) + Q(x) = /      (a  + b ) x                                  *
 *                        -----    n    n                                     *
 *                        n = 0                                               *
 *                                                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 19, 2023                                                  *
 ******************************************************************************/

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for adding two polynomials over Z[x].                            */
void
tmpl_IntPolynomial_AddTo_Same_Degree_Kernel(tmpl_IntPolynomial *P,
                                            const tmpl_IntPolynomial *Q)
{
    /*  Variable for indexing over the sum.                                   */
    size_t n;

    /*  Perform the addition term-by-term.                                    */
    for (n = (size_t)0; n <= P->degree; ++n)
        P->coeffs[n] += Q->coeffs[n];
}
/*  End of tmpl_IntPolynomial_AddTo_Same_Degree_Kernel.                       */
