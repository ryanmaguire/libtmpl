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
 *                         tmpl_kbmd20_tail_end_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2).               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_KBMD20_Tail_End                                            *
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) using a        *
 *      rational Remez approximation for 1 / 4 <= x <= 1 / 2.                 *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      kbmd20_x (float):                                                     *
 *          The Kaiser-Bessel window (alpha = 2) of x.                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The modified Kaiser-Bessel window can be expanded about x = 1 / 2 in  *
 *      terms of x - 1 / 2. The coefficients for the (4, 3) rational Remez    *
 *      approximation for the function:                                       *
 *                                                                            *
 *                 KBMD20(x + 1 / 2)                                          *
 *          f(x) = -----------------                                          *
 *                         x                                                  *
 *                                                                            *
 *      on the interval [-1/4, 0] (the limit of f at zero is used to avoid a  *
 *      division by zero), where KBMD20 represents the modified Kaiser-Bessel *
 *      window with alpha = 2, have been pre-computed below. Given x with     *
 *      1 / 4 <= x <= 1 / 2, we translate x into this interval using:         *
 *                                                                            *
 *                     1                                                      *
 *          t(x) = x - -                                                      *
 *                     2                                                      *
 *                                                                            *
 *      and then return t(x) * P(t(x)) / Q(t(x)), where P and Q are the       *
 *      numerator and denominator, respectively, for the degree (4, 3)        *
 *      rational minimax approximation for f.                                 *
 *                                                                            *
 *      Note that since we scale the result by t(x), the approximation is     *
 *      zero, exact, when x = 1 / 2. That is, the window goes to zero at the  *
 *      right endpoint in the window.                                         *
 *  Notes:                                                                    *
 *      1.) Accurate to single precision for 0.25 <= x <= 0.5.                *
 *                                                                            *
 *      2.) This function assumes a normalized window of width 1 is being     *
 *          used on the interval [-1/2, 1/2].                                 *
 *                                                                            *
 *      3.) This function does not accept negative inputs. Use the absolute   *
 *          value of the input if -1/2 <= x <= -1/4.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 19, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_KBMD20_TAIL_END_FLOAT_H
#define TMPL_KBMD20_TAIL_END_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (-4.5847278991051562429089311564130550204183655446957E-01F)
#define A01 (+4.2216425019193539697002975438431052674480091761243E+00F)
#define A02 (-1.2551738887360819562058794676932301273511240069298E+01F)
#define A03 (+2.7374513328524846695902966093754384053577239699204E+00F)
#define A04 (+3.9554502750538812674946293585030300771581622094548E+01F)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (-3.3834093307139033761084868850712687163361186251222E-01F)
#define B02 (+8.3142381782288784660525927014063839963467740729558E-01F)
#define B03 (-3.5418103505992050463225988987775087666572028554388E+00F)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z * (A01 + z * (A02 + z * (A03 + z * A04)))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z * (B01 + z * (B02 + z * B03))

/*  Computes the modified Kaiser-Bessel window via a rational Remez expansion.*/
TMPL_STATIC_INLINE
float tmpl_Float_KBMD20_Tail_End(const float x)
{
    /*  The polynomials are in terms of x - 1 / 2. Compute.                   */
    const float shift = x - 0.5F;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const float numer = TMPL_NUM_EVAL(shift);
    const float denom = TMPL_DEN_EVAL(shift);

    /*  The Kaiser-Bessel window is the ratio scaled by the translation.      */
    return shift * numer / denom;
}
/*  End of tmpl_Float_KBMD20_Tail_End.                                        */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
