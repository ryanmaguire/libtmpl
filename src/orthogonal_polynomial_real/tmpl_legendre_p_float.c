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
 *                           tmpl_legendre_p_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the evaluation of the Legendre polynomials at a real number. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Legendre_P                                                 *
 *  Purpose:                                                                  *
 *      Computes P_n(x) for a fixed x and for n = 0, 1, ..., length - 1.      *
 *  Arguments:                                                                *
 *      evals (float * const):                                                *
 *          The array of evaluations. evals[n] stores the value P_n(x).       *
 *      x (float):                                                            *
 *          A real number. Typically this is between -1 and 1.                *
 *      length (size_t):                                                      *
 *          The number of elements in the array. The highest Legendre         *
 *          polynomial that is computed is P_{length - 1}(x).                 *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      For length = 0, abort the computation since the array is empty. For   *
 *      length = 1 or length = 2, use the explicit formulas for the Legendre  *
 *      polynomials. They are:                                                *
 *                                                                            *
 *          P (x) = 1                                                         *
 *           0                                                                *
 *                                                                            *
 *          P (x) = x                                                         *
 *           1                                                                *
 *                                                                            *
 *      For length > 2, use Bonnet’s recursion formula (see [2], in French):  *
 *                                                                            *
 *                  (2n - 1) x P   (x) - (n - 1) P   (x)                      *
 *          P (x) =             n-1               n-2                         *
 *           n      ------------------------------------                      *
 *                                   n                                        *
 *                                                                            *
 *      Doing this in an upward iterative fashion is linear in time, whereas  *
 *      naively applying this recursive formula would be exponential. We      *
 *      perform the upwards linear expansion and return.                      *
 *  Error:                                                                    *
 *      The error depends on the number of Legendre polynomials requested.    *
 *      In general, the error for P_n(x) is on the order of:                  *
 *                                                                            *
 *          Err = O(epsilon * n * P_n(x))                                     *
 *                                                                            *
 *      For extremely large n, one may obtain a meaningless result.           *
 *      Since epsilon = 2^-52 ~= 2x10^-16 on most machines, one would need    *
 *      n to be on an order of magnitude equal to the reciprocal of epsilon   *
 *      to achieve completely meaningless results, but for n ~ 10^7 the error *
 *      may accumulate to single precision accuracy (~10^-8 relative error).  *
 *  Notes:                                                                    *
 *      1.) This functions checks for NULL pointers, and checks if length is  *
 *          zero. If length is non-zero, and if evals is not NULL, then the   *
 *          evals array must have at least length elements allocated to it.   *
 *      2.) The domain of the Legendre polynomials is -1 <= x <= 1. There are *
 *          no checks for this in the function, and you may use this routine  *
 *          for |x| > 1. The Legendre polynomials typically do not have much  *
 *          use when |x| > 1.                                                 *
 *      3.) No checks for NaN or Infinity are made.                           *
 *  References:                                                               *
 *      1.) McQuarrie, Donald (2003),                                         *
 *          "Mathematical Methods for Scientists and Engineers",              *
 *          University Science Books, ISBN 1-891389-29-7,                     *
 *          Chapter 14 "Orthogonal Polynomials and Sturm-Liouville Problems"  *
 *      2.) Bonnet, Ossian (1852),                                            *
 *          "These de Mecanique. Sur le Developpement des Fonctions en        *
 *              Series Ordonnees Suivant le Fonctions Xn et Yn"               *
 *          Journal de Mathematiques Pures et Appliquees,                     *
 *          1st Series, Vol. 17., Pages 265-300,                              *
 *          See Theorem V on page 267 for the original proof of Bonnet's      *
 *          Recursion Formula.                                                *
 *      3.) Arfken, G., Weber, H., Harris, F. (2013)                          *
 *          "Mathematical Methods for Physicists, Seventh Edition"            *
 *          Academic Press, Elsevier                                          *
 *          Chapter 15 "Legendre Functions"                                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_compat_cast.h:                                                   *
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
#include <libtmpl/include/tmpl_compat_cast.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_orthogonal_polynomial_real.h>

/*  Standard library header file. The size_t type is found here.              */
#include <stddef.h>

/*  Computes the Legendre polynomials P_n(x) for n = 0, 1, ..., length - 1.   */
void tmpl_Float_Legendre_P(float * const evals, float x, size_t length)
{
    /*  Cast some constant values to size_t, avoiding implicit conversion.    */
    const size_t zero = TMPL_CAST(0, size_t);
    const size_t one = TMPL_CAST(1, size_t);
    const size_t two = TMPL_CAST(2, size_t);

    /*  Declare necessary variables. C89 requires declarations at the top of  *
     *  a block. n is used for indexing the Legendre polynomials.             */
    size_t n;

    /*  Check for NULL pointers and empty arrays. Nothing to do in this case. */
    if (!evals || length == zero)
        return;

    /*  evals has at least one element allocated to it. P_0(x) = 1. Use this. */
    evals[0] = 1.0F;

    /*  If length is not greater than two, we can skip Bonnet's recursion     *
     *  formula. In this case, we are just computing P_0(x). Return.          */
    if (length == one)
        return;

    /*  length >= 2, use the next Legendre polynomial. P_1(x) = x.            */
    evals[1] = x;

    /*  Start Bonnet's recursion, using an upwards iteration.                 */
    for (n = two; n < length; ++n)
    {
        /*  Cast to float to avoid implicit conversions.                      */
        const float index = TMPL_CAST(n, float);

        /*  n P_n(x) = (2n - 1) x P_{n-1}(x) - (n - 1) P_{n-2}(x). Compute.   */
        const float left = (2.0F*index - 1.0F) * x * evals[n - 1];
        const float right = (index - 1.0F) * evals[n - 2];

        /*  Dividing the above equation by "n" gives P_{n}(x). Compute this.  */
        evals[n] = (left - right) / index;
    }
    /*  End of for-loop for the upward recurrence using Bonnet's formula.     */
}
/*  End of tmpl_Float_Legendre_P.                                             */
