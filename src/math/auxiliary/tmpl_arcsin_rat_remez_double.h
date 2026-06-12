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
 *                        tmpl_arcsin_rat_remez_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (10, 8) rational minimax approximation of asin(x)        *
 *      centered about the origin at double precision.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arcsin_Rat_Remez                                          *
 *  Purpose:                                                                  *
 *      Computes the (10, 8) rational minimax approximation for arcsin.       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      asin_x (double):                                                      *
 *          The rational minimax approximation of asin(x).                    *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The function f(x) = (asin(x) - x) / x^3 is even. We have pre-computed *
 *      the coefficients for the rational minimax function R(x) of degree     *
 *      (8, 8) for f(x). The odd terms have zero coefficients. We may thus    *
 *      compute the minimax approximation via:                                *
 *                                                                            *
 *                            a0 + a2 x^2 + ... + a8 x^8                      *
 *          asin(x) = x + x^3 --------------------------                      *
 *                            b0 + b2 x^2 + ... + b8 x^8                      *
 *                                                                            *
 *      Where the coefficients a_n and b_n are for the rational minimax       *
 *      approximation for f(x). These were pre-computed by the rational       *
 *      Remez exchange algorithm.                                             *
 *  Notes:                                                                    *
 *      Accurate for |x| < 0.5.                                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 1, 2023                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/06/01: Ryan Maguire                                                  *
 *      Corrected name and comments. This was previously called a "Pade"      *
 *      approximant, but it is not. The coefficients for the Pade approximant *
 *      and the rational minimax function are slightly different. To achieve  *
 *      the same precision the Pade approximation needs two more terms, one   *
 *      for the numerator and one for the denominator. That is, to attain     *
 *      double precision on [-0.5, 0.5] the (12, 10) Pade approximant is      *
 *      needed.                                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCSIN_RAT_REMEZ_DOUBLE_H
#define TMPL_ARCSIN_RAT_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+1.6666666666666675172610409335401762495970069423667E-01)
#define A01 (-2.9647442738212244852684254810912673101657174481766E-01)
#define A02 (+1.6001969221867813049084016184632874497094695883901E-01)
#define A03 (-2.5510481570872249173776491491771394448907125511346E-02)
#define A04 (+2.6066097969323856113412749790103952111930280796716E-04)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (-2.2288465642924490579275829949790393075345284377974E+00)
#define B02 (+1.6952419643599424152439428142515867324057155650851E+00)
#define B03 (-5.0120096652328631713045487959099718175996563925832E-01)
#define B04 (+4.5088915315077310386265964807853660211534733521946E-02)

/*  Helper macros for evaluating polynomials using Horner's method.           */
#define TMPL_NUM_EVAL(z) A00 + z * (A01 + z * (A02 + z * (A03 + z * A04)))
#define TMPL_DEN_EVAL(z) B00 + z * (B01 + z * (B02 + z * (B03 + z * B04)))

/*  Function for computing the (10, 8) minimax approximation for asin(x).     */
TMPL_CONST_FUNC
TMPL_STATIC_INLINE
double tmpl_Double_Arcsin_Rat_Remez(const double x)
TMPL_UNSEQUENCED
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const double x2 = x * x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const double p = TMPL_NUM_EVAL(x2);
    const double q = TMPL_DEN_EVAL(x2);
    const double r = x2 * p / q;

    /*  p/q is the minimax approximant for (asin(x) - x) / x^3.               */
    return x * r + x;
}
/*  End of tmpl_Double_Arcsin_Rat_Remez.                                      */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
