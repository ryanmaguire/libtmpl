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
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      C_x (double):                                                         *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_SinCosPi:                                             *
 *              Simultaneously computes sin(pi t) and cos(pi t).              *
 *  Method:                                                                   *
 *      Use the asymptotic expansion for C(x):                                *
 *                                                                            *
 *                 1    1                                                     *
 *          C(x) ~ - + ---- sin(pi/2 x^2)                                     *
 *                 2   pi x                                                   *
 *                                                                            *
 *      To avoid precision loss in the computation of sin(pi/2 x^2) we use a  *
 *      double-double trick and split x into two parts, xhi and xlo, so that: *
 *                                                                            *
 *          x^2 = (xhi + xlo)^2                                               *
 *                xhi^2 + 2 xhi xlo + xlo^2                                   *
 *                                                                            *
 *      xhi is chosen to be the upper 16 bits, and xlo is the lower 36 bits.  *
 *      By doing this we guarantee that xhi^2 / 2 is an integer for all       *
 *      x > 2^17. Since sin(pi t) is periodic with period 2, we can           *
 *      disregard the xhi^2 term completely and concentrate solely on         *
 *      2 xhi xlo + xlo^2. This term is passed to the SinCosPi function. By   *
 *      doing this we avoid precision loss that occurs with taking the sine   *
 *      of the square of a large number. This only minimally impacts          *
 *      performance as well.                                                  *
 *  Notes:                                                                    *
 *      This function assumes the input is greater than 2^17.                 *
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
#ifndef TMPL_NORMALIZED_FRESNEL_COS_ASYMPTOTIC_LDOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_ASYMPTOTIC_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  The denominator of the asymptotic expansion is scaled by pi.              */
#define TMPL_ONE_PI (+3.14159265358979323846264338327950288419716939E+00L)

/*  Used to compute sin(pi t) and cos(pi t) simultaneously.                   */
extern void
tmpl_LDouble_SinCosPi(long double t, long double *sin_t, long double *cos_t);

/*  Different splitting values are needed, depending on the type. If the      *
 *  mantissa is N bits, the magic number is 2^(N - floor(N/3) + 1) + 1. This  *
 *  guarantees that for |x| > 2^floor(N/3) the high part is even, meaning     *
 *  xhi^2 / 2 is an integer. Since sin(pi x) and cos(pi x) are periodic, we   *
 *  can then discard this computation entirely. We need only concentrate on   *
 *  the lower N - floor(N/3) bits.                                            */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  52-bit mantissa, value is 2^36 + 1.                                       */
#define TMPL_LDOUBLE_SPLIT (6.8719476737E+10L)
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/*  112-bit mantissa, value is 2^76 + 1.                                      */
#define TMPL_LDOUBLE_SPLIT (+7.5557863725914323419137E+22L)
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  104-bit mantissa, value is 2^71 + 1.                                      */
#define TMPL_LDOUBLE_SPLIT (+2.361183241434822606849E+21L)
#else

/*  63-bit mantissa, value is 2^43 + 1.                                       */
#define TMPL_LDOUBLE_SPLIT (+8.796093022209E+12L)

#endif
/*  End of double vs. extended vs. double-double vs. quadruple.               */

/*  Function for computing the normalized Fresnel cosine of a large input.    */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Asymptotic(long double x)
{
    /*  Use the double-double trick, split x into two parts, high and low.    */
    const long double split = TMPL_LDOUBLE_SPLIT * x;
    const long double xhi = split - (split - x);
    const long double xlo = x - xhi;

    /*  The scale factor for the asymptotic expansion. For x > 2^17 we only   *
     *  need the first term of the approximation.                             */
    const long double t = 1.0L / (TMPL_ONE_PI * x);

    /*  For large x we have that xhi^2 / 2 is an integer. Since sin(pi t)     *
     *  is periodic with period 2, the xhi^2 term can be disregarded. The     *
     *  argument we then care about is pi (2 xhi xlo + xlo^2) / 2.            */
    long double sin_hi, cos_hi, sin_lo, cos_lo, sin_x;

    /*  Compute sin(pi/2 (2 xhi xlo + xlo^2)) using the angle sum formula.    */
    tmpl_LDouble_SinCosPi(xlo * xhi, &sin_hi, &cos_hi);
    tmpl_LDouble_SinCosPi(0.5L * xlo * xlo, &sin_lo, &cos_lo);
    sin_x = cos_hi*sin_lo + cos_lo*sin_hi;

    /*  The first term of the asymptotic expansion is all that is needed.     */
    return 0.5L + t * sin_x;
}
/*  End of tmpl_Double_Normalized_Fresnel_Cos_Asymptotic.                     */

/*  Undefine everything in case someone wants to include this file.           */
#undef TMPL_ONE_PI
#undef TMPL_LDOUBLE_SPLIT

#endif
/*  End of include guard.                                                     */
