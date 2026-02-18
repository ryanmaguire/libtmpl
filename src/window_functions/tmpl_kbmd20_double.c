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
 *                       tmpl_kaiser_bessel_2_0_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Kaiser-Bessel window with alpha = 2 pi.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Kaiser_Bessel_2_0                                         *
 *  Purpose:                                                                  *
 *      Computes the Kaiser-Bessel window function with alpha set to 2 pi.    *
 *      This is defined in terms of modified Bessel functions:                *
 *                                                                            *
 *                        I_0(2 pi sqrt(1 - (2x/W)^2))                        *
 *          kb20(x, W) =  ----------------------------                        *
 *                                 I_0(2 pi)                                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the input data value.                              *
 *      W (double):                                                           *
 *          The width of the window. Units are the same as x.                 *
 *  Output:                                                                   *
 *      window (double):                                                      *
 *          The Kaiser-Bessel window with alpha = 2 Pi and window width W     *
 *          evaluated at the point x.                                         *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Compute the value 1 - (2x/W)^2. Check that sign bit. It the       *
 *          value is negative, then x falls outside the window and 0 is       *
 *          returned. Otherwise a (9, 9) Pade approximant is used.            *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Same as IEEE-754 method but check if 1 - (2x/W)^2 is negative     *
 *          using comparisons, rather than examining the sign bit. This is    *
 *          slightly slower on some machines, but not by much.                *
 *  Error:                                                                    *
 *      Max Relative Error: 2E-18                                             *
 *      RMS Relative Error: 7E-19                                             *
 *                                                                            *
 *      These values are theoretical errors from the Pade approximant.        *
 *      Actual error for 64-bit double is 1 ULP, 2^-52 ~= 2.22E-16.           *
 *  Notes:                                                                    *
 *      No checks for x = NaN or x = +/- Inf are performed. For x = +/- inf,  *
 *      1 - (x/W)^2 will be negative, so zero is returned. For NaN the result *
 *      can be +/- NaN or zero.                                               *
 *                                                                            *
 *      No checks for W = NaN, +/- Inf, or zero are performed. W = zero will  *
 *      result in divide-by-zero, and NaN or Inf may return.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing TMPL_HAS_IEEE754_DOUBLE macro.             *
 *  2.) tmpl_window_functions.h:                                              *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 27, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/05: Ryan Maguire                                                  *
 *      Changed algorithm from Taylor series to Pade approximant. This        *
 *      improves the precision from 1E-10 to 2E-16, double precision.         *
 *  2023/01/06: Ryan Maguire                                                  *
 *      Added license and comments.                                           *
 ******************************************************************************/

/*  Function prototype found here.                                            */
extern double
tmpl_Double_Modified_Kaiser_Bessel_2_0(const double x, const double width);

/*  TMPL_NAN macro found here which provides double precision NaN.            */
#include <libtmpl/include/nan/tmpl_nan_double.h>

/*  TMPL_HAS_IEEE754_DOUBLE macro and tmpl_IEEE754_Double type given here.    */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Rational Remez approximation for the modified Kaiser-Bessel window.       */
#include "auxiliary/tmpl_kbmd20_rat_remez_double.h"

/*  Tail-end expansion using a shifted rational Remez approximation.          */
#include "auxiliary/tmpl_kbmd20_tail_end_double.h"

/*  With IEEE-754 support we can check if the input falls within the window   *
 *  more efficiently. This gives a slight performance boost.                  */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Double precision Kaiser-Bessel window with alpha = 2 pi.                  */
double tmpl_Double_Modified_Kaiser_Bessel_2_0(const double x, const double width)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2))/I_0(2pi) for values      *
     *  inside the window. To determine if x falls in the window we need to   *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    w.r = x / width;

    if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 0x02U)
        return tmpl_Double_KBMD20_Rat_Remez(w.r);

    if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 0x01U)
    {
        w.bits.sign = 0x00U;
        return tmpl_Double_KBMD20_Tail_End(w.r);
    }

    return 0.0;
}
/*  End of tmpl_Double_Kaiser_Bessel_2_0.                                     */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/*  Double precision Kaiser-Bessel window with alpha = 2 pi.                  */
double tmpl_Double_Kaiser_Bessel_2_0(double x, double W)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double numer, denom;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2))/I_0(2pi) for values      *
     *  inside the window. To determine if x falls in the window we need to   *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const double c = 2.0*x/W;
    const double arg = 1.0 - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (arg < 0.0)
        return 0.0;

    /*  Otherwise x falls inside the window. Compute via the Pade approximant.*/
    numer = TMPL_PADE_HELPER(arg, P);
    denom = TMPL_PADE_HELPER(arg, Q);
    return numer / denom;
}
/*  End of tmpl_Double_Kaiser_Bessel_2_0.                                     */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
