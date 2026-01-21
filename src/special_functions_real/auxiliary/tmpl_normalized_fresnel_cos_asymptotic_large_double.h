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
 *            tmpl_normalized_fresnel_cos_asymptotic_large_double             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for large positive inputs.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Cos_Asymptotic_Large                   *
 *  Purpose:                                                                  *
 *      Computes C(x) for very large positive inputs.                         *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      fresnel_cos_x (double):                                               *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_SinCosPi:                                             *
 *              Simultaneously computes sin(pi t) and cos(pi t).              *
 *      src/split/                                                            *
 *          tmpl_Double_Even_High_Split:                                      *
 *              Splits a double into two parts so that x = xhi + xlo.         *
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
 *      For x > 2^28, we have that xhi^2 / 2 is even. Since sin(pi t) is      *
 *      periodic with period 2, we may ignore the xhi^2 / 2 part of x^2.      *
 *      We compute sin(pi/2 x^2) using the angle-sum formula with the         *
 *      expression pi (xhi * xlo + xlo * xlo / 2).                            *
 *  Notes:                                                                    *
 *      1.) This function assumes the input is greater than 2^28.             *
 *                                                                            *
 *      2.) Do not use this function for arguments greater than 2^52. The     *
 *          computations of sin(pi x^2) and cos(pi x^2) are redundant since   *
 *          the final expression is divided by pi x, meaning the output is    *
 *          1 / 2 to double precision. For extremely large inputs, simply     *
 *          return 1 / 2.                                                     *
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
#ifndef TMPL_NORMALIZED_FRESNEL_COS_ASYMPTOTIC_LARGE_DOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_ASYMPTOTIC_LARGE_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  The splitting function is small enough that it can be inlined.            */
#if TMPL_USE_INLINE == 1

/*  Splitting function for retrieving the high part of a double found here.   */
#include <libtmpl/include/inline/split/tmpl_even_high_split_double.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern double tmpl_Double_Even_High_Split(const double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  The denominator of the asymptotic expansion is scaled by pi.              */
extern const double tmpl_double_pi;

/*  Used to compute sin(pi t) and cos(pi t) simultaneously.                   */
extern void
tmpl_Double_SinCosPi(const double t,
                     double * TMPL_RESTRICT const sin_t,
                     double * TMPL_RESTRICT const cos_t);

/*  Function for computing the normalized Fresnel cosine of a large input.    */
TMPL_STATIC_INLINE
double tmpl_Double_Normalized_Fresnel_Cos_Asymptotic_Large(const double x)
{
    /*  Split the input into two parts. This allows us to compute the square  *
     *  of x more precisely.                                                  */
    const double xhi = tmpl_Double_Even_High_Split(x);
    const double xlo = x - xhi;

    /*  The scale factor for the asymptotic expansion. For x > 2^28 we only   *
     *  need the first term of the approximation.                             */
    const double t = 1.0 / (tmpl_double_pi * x);

    /*  For x > 2^28, we have xhi^2 / 2 is an even integer. Since sin(pi t)   *
     *  is periodic with period 2, the xhi^2 term can be ignored. The         *
     *  argument we then care about is pi (2 xhi xlo + xlo^2) / 2.            */
    double sin_hi, cos_hi, sin_lo, cos_lo, sin_x;

    /*  Compute sin(pi/2 (2 xhi xlo + xlo^2)) using the angle sum formula.    */
    tmpl_Double_SinCosPi(xlo * xhi, &sin_hi, &cos_hi);
    tmpl_Double_SinCosPi(0.5 * xlo * xlo, &sin_lo, &cos_lo);
    sin_x = cos_hi * sin_lo + cos_lo * sin_hi;

    /*  The first term of the asymptotic expansion is all that is needed.     */
    return 0.5 + t * sin_x;
}
/*  End of tmpl_Double_Normalized_Fresnel_Cos_Asymptotic_Large.               */

#endif
/*  End of include guard.                                                     */
