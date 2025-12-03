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
 *                     tmpl_add_same_degree_intpolynomial                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds two polynomials with integer coefficients of the same degree.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Add_Same_Degree                                    *
 *  Purpose:                                                                  *
 *      Computes the sum of two polynomials over Z[x] with 'int' coefficients.*
 *      That is, given polynomials p, q in Z[x], computes p + q. p and q are  *
 *      assumed to have the same degree.                                      *
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
 *          tmpl_IntPolynomial_Add_Same_Degree_Kernel:                        *
 *              Adds two polynomials without error checking or shrinking.     *
 *          tmpl_IntPolynomial_Make_Empty:                                    *
 *              Free's the data in a polynomial and makes it empty.           *
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
 *      1.) One should check if "sum" is NULL or has error_occurred set to    *
 *          True after calling this function to safely handle errors.         *
 *      2.) This function assumes p and q are of the same degree.             *
 *      3.) If p, q, p->coeffs, or q->coeffs are NULL, sum is made empty.     *
 *      4.) If sum is NULL or sum->error_occurred is True, nothing is done.   *
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
 ******************************************************************************/

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Integer polynomial typedef provided here.                                 */
#include <libtmpl/include/types/tmpl_polynomial_int.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for adding two polynomials over Z[x] of the same degree.         */
void
tmpl_IntPolynomial_Add_Same_Degree(tmpl_IntPolynomial * const sum,
                                   const tmpl_IntPolynomial * const p,
                                   const tmpl_IntPolynomial * const q)
{
    /*  If the output pointer is NULL there's nothing to be done.             */
    if (!sum)
        return;

    /*  If an error occurred before this function was called, abort.          */
    if (sum->error_occurred)
        return;

    /*  Since we assume both polynomials have the same degree, if one of them *
     *  is the empty polynomial, then we may assume both are. In this case    *
     *  we set the output to the empty polynomial as well.                    */
    if (!p || !q)
    {
        /*  Safely free any data in sum and set it to the empty polynomial.   */
        tmpl_IntPolynomial_Make_Empty(sum);
        return;
    }

    /*  If either p or q have an error, abort the computation.                */
    if (p->error_occurred || q->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message =
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Add_Same_Degree\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n";

        return;
    }

    /*  Similar check for NULL pointers, if either of the coefficient arrays  *
     *  are NULL, then we are summing empty polynomials. The result is empty. */
    if (!p->coeffs || !q->coeffs)
    {
        /*  Same idea as before, free the data and make an empty polynomial.  */
        tmpl_IntPolynomial_Make_Empty(sum);
        return;
    }

    /*  Add the two polynomials and store the result in sum.                  */
    tmpl_IntPolynomial_Add_Same_Degree_Kernel(sum, p, q);

    /*  Remove all terms past the largest non-zero entry.                     */
    tmpl_IntPolynomial_Shrink(sum);
}
/*  End of tmpl_IntPolynomial_Add_Same_Degree.                                */
