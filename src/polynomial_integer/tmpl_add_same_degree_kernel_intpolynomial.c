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
 *      Given polynomials P, Q in Z[x] of the same degree this computes P + Q.*
 *  Arguments:                                                                *
 *      P (const tmpl_IntPolynomial *):                                       *
 *          A pointer to a polynomial.                                        *
 *      Q (const tmpl_IntPolynomial *):                                       *
 *          Another pointer to a polynomial, of the same degree as P.         *
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
 *  Notes:                                                                    *
 *      This function does not check for NULL pointers nor shrinks the end    *
 *      result. Use tmpl_IntPolynomial_Add_Same_Degree for a safer            *
 *      alternative. It checks the inputs and then uses this function.        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library file with realloc and size_t.                    *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  3.) tmpl_string.h:                                                        *
 *          Header file where tmpl_String_Duplicate is declared.              *
 *  4.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 19, 2023                                                  *
 ******************************************************************************/

/*  realloc found here.                                                       */
#include <stdlib.h>

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_String_Duplicate function provided here.                             */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for adding two polynomials over Z[x].                            */
void
tmpl_IntPolynomial_Add_Same_Degree_Kernel(const tmpl_IntPolynomial *P,
                                          const tmpl_IntPolynomial *Q,
                                          tmpl_IntPolynomial *sum)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;

    /*  The length of the array of coefficients for the sum.                  */
    const size_t len = P->degree + (size_t)1;

    /*  Check if sum needs to be resized.                                     */
    if (sum->degree != P->degree)
    {
        /*  reallocate memory for the sum pointer. This needs degree+1 terms. */
        void *tmp = realloc(sum->coeffs, sizeof(*sum->coeffs)*len);

        /*  Check if realloc failed.                                          */
        if (!tmp)
        {
            sum->error_occurred = tmpl_True;
            sum->error_message = tmpl_String_Duplicate(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Add_Same_Degree_Kernel\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }

        /*  Otherwise reset the degree and the coefficients pointer.          */
        sum->coeffs = tmp;
        sum->degree = P->degree;
    }

    /*  Compute the sum term by term.                                         */
    for (n = (size_t)0; n < len; ++n)
        sum->coeffs[n] = P->coeffs[n] + Q->coeffs[n];
}
/*  End of tmpl_IntPolynomial_Add_Same_Degree_Kernel.                         */
