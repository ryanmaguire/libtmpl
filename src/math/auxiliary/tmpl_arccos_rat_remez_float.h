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
 *                        tmpl_arccos_rat_remez_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (4, 2) rational minimax approximation of acos(x)         *
 *      centered about the origin at single precision.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arccos_Rat_Remez                                           *
 *  Purpose:                                                                  *
 *      Computes the degree (4, 2) minimax approximation for arccos.          *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (float):                                                       *
 *          The minimax approximation of acos(x).                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The function f(x) = (acos(x) + x - pi/2) / x^3 is even. Pre-compute   *
 *      the coefficients for the rational minimax function R(x) of degree     *
 *      (4, 2) for f(x). The odd terms have zero coefficients. We may thus    *
 *      compute the minimax approximation via:                                *
 *                                                                            *
 *                                   a0 + a2 x^2 + a4 x^4                     *
 *          acos(x) = pi/2 - x + x^3 --------------------                     *
 *                                        b0 + b2 x^2                         *
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
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_pade_float.c to just include this file.  *
 *  2023/05/13: Ryan Maguire                                                  *
 *      Corrected name and comments. This was previously called a "Pade"      *
 *      approximant, but it is not. The coefficients for the Pade approximant *
 *      and the rational minimax function are slightly different.             *
 *  2024/10/29: Ryan Maguire                                                  *
 *      Updating coefficients. These are now the exact output of the python   *
 *      script found in libtmpl_data. Attempting to create reproducible       *
 *      results in doing this.                                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_RAT_REMEZ_FLOAT_H
#define TMPL_ARCCOS_RAT_REMEZ_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.6666657332654782511630744878585859634321997276656E-01F)
#define A01 (-4.2035660448040502977938914900697450640872894337286E-02F)
#define A02 (-8.2125492968317658201629446415138054874693066700587E-03F)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (-7.0227698493007347430817019567204548858969498944150E-01F)

/*  The constant Pi / 2.                                                      */
#define TMPL_PI_BY_TWO (+1.5707963267948966192313216916397514420985846996F)

/*  Function for computing the (4, 2) minimax approximation of acos(x).       */
TMPL_STATIC_INLINE
float tmpl_Float_Arccos_Rat_Remez(float x)
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const float x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const float p = A00 + x2*(A01 + x2*A02);
    const float q = B00 + x2*B01;
    const float r = x2*p/q;

    /*  p/q is the rational minimax approximant for (acos(x) - pi/2 + x)/x^3. *
     *  Solving for acos(x), we get pi/2 - (x + x*x2*p/q).                    */
    return TMPL_PI_BY_TWO - (x + x*r);
}
/*  End of tmpl_Float_Arccos_Rat_Remez.                                       */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
