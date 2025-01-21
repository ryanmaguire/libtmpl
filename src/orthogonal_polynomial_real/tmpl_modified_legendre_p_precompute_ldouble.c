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
 *                 tmpl_modified_legendre_p_precompute_ldouble                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes modified Legendre polynomials from the Legendre polynomials. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Modified_Legendre_P_Precompute                           *
 *  Purpose:                                                                  *
 *      Computes the modified Legendre polynomials from the precomputed       *
 *      Legendre polynomials. That is, given P_n(x) precomputed for n = 0, 1, *
 *      ..., length, this computes the modified Legendre polynomials for      *
 *      n = 0, 1, ..., length - 1.                                            *
 *  Arguments:                                                                *
 *      evals (long double * TMPL_RESTRICT const):                            *
 *          The array of evaluations. evals[n] stores the value b_n(x).       *
 *      legendre (const long double * TMPL_RESTRICT const):                   *
 *          The pre-computed Legendre polynomials, P_n(x). Note that we need  *
 *          P_n(x) for n = 0, 1, ..., length - 1, length. Hence the size of   *
 *          "legendre" must be at least "length + 1".                         *
 *      length (size_t):                                                      *
 *          The number of elements in the array. The highest modified         *
 *          Legendre polynomial that is computed is b_{length - 1}(x).        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The modified Legendre polynomials are defined in terms of the         *
 *      Legendre polynomials. They are:                                       *
 *                                                                            *
 *                  P (x) - x P   (x)                                         *
 *          b (x) =  n         n+1                                            *
 *           n      -----------------                                         *
 *                        n + 2                                               *
 *                                                                            *
 *      This is computed for n = 0, 1, ..., length-1 in a for loop.           *
 *  Error:                                                                    *
 *      Assuming the Legendre polynomials were correctly computed, one should *
 *      expect the error in b_n(x) to be O(epsilon x P_{n+1}(x))              *
 *  Notes:                                                                    *
 *      1.) This functions checks for NULL pointers, and checks if length is  *
 *          zero. If length is non-zero, and if evals is not NULL, then the   *
 *          evals array must have at least length elements allocated to it.   *
 *      2.) The legendre array must have at least length + 1 elements.        *
 *      3.) The domain of the Legendre polynomials is -1 <= x <= 1. There are *
 *          no checks for this in the function, and you may use this routine  *
 *          for |x| > 1. The Legendre polynomials typically do not have much  *
 *          use when |x| > 1.                                                 *
 *      4.) No checks for NaN or Infinity are made.                           *
 *      5.) On compilers with restrict (C99 or higher), TMPL_RESTRICT expands *
 *          to restrict. To properly use this function, the "evals" array and *
 *          the "legendre" array should be different.                         *
 *  References:                                                               *
 *      1.) McQuarrie, Donald (2003),                                         *
 *          "Mathematical Methods for Scientists and Engineers",              *
 *          University Science Books, ISBN 1-891389-29-7,                     *
 *          Chapter 14 "Orthogonal Polynomials and Sturm-Liouville Problems"  *
 *      2.) Arfken, G., Weber, H., Harris, F. (2013)                          *
 *          "Mathematical Methods for Physicists, Seventh Edition"            *
 *          Academic Press, Elsevier                                          *
 *          Chapter 15 "Legendre Functions"                                   *
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

/*  Computes the modified Legendre polynomials b_n(x) from P_n(x).            */
void
tmpl_LDouble_Modified_Legendre_P_Precompute(
    long double * TMPL_RESTRICT const evals,
    const long double * TMPL_RESTRICT const legendre,
    size_t length
)
{
    /*  Cast some constant values to size_t, avoiding implicit conversion.    */
    const size_t zero = TMPL_CAST(0, size_t);
    const size_t two = TMPL_CAST(2, size_t);

    /*  Declare necessary variables. C89 requires declarations at the top of  *
     *  a block. n is used for indexing the modified Legendre polynomials.    */
    size_t n;

    /*  x is the input value, which is obtained from P_1(x).                  */
    long double x;

    /*  Check for NULL pointers and empty arrays. Nothing to do in this case. */
    if (!evals || !legendre || length == zero)
        return;

    /*  x can be recovered from P_n simplify because P_1(x) = x.              */
    x = legendre[1];

    /*  The modified Legendre polynomials are computed iteratively from the   *
     *  normal Legendre polynomial. b_n(x) requires P_n(x) and P_{n+1}(x).    */
    for (n = zero; n < length; ++n)
    {
        /*  Cast to long double to avoid implicit conversions.                */
        const long double denom = TMPL_CAST(n + two, long double);

        /*  b_n(x) = (P_n(x) - x P_{n+1}(x)) / (n + 2). Compute.              */
        evals[n] = (legendre[n] - x * legendre[n + 1]) / denom;
    }
    /*  End of for-loop for the modified Legendre polynomials.                */
}
/*  End of tmpl_LDouble_Modified_Legendre_P_Precompute.                       */
