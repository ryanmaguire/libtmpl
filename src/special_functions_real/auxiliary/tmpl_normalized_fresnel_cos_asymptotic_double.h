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
 *                tmpl_normalized_fresnel_cos_asymptotic_double               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for large positive inputs.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Cos_Asymptotic                         *
 *  Purpose:                                                                  *
 *      Computes C(x) for large positive inputs.                              *
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
 *          tmpl_Double_High_Split:                                           *
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
 *      xhi is chosen to be the upper 16 bits, and xlo is the lower 36 bits.  *
 *      By doing this we guarantee that xhi^2 / 2 is an even integer for all  *
 *      x > 2^17. Since sin(pi t) is periodic with period 2, we can           *
 *      disregard the xhi^2 term completely and concentrate solely on         *
 *      2 xhi xlo + xlo^2. This term is passed to the SinCosPi function. By   *
 *      doing this we avoid precision loss that occurs with taking the sine   *
 *      of the square of a large number. This only minimally impacts          *
 *      performance as well.                                                  *
 *  Notes:                                                                    *
 *      1.) This function assumes the input is greater than 2^17.             *
 *                                                                            *
 *      2.) Do not use this function for arguments greater than 2^52. The     *
 *          computation of sin(pi x^2) and cos(pi x^2) are redundant since    *
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
 *  Date:       July 8, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_COS_ASYMPTOTIC_DOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_ASYMPTOTIC_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  The splitting function is small enough that it can be inlined.            */
#if TMPL_USE_INLINE == 1

/*  Splitting function for retrieving the high part of a double found here.   */
#include <libtmpl/include/inline/split/tmpl_high_split_double.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern double tmpl_Double_High_Split(const double x, const double splitter);

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
double tmpl_Double_Normalized_Fresnel_Cos_Asymptotic(const double x)
{
    /*  We use a double-double trick to split x into two parts, high and low. *
     *  The magic number 68719476737 is 2^(52 - 16) + 1. Hence xhi has the    *
     *  upper 16 bits of the mantissa and xlo has the lower 36 bits.          */
    const double splitter = +6.8719476737E+10;

    /*  Split the input into two parts. This allows us to compute the square  *
     *  of x more precisely.                                                  */
    const double xhi = tmpl_Double_High_Split(x, splitter);
    const double xlo = x - xhi;

    /*  The scale factor for the asymptotic expansion. For x > 2^17 we only   *
     *  need the first term of the approximation.                             */
    const double t = 1.0 / (tmpl_double_pi * x);

    /*  For x > 2^17, we have xhi^2 / 2 is an even integer. Since sin(pi t)   *
     *  is periodic with period 2, the xhi^2 term can be disregarded. The     *
     *  argument we then care about is pi (2 xhi xlo + xlo^2) / 2.            */
    double sin_hi, cos_hi, sin_lo, cos_lo, sin_x;

    /*  Compute sin(pi/2 (2 xhi xlo + xlo^2)) using the angle sum formula.    */
    tmpl_Double_SinCosPi(xlo * xhi, &sin_hi, &cos_hi);
    tmpl_Double_SinCosPi(0.5 * xlo * xlo, &sin_lo, &cos_lo);
    sin_x = cos_hi * sin_lo + cos_lo * sin_hi;

    /*  The first term of the asymptotic expansion is all that is needed.     */
    return 0.5 + t * sin_x;
}
/*  End of tmpl_Double_Normalized_Fresnel_Cos_Asymptotic.                     */

#endif
/*  End of include guard.                                                     */
