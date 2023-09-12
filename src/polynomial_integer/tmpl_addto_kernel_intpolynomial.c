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
 *                       tmpl_addto_kernel_intpolynomial                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds two polynomials with integer coefficients.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_AddTo_Kernel                                       *
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
 *      stdlib.h:                                                             *
 *          realloc:                                                          *
 *              Resizes an array.                                             *
 *      tmpl_string.h:                                                        *
 *          tmpl_String_Duplicate:                                            *
 *              Duplicates a string. Equivalent to the POSIX function strdup. *
 *  Method:                                                                   *
 *      Polynomial addition is performed term-by-term. The complexity is thus *
 *      O(max(deg(P), deg(Q)). That is, if we have:                           *
 *                                                                            *
 *                   N                       M                                *
 *                 -----                   -----                              *
 *                 \          n            \          m                       *
 *          P(x) = /      a  x      Q(x) = /      b  x                        *
 *                 -----   n               -----   m                          *
 *                 n = 0                   m = 0                              *
 *                                                                            *
 *      The sum is defined by:                                                *
 *                                                                            *
 *                          K                                                 *
 *                        -----                                               *
 *                        \                 k                                 *
 *          P(x) + Q(x) = /      (a  + b ) x                                  *
 *                        -----    k    k                                     *
 *                        k = 0                                               *
 *                                                                            *
 *      Where K = max(N, M) and we pad either a_k or b_k with zeros to make   *
 *      the terms valid. We perform this by computing the sum a_k + b_k for   *
 *      0 <= k <= min(N, M) and then copy the coefficients of the larger      *
 *      degree polynomial for min(N, M) < k <= max(N, M).                     *
 *  Notes:                                                                    *
 *      This function does not check for NULL pointers nor shrinks the end    *
 *      result. Use tmpl_IntPolynomial_AddTo for a safer alternative. That    *
 *      function checks the inputs and then calls this function.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library file with realloc and size_t.                    *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  3.) tmpl_minmax.h:                                                        *
 *          Provides the TMPL_MAX macro.                                      *
 *  4.) tmpl_string.h:                                                        *
 *          Header file where tmpl_String_Duplicate is declared.              *
 *  5.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 *  6.) string.h (optional):                                                  *
 *          Standard library file with the memcpy function.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 25, 2023                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/25: Ryan Maguire                                                  *
 *      Added doc-string and comments.                                        *
 ******************************************************************************/

/*  realloc found here.                                                       */
#include <stdlib.h>

/*  TMPL_USE_MEMCPY macro is here.                                            */
#include <libtmpl/include/tmpl_config.h>

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  TMPL_MAX macro provided here.                                             */
#include <libtmpl/include/tmpl_minmax.h>

/*  tmpl_String_Duplicate function provided here.                             */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for adding two polynomials over Z[x].                            */
void
tmpl_IntPolynomial_AddTo_Kernel(tmpl_IntPolynomial *P,
                                const tmpl_IntPolynomial *Q)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;

    /*  Useful constants cast to type "size_t".                               */
    const size_t zero = (size_t)0;
    const size_t one = (size_t)1;

    /*  Check if the sum needs to be resized.                                 */
    if (P->degree < Q->degree)
    {
        /*  The number of elements in the final array.                        */
        const size_t len = Q->degree + one;

        /*  reallocate memory for the sum pointer. This needs degree+1 terms. */
        void *tmp = realloc(P->coeffs, sizeof(*P->coeffs) * len);

        /*  Check if realloc failed.                                          */
        if (!tmp)
        {
            P->error_occurred = tmpl_True;
            P->error_message = tmpl_String_Duplicate(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_AddTo_Kernel\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }

        /*  Otherwise reset the coefficient pointer.                          */
        P->coeffs = tmp;

        /*  Initialize the new entries to zero.                               */
        for (n = P->degree + one; n < len; ++n)
            P->coeffs[n] = 0;

        /*  Reset the degree to reflect the size of the new array.            */
        P->degree = Q->degree;
    }

    /*  Compute the sum term by term.                                         */
    for (n = zero; n <= Q->degree; ++n)
        P->coeffs[n] += Q->coeffs[n];
}
/*  End of tmpl_IntPolynomial_AddTo_Kernel.                                   */
