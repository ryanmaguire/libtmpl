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
 *      Provides scalar multiplication for elements of Z[x].                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Scale                                              *
 *  Purpose:                                                                  *
 *      Computes the scalar product of a polynomial with an integer.          *
 *  Arguments:                                                                *
 *      P (const tmpl_IntPolynomial *):                                       *
 *          A pointer to a polynomial.                                        *
 *      scale (int):                                                          *
 *          The integer scalar.                                               *
 *      prod (tmpl_IntPolynomial *):                                          *
 *          A pointer to a polynomial. The product is stored here.            *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      tmpl_IntPolynomial_Scale_Kernel (tmpl_polynomial_int.h):              *
 *          Scalar multiplication without error checking.                     *
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
 *                    \            n                                          *
 *          c P(x) =  /      c a  x                                           *
 *                    -----     n                                             *
 *                    n = 0                                                   *
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

/*  free found here.                                                          */
#include <stdlib.h>

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup function provided here.                                       */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for performing scalar multiplication for polynomials over Z[x].  */
void
tmpl_IntPolynomial_Scale(const tmpl_IntPolynomial *P,
                         int scale, tmpl_IntPolynomial *prod)
{
    /*  If the output pointer is NULL there's nothing to be done.             */
    if (!prod)
        return;

    /*  If an error occurred before this function was called, abort.          */
    if (prod->error_occurred)
        return;

    /*  If P is NULL set an error and return.                                 */
    if (!P)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Scale\n\n"
            "Input polynomial is NULL. Aborting.\n\n"
        );
        return;
    }

    /*  Similarly if P has an error set.                                      */
    if (P->error_occurred)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Scale\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n"
        );
        return;
    }

    /*  If the polynomial is empty there is nothing to scale.                 */
    if (!P->coeffs)
    {
        /*  Scaling by the empty polynomial should result in an empty         *
         *  polynomial. Avoid memory leaks, check if anything should be freed.*/
        if (prod->coeffs)
            free(prod->coeffs);

        /*  Set the product to the empty polynomial.                          */
        prod->coeffs = NULL;
        prod->degree = (size_t)0;
        return;
    }

    /*  Scale the polynomial and store the result in prod.                    */
    tmpl_IntPolynomial_Scale_Kernel(P, scale, prod);
}
/*  End of tmpl_IntPolynomial_Scale.                                          */
