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
 *                tmpl_normalized_fresnel_sin_asymptotic_double               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine for large positive inputs.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Sin_Asymptotic                         *
 *  Purpose:                                                                  *
 *      Computes S(x) for large positive inputs.                              *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      S_x (double):                                                         *
 *          The normalized Fresnel sine of x.                                 *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_SinCosPi:                                             *
 *              Simultaneously computes sin(pi t) and cos(pi t).              *
 *  Method:                                                                   *
 *      Use the asymptotic expansion for S(x):                                *
 *                                                                            *
 *                 1    1                                                     *
 *          S(x) ~ - - ---- cos(pi/2 x^2)                                     *
 *                 2   pi x                                                   *
 *                                                                            *
 *      To avoid precision loss in the computation of cos(pi/2 x^2) we use a  *
 *      double-double trick and split x into two parts, xhi and xlo, so that: *
 *                                                                            *
 *          x^2 = (xhi + xlo)^2                                               *
 *              = xhi^2 + 2 xhi xlo + xlo^2                                   *
 *                                                                            *
 *      xhi is chosen to be the upper 16 bits, and xlo is the lower 36 bits.  *
 *      By doing this we guarantee that xhi^2 / 2 is an even integer for all  *
 *      x > 2^17. Since cos(pi t) is periodic with period 2, we can           *
 *      disregard the xhi^2 term completely and concentrate solely on         *
 *      2 xhi xlo + xlo^2. This term is passed to the SinCosPi function. By   *
 *      doing this we avoid precision loss that occurs with taking the cosine *
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
 *  Date:       January 21, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_SIN_ASYMPTOTIC_LARGE_DOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_SIN_ASYMPTOTIC_LARGE_DOUBLE_H

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

/*  Function for computing the normalized Fresnel sine of a large input.      */
TMPL_STATIC_INLINE
double tmpl_Double_Normalized_Fresnel_Sin_Asymptotic_Large(const double x)
{
    /*  Split the input into two parts. This allows us to compute the square  *
     *  of x more precisely.                                                  */
    const double xhi = tmpl_Double_Even_High_Split(x);
    const double xlo = x - xhi;

    /*  The scale factor for the asymptotic expansion. For x > 2^28 we only   *
     *  need the first term of the approximation.                             */
    const double t = 1.0 / (tmpl_double_pi * x);

    /*  For x > 2^28, we have xhi^2 / 2 is an even integer. Since cos(pi t)   *
     *  is periodic with period 2, the xhi^2 term can be ignored. The         *
     *  argument we then care about is pi (2 xhi xlo + xlo^2) / 2.            */
    double sin_hi, cos_hi, sin_lo, cos_lo, minus_cos_x;

    /*  Compute cos(pi/2 (2 xhi xlo + xlo^2)) using the angle sum formula.    */
    tmpl_Double_SinCosPi(xlo * xhi, &sin_hi, &cos_hi);
    tmpl_Double_SinCosPi(0.5 * xlo * xlo, &sin_lo, &cos_lo);
    minus_cos_x = sin_hi * sin_lo - cos_hi * cos_lo;

    /*  The first term of the asymptotic expansion is all that is needed.     */
    return 0.5 + t * minus_cos_x;
}
/*  End of tmpl_Double_Normalized_Fresnel_Sin_Asymptotic.                     */

/*  Undefine everything in case someone wants to include this file.           */
#undef TMPL_ONE_PI
#undef TMPL_SPLITTING_FACTOR

#endif
/*  End of include guard.                                                     */
