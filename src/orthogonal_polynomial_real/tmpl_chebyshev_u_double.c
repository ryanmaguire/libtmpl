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
 *                           tmpl_chebyshev_u_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the evaluation of the Chebyshev U polynomials (second kind). *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Chebyshev_U                                               *
 *  Purpose:                                                                  *
 *      Computes U_n(x) for a fixed x and for n = 0, 1, ..., length - 1.      *
 *  Arguments:                                                                *
 *      evals (double * const):                                               *
 *          The array of evaluations. evals[n] stores the value U_n(x).       *
 *      x (double):                                                           *
 *          A real number. Typically this is between -1 and 1.                *
 *      length (size_t):                                                      *
 *          The number of elements in the array. The highest Chebyshev        *
 *          polynomial that is computed is U_{length - 1}(x).                 *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      For length = 0, abort the computation since the array is empty. For   *
 *      length = 1 or length = 2, use the explicit formulas for the Chebyshev *
 *      polynomials. They are:                                                *
 *                                                                            *
 *          U (x) = 1                                                         *
 *           0                                                                *
 *                                                                            *
 *          U (x) = 2 x                                                       *
 *           1                                                                *
 *                                                                            *
 *      For length > 2, use the recursion relation:                           *
 *                                                                            *
 *          U   (x) = 2 x U   (x) - U (x)                                     *
 *           n+2           n+1       n                                        *
 *                                                                            *
 *      Doing this in an upward iterative fashion is linear in time, whereas  *
 *      naively applying this recursive formula would be exponential. We      *
 *      perform the upwards linear expansion and return.                      *
 *  Error:                                                                    *
 *      The error depends on the number of Chebyshev polynomials requested.   *
 *      In general, the error for U_n(x) is on the order of:                  *
 *                                                                            *
 *          Err = O(epsilon * n * U_n(x))                                     *
 *                                                                            *
 *      For extremely large n, one may obtain a meaningless result.           *
 *  Notes:                                                                    *
 *      1.) This functions checks for NULL pointers, and checks if length is  *
 *          zero. If length is non-zero, and if evals is not NULL, then the   *
 *          evals array must have at least length elements allocated to it.   *
 *      2.) The domain of the Chebyshev polynomials is -1 <= x <= 1. There    *
 *          are no checks for this in the function, and you may use this      *
 *          routine for |x| > 1. The Chebyshev polynomials typically do not   *
 *          have much use when |x| > 1.                                       *
 *      3.) No checks for NaN or Infinity are made.                           *
 *  References:                                                               *
 *      1.) McQuarrie, Donald (2003),                                         *
 *          Mathematical Methods for Scientists and Engineers                 *
 *          University Science Books, ISBN 1-891389-29-7                      *
 *                                                                            *
 *          Excellent introductory text on mathematical physics. A detailed   *
 *          discussion of orthogonal polynomials can be found in Chapter 14:  *
 *          Orthogonal Polynomials and Sturm-Liouville Problems.              *
 *                                                                            *
 *      2.) Arfken, G., Weber, H., Harris, F. (2013)                          *
 *          Mathematical Methods for Physicists, Seventh Edition              *
 *          Academic Press, Elsevier                                          *
 *                                                                            *
 *          Standard textbook on mathematical physics, often used in          *
 *          introductory graduate courses. See Chapter 18: More Special       *
 *          Functions, Section 4: Chebyshev Polynomials                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_cast.h:                                                          *
 *          Header file providing helper macros for casting in C vs. C++.     *
 *  2.) tmpl_orthogonal_polynomial_real.h:                                    *
 *          Header file with the functions prototype.                         *
 *  3.) stddef.h:                                                             *
 *          Standard library header file providing the size_t data type.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 11, 2024                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2021/04/21: Ryan Maguire                                                  *
 *      Initial rough draft used in rss_ringoccs.                             *
 *  2024/12/11: Ryan Maguire                                                  *
 *      Migrated from special_functions_real. Added license and comments.     *
 ******************************************************************************/

/*  Helper macro providing casting for C vs. C++ styles.                      */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_orthogonal_polynomial_real.h>

/*  Standard library header file. The size_t type is found here.              */
#include <stddef.h>

/*  Computes the Chebyshev polynomials U_n(x) for n = 0, 1, ..., length - 1.  */
void tmpl_Double_Chebyshev_U(double * const evals, double x, size_t length)
{
    /*  Cast some constant values to size_t, avoiding implicit conversion.    */
    const size_t zero = TMPL_CAST(0, size_t);
    const size_t one = TMPL_CAST(1, size_t);
    const size_t two = TMPL_CAST(2, size_t);

    /*  Declare necessary variables. C89 requires declarations at the top of  *
     *  a block. n is used for indexing the Chebyshev polynomials.            */
    size_t n;

    /*  Check for NULL pointers and empty arrays. Nothing to do in this case. */
    if (!evals || length == zero)
        return;

    /*  evals has at least one element allocated to it. U_0(x) = 1. Use this. */
    evals[0] = 1.0;

    /*  If length is not greater than two, we can skip the recursion          *
     *  formula. In this case, we are just computing U_0(x). Return.          */
    if (length == one)
        return;

    /*  length >= 2, use the next Chebyshev polynomial. U_1(x) = 2x.          */
    evals[1] = 2.0 * x;

    /*  U_{n}(x) = 2*x*U_{n-1}(x) - U_{n-2}(x). Compute.                      */
    for (n = two; n < length; ++n)
        evals[n] = 2.0 * x * evals[n - 1] - evals[n - 2];
}
/*  End of tmpl_Double_Chebyshev_U.                                           */
