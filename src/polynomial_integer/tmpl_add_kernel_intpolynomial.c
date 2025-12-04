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
 *                        tmpl_add_kernel_intpolynomial                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds two polynomials with integer coefficients.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Add_Kernel                                         *
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
 *      stdlib.h:                                                             *
 *          realloc:                                                          *
 *              Resizes an array.                                             *
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
 *      1.) This function does not check for NULL pointers nor shrinks the    *
 *          end result. Use tmpl_IntPolynomial_Add for a safer alternative.   *
 *          That function checks the inputs and then calls this function.     *
 *      2.) The option to use memcpy, instead of a for-loop, used to be       *
 *          available by setting USE_MEMCPY at compile time. In this          *
 *          function memcpy may produce undefined behavior if sum and p point *
 *          to the same polynomial, or if sum and q are the same.             *
 *          Benchmarks show that the for-loop method is just as fast (faster, *
 *          actually) than the memcpy method when a compiler with decent      *
 *          optimizations is used. Because of this the memcpy method has been *
 *          removed. It is valid to do tmpl_IntPolynomial_Add(p, p, q) or     *
 *          tmpl_IntPolynomial_Add(q, p, q), but note that it is faster to    *
 *          use tmpl_IntPolynomial_AddTo instead.                             *
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
 *  Date:       April 25, 2023                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/25: Ryan Maguire                                                  *
 *      Added doc-string and comments.                                        *
 *  2025/12/03: Ryan Maguire                                                  *
 *      Changed order of function call, sum is now first. This mimics the     *
 *      behavior of many C libraries (memcpy, for example), dest is first.    *
 *      Removed memcpy method. Only the for-loop method remains.              *
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
tmpl_IntPolynomial_Add_Kernel(tmpl_IntPolynomial * const sum,
                              const tmpl_IntPolynomial * const p,
                              const tmpl_IntPolynomial * const q);

/*  Function for adding two polynomials over Z[x].                            */
void
tmpl_IntPolynomial_Add_Kernel(tmpl_IntPolynomial * const sum,
                              const tmpl_IntPolynomial * const p,
                              const tmpl_IntPolynomial * const q)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;

    /*  Get the polynomial with the larger degree and set it to "first".      */
    const tmpl_IntPolynomial * const first = (p->degree < q->degree ? q : p);
    const tmpl_IntPolynomial * const second = (p->degree < q->degree ? p : q);

    /*  The length of the array of coefficients for the sum.                  */
    const size_t length = first->degree + 1;

    /*  Check if sum needs to be resized.                                     */
    if (sum->degree != first->degree)
    {
        /*  Reallocate memory for the sum pointer. This needs degree+1 terms. */
        void * const tmp = TMPL_REALLOC(sum->coeffs, length);

        /*  Check if realloc failed.                                          */
        if (!tmp)
        {
            sum->error_occurred = tmpl_True;
            sum->error_message =
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Add_Kernel\n\n"
                "realloc failed. Aborting.\n\n";

            return;
        }

        /*  Otherwise reset the degree and the coefficients pointer.          */
        sum->coeffs = TMPL_CAST(tmp, signed int *);
        sum->degree = first->degree;
    }

    /*  Compute the sum term by term.                                         */
    for (n = 0; n <= second->degree; ++n)
        sum->coeffs[n] = first->coeffs[n] + second->coeffs[n];

    /*  Add the coefficients of the larger polynomial.                        */
    for (n = second->degree + 1; n < length; ++n)
        sum->coeffs[n] = first->coeffs[n];
}
/*  End of tmpl_IntPolynomial_Add_Kernel.                                     */
