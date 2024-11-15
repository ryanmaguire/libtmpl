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
 *      Accurate for |x| < 1.                                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 15, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SINH_RAT_REMEZ_DOUBLE_H
#define TMPL_SINH_RAT_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.6666666666666654025173001455235362542672257136354E-01)
#define A01 (+5.9813406128811409066694066192871242671864693605473E-03)
#define A02 (+9.2436577905147168605551794800337606637491093467698E-05)
#define A03 (+5.3691681708737223014278619667055633690566078199818E-07)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (-1.4111956322767531134831386699657059518162619062169E-02)
#define B02 (+6.9741093725010168426383849295551508778267039294456E-05)

/*  Helper macros for evaluating polynomials using Horner's method.           */
#define TMPL_POLYA_EVAL(z) A00 + z*(A01 + z*(A02 + z*A03))
#define TMPL_POLYB_EVAL(z) B00 + z*(B01 + z*B02)

/*  Function for computing the (6, 4) rational Remez approximation for sinh.  */
TMPL_STATIC_INLINE
double tmpl_Double_Sinh_Rat_Remez(double x)
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const double x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const double p = TMPL_POLYA_EVAL(x2);
    const double q = TMPL_POLYB_EVAL(x2);
    const double r = x2 * p / q;

    /*  p/q is the rational minimax approximant for (sinh(x) - x) / x^3.      *
     *  Solving for sinh(x), we get x * (1 + x2*p/q).                         */
    return x * (1.0 + r);
}
/*  End of tmpl_Double_Sinh_Rat_Remez.                                        */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
