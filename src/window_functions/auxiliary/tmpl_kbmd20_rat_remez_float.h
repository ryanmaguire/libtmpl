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
 *                        tmpl_kbmd20_rat_remez_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) for small x.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_KBMD20_Rat_Remez                                           *
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) using a        *
 *      rational Remez approximation for small arguments.                     *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      kbmd20_x (float):                                                     *
 *          The modified Kaiser-Bessel window (alpha = 2) of x.               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the (6, 4) rational Remez approximation for the  *
 *      modified Kaiser-Bessel window (alpha = 2) have been pre-computed on   *
 *      the interval [-1/4, 1/4]. Since the window is an even function, half  *
 *      of the coefficients are zero, meaning we only have 4 non-zero terms   *
 *      in the numerator and 3 non-zero terms in the denominator. The         *
 *      approximation is performed using Horner's method for the numerator    *
 *      and denominator, and then returning their ratio.                      *
 *  Notes:                                                                    *
 *      1.) Accurate to single precision for |x| < 0.25.                      *
 *                                                                            *
 *      2.) This function assumes a normalized window of width 1 is being     *
 *          used on the interval [-1/2, 1/2].                                 *
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
#ifndef TMPL_KBMD20_RAT_REMEZ_FLOAT_H
#define TMPL_KBMD20_RAT_REMEZ_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.9999999704619642565451752785030992179426086404505E-01F)
#define A01 (-8.7495862521825602318475474174062426666292026837914E+00F)
#define A02 (+2.5883381339572181262810579798201604371201486548716E+01F)
#define A03 (-2.7982041746437019074211960987898390264473565102788E+01F)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (+2.9018318527422568574967235170130839088968758909704E+00F)
#define B02 (+3.1236128502204739389502347344023492877271183319789E+00F)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z * (A01 + z * (A02 + z * A03))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z * (B01 + z * B02)

/*  Computes the modified Kaiser-Bessel window via a rational Remez expansion.*/
TMPL_STATIC_INLINE
float tmpl_Float_KBMD20_Rat_Remez(const float x)
{
    /*  The polynomials are in terms of x^2. Compute.                         */
    const float x2 = x * x;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const float numer = TMPL_NUM_EVAL(x2);
    const float denom = TMPL_DEN_EVAL(x2);

    /*  The modified Kaiser-Bessel window is the ratio.                       */
    return numer / denom;
}
/*  End of tmpl_Float_KBMD20_Rat_Remez.                                       */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
