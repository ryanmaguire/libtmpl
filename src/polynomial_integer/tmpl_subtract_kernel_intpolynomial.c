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
 *                     tmpl_subtract_kernel_intpolynomial                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Subtracts two polynomials with integer coefficients.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Subtract_Kernel                                    *
 *  Purpose:                                                                  *
 *      Computes the difference of two polynomials over Z[x] with 'int'       *
 *      coefficients. That is, given polynomials P, Q in Z[x], computes P - Q.*
 *  Arguments:                                                                *
 *      P (const tmpl_IntPolynomial *):                                       *
 *          A pointer to a polynomial.                                        *
 *      Q (const tmpl_IntPolynomial *):                                       *
 *          Another pointer to a polynomial.                                  *
 *      diff (tmpl_IntPolynomial *):                                          *
 *          A pointer to a polynomial. The difference is stored here.         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      realloc (stdlib.h):                                                   *
 *          Resizes an array.                                                 *
 *      tmpl_strdup (tmpl_string.h):                                          *
 *          Duplicates a string. Equivalent to the POSIX function strdup.     *
 *  Method:                                                                   *
 *      Polynomial subtraction is performed term-by-term. The complexity is   *
 *      thus O(max(deg(P), deg(Q)). That is, if we have:                      *
 *                                                                            *
 *                   N                       M                                *
 *                 -----                   -----                              *
 *                 \          n            \          m                       *
 *          P(x) = /      a  x      Q(x) = /      b  x                        *
 *                 -----   n               -----   m                          *
 *                 n = 0                   m = 0                              *
 *                                                                            *
 *      The difference is defined by:                                         *
 *                                                                            *
 *                          K                                                 *
 *                        -----                                               *
 *                        \                 k                                 *
 *          P(x) - Q(x) = /      (a  - b ) x                                  *
 *                        -----    k    k                                     *
 *                        k = 0                                               *
 *                                                                            *
 *      Where K = max(N, M) and we pad either a_k or b_k with zeros to make   *
 *      the terms valid. We perform this by computing the sum a_k + b_k for   *
 *      0 <= k <= min(N, M) and then copy the coefficients of the larger      *
 *      degree polynomial for min(N, M) < k <= max(N, M).                     *
 *  Notes:                                                                    *
 *      This function does not check for NULL pointers nor shrinks the end    *
 *      result. Use tmpl_IntPolynomial_Subtract for a safer alternative. That *
 *      function checks the inputs and then calls this function.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library file with realloc and size_t.                    *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  3.) tmpl_string.h:                                                        *
 *          Header file where tmpl_strdup is declared.                        *
 *  4.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 26, 2023                                                *
 ******************************************************************************/

/*  realloc found here.                                                       */
#include <stdlib.h>

#include <libtmpl/include/helper/tmpl_max.h>

/*  TMPL_USE_MEMCPY macro is here.                                            */
#include <libtmpl/include/tmpl_config.h>

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup function provided here.                                       */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for subtracting two polynomials over Z[x].                       */
void
tmpl_IntPolynomial_Subtract_Kernel(const tmpl_IntPolynomial *P,
                                   const tmpl_IntPolynomial *Q,
                                   tmpl_IntPolynomial *diff)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const size_t degree = TMPL_MAX(P->degree, Q->degree);
    size_t n;

    /*  Check if sum needs to be resized.                                     */
    if (diff->degree != degree)
    {
        /*  reallocate memory for the sum pointer. This needs degree+1 terms. */
        const size_t len = degree + (size_t)1;
        void *tmp = realloc(diff->coeffs, sizeof(*diff->coeffs)*len);

        /*  Check if realloc failed.                                          */
        if (!tmp)
        {
            diff->error_occurred = tmpl_True;
            diff->error_message = tmpl_String_Duplicate(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Subtract_Kernel\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }

        /*  Otherwise reset the degree and the coefficients pointer.          */
        else
        {
            diff->coeffs = tmp;
            diff->degree = degree;
        }
    }

    /*  If P is larger than Q we compute the difference for the first deg(Q)  *
     *  terms and then copy the remaining deg(P)-deg(Q) terms of P.           */
    if (P->degree > Q->degree)
    {
        /*  Perform a_k - b_k up to the degree of Q.                          */
        for (n = (size_t)0; n <= Q->degree; ++n)
            diff->coeffs[n] = P->coeffs[n] - Q->coeffs[n];

        /*  For the remaining terms store the values of P.                    */
        for (n = Q->degree + (size_t)1; n <= P->degree; ++n)
            diff->coeffs[n] = P->coeffs[n];
    }

    /*  Otherwise we flip this and copy the negative of the terms of Q.       */
    else
    {
        /*  Perform a_k - b_k up to the degree of P.                          */
        for (n = (size_t)0; n <= P->degree; ++n)
            diff->coeffs[n] = P->coeffs[n] - Q->coeffs[n];

        /*  For the remaining terms store the negative values of Q.           */
        for (n = P->degree + (size_t)1; n <= Q->degree; ++n)
            diff->coeffs[n] = -Q->coeffs[n];
    }
}
/*  End of tmpl_IntPolynomial_Subtract_Kernel.                                */
