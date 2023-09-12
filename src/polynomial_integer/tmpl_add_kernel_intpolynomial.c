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
 *      stdlib.h:                                                             *
 *          realloc:                                                          *
 *              Resizes an array.                                             *
 *      tmpl_string.h:                                                        *
 *          tmpl_String_Duplicate:                                            *
 *              Duplicates a string. Equivalent to the POSIX function strdup. *
 *      string.h:                                                             *
 *          memcpy:                                                           *
 *              Copies data from one chunk of memory to another. Only used if *
 *              TMPL_USE_MEMCPY is set to 1.                                  *
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
 *      result. Use tmpl_IntPolynomial_Add for a safer alternative. That      *
 *      function checks the inputs and then calls this function.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library file with realloc and size_t.                    *
 *  2.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_USE_MEMCPY macro.                 *
 *  3.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
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

/*  tmpl_String_Duplicate function provided here.                             */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  It may be faster, pending computer, to use memcpy to copy the larger      *
 *  polynomial into the output, rather than using a for-loop. On computers    *
 *  tested the for-loop is slightly faster. Nevertheless, to use this version *
 *  build libtmpl with USE_MEMCPY=1 set.                                      *
 *                                                                            *
 *  WARNING:                                                                  *
 *      If you use memcpy instead of a for-loop, calling this function with   *
 *      P == sum or Q == sum may result in undefined behavior. For this       *
 *      reason, and since the for-loop seems to be slightly faster, default   *
 *      behavior is to avoid memcpy.                                          */
#if TMPL_USE_MEMCPY == 1
#include <string.h>
#endif

/*  Function for adding two polynomials over Z[x].                            */
void
tmpl_IntPolynomial_Add_Kernel(const tmpl_IntPolynomial *P,
                              const tmpl_IntPolynomial *Q,
                              tmpl_IntPolynomial *sum)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n, len;
    const tmpl_IntPolynomial *first, *second;

    /*  Useful constants cast to type "size_t".                               */
    const size_t zero = (size_t)0;
    const size_t one = (size_t)1;

    /*  Get the polynomial with the larger degree and set to "first".         */
    if (P->degree < Q->degree)
    {
        first = Q;
        second = P;
    }
    else
    {
        first = P;
        second = Q;
    }

    /*  The length of the array of coefficients for the sum.                  */
    len = first->degree + one;

    /*  Check if sum needs to be resized.                                     */
    if (sum->degree != first->degree)
    {
        /*  reallocate memory for the sum pointer. This needs degree+1 terms. */
        void *tmp = realloc(sum->coeffs, sizeof(*sum->coeffs)*len);

        /*  Check if realloc failed.                                          */
        if (!tmp)
        {
            sum->error_occurred = tmpl_True;
            sum->error_message = tmpl_String_Duplicate(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Add_Kernel\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }

        /*  Otherwise reset the degree and the coefficients pointer.          */
        sum->coeffs = tmp;
        sum->degree = first->degree;
    }

    /*  If the user requested memcpy, use this to copy the data.              */
#if TMPL_USE_MEMCPY == 1

    /*  memcpy syntax is (void *dest, const void *src, size_t num).           */
    memcpy(sum->coeffs, first->coeffs, len*sizeof(*sum->coeffs));

    /*  Now add the coefficients from the smaller polynomial to conclude.     */
    for (n = zero; n <= second->degree; ++n)
        sum->coeffs[n] += second->coeffs[n];

#else
/*  Else for #if TMPL_USE_MEMCPY == 1.                                        */

    /*  Compute the sum term by term.                                         */
    for (n = zero; n <= second->degree; ++n)
        sum->coeffs[n] = first->coeffs[n] + second->coeffs[n];

    /*  Add the coefficients of the larger polynomial.                        */
    for (n = second->degree + one; n < len; ++n)
        sum->coeffs[n] = first->coeffs[n];

#endif
/*  End of #if TMPL_USE_MEMCPY == 1.                                          */

}
/*  End of tmpl_IntPolynomial_Add_Kernel.                                     */
