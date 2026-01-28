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
 *            tmpl_normalized_fresnel_cos_asymptotic_large_ldouble            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for large positive inputs.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Normalized_Fresnel_Cos_Asymptotic_Large                  *
 *  Purpose:                                                                  *
 *      Computes C(x) for very large positive inputs.                         *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      fresnel_cos_x (long double):                                          *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_SinCosPi:                                            *
 *              Simultaneously computes sin(pi t) and cos(pi t).              *
 *      src/split/                                                            *
 *          tmpl_LDouble_Even_High_Split:                                     *
 *              Splits a long double into two parts so that x = xhi + xlo.    *
 *  Method:                                                                   *
 *      Use the asymptotic expansion for C(x):                                *
 *                                                                            *
 *                               -        -                                   *
 *                 1    1       |  pi   2  |                                  *
 *          C(x) ~ - + ---- sin |  --- x   |                                  *
 *                 2   pi x     |   2      |                                  *
 *                               -        -                                   *
 *                                                                            *
 *      To avoid precision loss in the computation of sin(pi/2 x^2) we use a  *
 *      double-double trick and split x into two parts, xhi and xlo, so that: *
 *                                                                            *
 *          x^2 = (xhi + xlo)^2                                               *
 *              = xhi^2 + 2 xhi xlo + xlo^2                                   *
 *                                                                            *
 *      For very large x, we have that xhi^2 / 2 is even. Since sin(pi t) is  *
 *      periodic with period 2, we may ignore the xhi^2 / 2 part of x^2.      *
 *      We compute sin(pi/2 x^2) using the angle-sum formula with the         *
 *      expression pi (xhi * xlo + xlo * xlo / 2).                            *
 *  Notes:                                                                    *
 *      1.) This function assumes the input is greater than 2^(N/2+2) where   *
 *          N is the number of bits in the mantissa of long double.           *
 *                                                                            *
 *      2.) Do not use this function for arguments greater than 2^N where N   *
 *          is the number of bits in the mantissa of long double. The         *
 *          computations of sin(pi x^2) and cos(pi x^2) are redundant since   *
 *          the final expression is divided by pi x, meaning the output is    *
 *          1 / 2 to long double precision. For extremely large inputs,       *
 *          simply return 1 / 2.                                              *
 *                                                                            *
 *      3.) There are no checks for NaN or infinity.                          *
 *                                                                            *
 *      4.) There are no checks for negative numbers. This function assumes   *
 *          the input is positive.                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 21, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_COS_ASYMPTOTIC_LARGE_LDOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_ASYMPTOTIC_LARGE_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  The splitting function is small enough that it can be inlined.            */
#if TMPL_USE_INLINE == 1

/*  Splitting function for getting the high part of a long double found here. */
#include <libtmpl/include/inline/split/tmpl_even_high_split_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern long double tmpl_LDouble_Even_High_Split(const long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  The denominator of the asymptotic expansion is scaled by pi.              */
extern const long double tmpl_ldouble_pi;

/*  Used to compute sin(pi t) and cos(pi t) simultaneously.                   */
extern void
tmpl_LDouble_SinCosPi(const long double t,
                      long double * TMPL_RESTRICT const sin_t,
                      long double * TMPL_RESTRICT const cos_t);

/*  Function for computing the normalized Fresnel cosine of a large input.    */
TMPL_STATIC_INLINE
long double
tmpl_LDouble_Normalized_Fresnel_Cos_Asymptotic_Large(const long double x)
{
    /*  Split the input into two parts. This allows us to compute the square  *
     *  of x more precisely.                                                  */
    const long double xhi = tmpl_LDouble_Even_High_Split(x);
    const long double xlo = x - xhi;

    /*  The scale factor for the asymptotic expansion. For large x we only    *
     *  need the first term of the approximation.                             */
    const long double t = 1.0L / (tmpl_ldouble_pi * x);

    /*  For large x, we have xhi^2 / 2 is an even integer. Since sin(pi t)    *
     *  is periodic with period 2, the xhi^2 term can be ignored. The         *
     *  argument we then care about is pi (2 xhi xlo + xlo^2) / 2.            */
    long double sin_hi, cos_hi, sin_lo, cos_lo, sin_x;

    /*  Compute sin(pi/2 (2 xhi xlo + xlo^2)) using the angle sum formula.    */
    tmpl_LDouble_SinCosPi(xlo * xhi, &sin_hi, &cos_hi);
    tmpl_LDouble_SinCosPi(0.5 * xlo * xlo, &sin_lo, &cos_lo);
    sin_x = cos_hi * sin_lo + cos_lo * sin_hi;

    /*  The first term of the asymptotic expansion is all that is needed.     */
    return 0.5L + t * sin_x;
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Cos_Asymptotic_Large.              */

#endif
/*  End of include guard.                                                     */
