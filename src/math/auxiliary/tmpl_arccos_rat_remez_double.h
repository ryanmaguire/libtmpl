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
 *                        tmpl_arccos_rat_remez_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (8, 8) rational minimax approximation of acos(x)         *
 *      centered about the origin at double precision.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arccos_Rat_Remez                                          *
 *  Purpose:                                                                  *
 *      Computes the (8, 8) rational minimax approximation for arccos.        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (double):                                                      *
 *          The rational minimax approximation of acos(x).                    *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The function f(x) = (acos(x) + x - pi/2) / x^3 is even. Pre-compute   *
 *      the coefficients for the rational minimax function R(x) of degree     *
 *      (8, 8) for f(x). The odd terms have zero coefficients. We may thus    *
 *      compute the minimax approximation via:                                *
 *                                                                            *
 *                                   a0 + a2 x^2 + ... + a8 x^8               *
 *          acos(x) = pi/2 - x + x^3 --------------------------               *
 *                                   b0 + b2 x^2 + ... + b8 x^8               *
 *                                                                            *
 *      Where the coefficients a_n and b_n are for the rational minimax       *
 *      approximation for f(x). These were pre-computed by the rational       *
 *      Remez exchange algorithm.                                             *
 *  Notes:                                                                    *
 *      Accurate for |x| < 0.5.                                               *
 *  References:                                                               *
 *      1.) Maguire, Ryan (2024)                                              *
 *          tmpld                                                             *
 *          https://github.com/ryanmaguire/libtmpl_data                       *
 *                                                                            *
 *          Python library providing an implementation of the rational        *
 *          Remez exchange algorithm. The coefficients for the                *
 *          approximation used by this function were computed using this.     *
 *                                                                            *
 *      2.) Tasissa, Abiy (2019)                                              *
 *          Function Approximation and the Remez Exchange Algorithm.          *
 *          https://sites.tufts.edu/atasissa/files/2019/09/remez.pdf          *
 *                                                                            *
 *          Survey of the Remez polynomial and Remez exchange algorithm.      *
 *          The implementation in tmpld is based on these notes.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_pade_double.c to just include this file. *
 *  2023/05/13: Ryan Maguire                                                  *
 *      Corrected name and comments. This was previously called a "Pade"      *
 *      approximant, but it is not. The coefficients for the Pade approximant *
 *      and the rational minimax function are slightly different. To achieve  *
 *      the same precision the Pade approximation needs more terms, two for   *
 *      the numerator and one for the denominator. That is, to attain double  *
 *      precision on [-0.5, 0.5] the (12, 10) Pade approximant is needed.     *
 *  2024/10/29: Ryan Maguire                                                  *
 *      In an effort to have reproducible results, the Remez coefficients are *
 *      now the exact same ones that are output from the Python script found  *
 *      in libtmpl_data. The previous coefficients were truncated.            *
 *  2024/10/29: Ryan Maguire                                                  *
 *      After some experimenting, I noticed that the (8, 8) rational Remez    *
 *      approximation is sufficient for double precision. Peak theoretical    *
 *      is 8.5 * 10^-17. Unit tests show the actual error is within 1 ULP of  *
 *      other libm implementations. Slight performance boost using this.      *
 *  2025/02/13: Ryan Maguire                                                  *
 *      Added references.                                                     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_RAT_REMEZ_DOUBLE_H
#define TMPL_ARCCOS_RAT_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

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
#define TMPL_POLYA_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))
#define TMPL_POLYB_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  The constant Pi / 2.                                                      */
extern const double tmpl_double_pi_by_two;

/*  Function for computing the (8, 8) minimax approximation for acos(x).      */
TMPL_STATIC_INLINE
double tmpl_Double_Arccos_Rat_Remez(double x)
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const double x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const double p = TMPL_POLYA_EVAL(x2);
    const double q = TMPL_POLYB_EVAL(x2);
    const double r = x2 * p / q;

    /*  p/q is the rational Remez approximation for (acos(x) - pi/2 + x)/x^3. *
     *  Solving for acos(x), we get pi/2 - (x + x*x2*p/q).                    */
    return tmpl_double_pi_by_two - (x + x*r);
}
/*  End of tmpl_Double_Arccos_Rat_Remez.                                      */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
