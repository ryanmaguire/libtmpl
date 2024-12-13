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
 *                       tmpl_modified_legendre_p_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the modified Legendre polynomials.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Modified_Legendre_P                                        *
 *  Purpose:                                                                  *
 *      Computes the modified Legendre polynomials using upwards recursion.   *
 *  Arguments:                                                                *
 *      evals (float * const):                                                *
 *          The array of evaluations. evals[n] stores the value b_n(x).       *
 *      x (float):                                                            *
 *          A real number. Typically this is between -1 and 1.                *
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
 *      From this one may prove the following recursion relation (see [1]):   *
 *                                                                            *
 *                    (2n + 5) x b   (x) - (n + 1) b (x)                      *
 *                                n+1               n                         *
 *          b   (x) = ----------------------------------                      *
 *           n+2                    n + 4                                     *
 *                                                                            *
 *      starting with b_0(x) = (1 - x^2)/2 and b_1(x) = x(1 - x^2)/2. We use  *
 *      this to compute b_n(x) in an upward fashion.                          *
 *  Error:                                                                    *
 *      The error depends on the number of modified Legendre polynomials      *
 *      requested. In general, the error for b_n(x) is on the order of:       *
 *                                                                            *
 *          Err = O(epsilon * n * b_n(x))                                     *
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
 *      2.) The domain of the modified Legendre polynomials is -1 <= x <= 1.  *
 *          There are no checks for this in the function and you may use this *
 *          for |x| > 1. The modified Legendre polynomials typically do not   *
 *          have much use when |x| > 1.                                       *
 *      3.) No checks for NaN or Infinity are made.                           *
 *  References:                                                               *
 *      1.) Maguire, R., French, R. (2024)                                    *
 *          "Applications of Legendre Polynomials for Fresnel Inversion       *
 *              and Occultation Observations"                                 *
 *      2.) Arfken, G., Weber, H., Harris, F. (2013)                          *
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
 *  Date:       December 13, 2024                                             *
 ******************************************************************************/

/*  Helper macro providing casting for C vs. C++ styles.                      */
#include <libtmpl/include/tmpl_compat_cast.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_orthogonal_polynomial_real.h>

/*  Standard library header file. The size_t type is found here.              */
#include <stddef.h>

/*  Computes the modified Legendre polynomials b_n(x) for n = 0 to length - 1.*/
void tmpl_Float_Modified_Legendre_P(float * const evals, float x, size_t length)
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

    /*  evals has at least one element allocated to it. b_0(x) = (1-x^2)/2.   */
    evals[0] = 0.5F*(1.0F - x*x);

    /*  If length is not greater than two, we can skip the recursion formula. *
     *  In this case, we are just computing b_0(x). Return.                   */
    if (length == one)
        return;

    /*  length >= 2, use the next modified polynomial: b_1(x) = x(1 - x^2)/2. *
     *  We have already computed (1 - x^2)/2, this is evals[0]. Simply scale  *
     *  this by x to compute b_1(x).                                          */
    evals[1] = x * evals[0];

    /*  Start the recursion formula, using an upwards iteration.              */
    for (n = two; n < length; ++n)
    {
        /*  Cast to float to avoid implicit conversions.                      */
        const float index = TMPL_CAST(n, float);

        /*  (n + 2) b_n(x) = (2n + 1) x b_{n-1}(x) - (n - 1) b_{n-2}(x).      */
        const float left = (2.0F*index + 1.0F) * x * evals[n - 1];
        const float right = (index - 1.0F) * evals[n - 2];

        /*  Dividing the above equation by "n + 2" gives b_{n}(x). Compute.   */
        evals[n] = (left - right) / (index + 2.0F);
    }
    /*  End of for-loop for the upward recurrence relation.                   */
}
/*  End of tmpl_Float_Modified_Legendre_P.                                    */
