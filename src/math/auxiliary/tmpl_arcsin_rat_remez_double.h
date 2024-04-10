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
 *      (10, 8) for f(x). The odd terms have zero coefficients. We may thus   *
 *      compute the minimax approximation via:                                *
 *                                                                            *
 *                            a0 + a2 x^2 + ... + a10 x^10                    *
 *          asin(x) = x + x^3 ----------------------------                    *
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

/*  Coefficients for the numerator.                                           */
#define A00 (+1.66666666666666657415E-01)
#define A01 (-3.25565818622400915405E-01)
#define A02 (+2.01212532134862925881E-01)
#define A03 (-4.00555345006794114027E-02)
#define A04 (+7.91534994289814532176E-04)
#define A05 (+3.47933107596021167570E-05)

/*  Coefficients for the denominator.                                         */
#define B00 (+1.00000000000000000000E+00)
#define B01 (-2.40339491173441421878E+00)
#define B02 (+2.02094576023350569471E+00)
#define B03 (-6.88283971605453293030E-01)
#define B04 (+7.70381505559019352791e-02)

/*  Helper macros for evaluating polynomials using Horner's method.           */
#define TMPL_POLYA_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))
#define TMPL_POLYB_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  Function for computing the (10, 8) minimax approximation for asin(x).     */
TMPL_STATIC_INLINE
double tmpl_Double_Arcsin_Rat_Remez(double x)
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const double x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const double p = TMPL_POLYA_EVAL(x2);
    const double q = TMPL_POLYB_EVAL(x2);
    const double r = x2*p/q;

    /*  p/q is the minimax approximant for (asin(x) - x) / x^3.               */
    return x*r + x;
}
/*  End of tmpl_Double_Arcsin_Rat_Remez.                                      */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
