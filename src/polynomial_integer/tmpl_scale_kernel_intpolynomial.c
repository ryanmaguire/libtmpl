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
 *      Scalar multiplication is performed term-by-term. That is, if we have: *
 *                                                                            *
 *                   N                                                        *
 *                 -----                                                      *
 *                 \          n                                               *
 *          P(x) = /      a  x                                                *
 *                 -----   n                                                  *
 *                 n = 0                                                      *
 *                                                                            *
 *      The product is defined by:                                            *
 *                                                                            *
 *                      N                                                     *
 *                    -----                                                   *
 *                    \            k                                          *
 *          c P(x) =  /      c a  x                                           *
 *                    -----     k                                             *
 *                    k = 0                                                   *
 *                                                                            *
 *      This is computed term-by-term and returned.                           *
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
 *  Date:       April 26, 2023                                                *
 ******************************************************************************/

/*  realloc provided here.                                                    */
#include <stdlib.h>

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup function provided here.                                       */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for performing scalar multiplication for polynomials over Z[x].  */
void
tmpl_IntPolynomial_Scale_Kernel(const tmpl_IntPolynomial *P,
                                int scale, tmpl_IntPolynomial *prod)
{
    size_t n;
    if (prod->degree != P->degree)
    {
        const size_t len = P->degree + (size_t)1;
        void *tmp = realloc(prod->coeffs, sizeof(*prod->coeffs)*len);

        if (!tmp)
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Scale_Kernel\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }

        /*  Otherwise reset the degree and the coefficients pointer.          */
        else
        {
            prod->coeffs = tmp;
            prod->degree = P->degree;
        }
    }

    for (n = (size_t)0; n <= P->degree; ++n)
        prod->coeffs[n] = scale*P->coeffs[n];
}
/*  End of tmpl_IntPolynomial_Scale_Kernel.                                   */
