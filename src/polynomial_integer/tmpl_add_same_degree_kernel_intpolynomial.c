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
 *                  tmpl_add_same_degree_kernel_intpolynomial                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds two polynomials with integer coefficients of the same degree.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Add_Same_Degree_Kernel                             *
 *  Purpose:                                                                  *
 *      Computes the sum of two polynomials over Z[x] with 'int' coefficients.*
 *      Given polynomials p, q in Z[x] of the same degree this computes p + q.*
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
 *      stdlib.h:                                                             *
 *          realloc:                                                          *
 *              Resizes an array.                                             *
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
 *          end result. Use tmpl_IntPolynomial_Add_Same_Degree for a safer    *
 *          alternative. That checks the inputs and then uses this function.  *
 *                                                                            *
 *      2.) This function assumes that deg(p) = deg(q). No checks for this    *
 *          are performed, only use this function if you know this is true.   *
 *                                                                            *
 *      3.) If realloc fails, the error_occurred Boolean is set to true.      *
 *          The data in sum is not free'd in this case, it is left alone.     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_cast.h:                                                          *
 *          Header with TMPL_CAST for casting with C vs. C++ compatibility.   *
 *  2.) tmpl_realloc.h:                                                       *
 *          Header providing TMPL_REALLOC.                                    *
 *  3.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  4.) tmpl_polynomial_int.h:                                                *
 *          Header where the tmpl_IntPolynomial typedef is given.             *
 *  5.) stddef.h:                                                             *
 *          Standard library header providing the size_t type.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 19, 2023                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/12/03: Ryan Maguire                                                  *
 *      Changed order of function call, sum is now first. This mimics the     *
 *      behavior of many C libraries (memcpy, for example), dest is first.    *
 ******************************************************************************/

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  realloc and casting with C vs. C++ compatibility provided here.           */
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/compat/tmpl_realloc.h>

/*  Integer polynomial typedef provided here.                                 */
#include <libtmpl/include/types/tmpl_polynomial_int.h>

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Forward declaration / function prototype.                                 */
extern void
tmpl_IntPolynomial_Add_Same_Degree_Kernel(tmpl_IntPolynomial * const sum,
                                          const tmpl_IntPolynomial * const p,
                                          const tmpl_IntPolynomial * const q);

/*  Function for adding two polynomials over Z[x].                            */
void
tmpl_IntPolynomial_Add_Same_Degree_Kernel(tmpl_IntPolynomial * const sum,
                                          const tmpl_IntPolynomial * const p,
                                          const tmpl_IntPolynomial * const q)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;

    /*  The length of the array of coefficients for the sum.                  */
    const size_t length = p->degree + 1;

    /*  Check if sum needs to be resized.                                     */
    if (sum->degree != p->degree)
    {
        /*  reallocate memory for the sum pointer. This needs degree+1 terms. */
        void * const tmp = TMPL_REALLOC(sum->coeffs, length);

        /*  Check if realloc failed. Treat this as an error if it did.        */
        if (!tmp)
        {
            sum->error_occurred = tmpl_True;
            sum->error_message =
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Add_Same_Degree_Kernel\n\n"
                "realloc failed and returned NULL.\n\n";

            return;
        }

        /*  Otherwise reset the degree and the coefficients pointer.          */
        sum->coeffs = TMPL_CAST(tmp, signed int *);
        sum->degree = p->degree;
    }

    /*  Compute the sum term by term. Note, we are assuming deg(p) = deg(q).  */
    for (n = 0; n < length; ++n)
        sum->coeffs[n] = p->coeffs[n] + q->coeffs[n];
}
/*  End of tmpl_IntPolynomial_Add_Same_Degree_Kernel.                         */
