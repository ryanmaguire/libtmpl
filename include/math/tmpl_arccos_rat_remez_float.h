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
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_RAT_REMEZ_FLOAT_H
#define TMPL_ARCCOS_RAT_REMEZ_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator.                                           */
#define P0 (+1.6666586697E-01F)
#define P1 (-4.2743422091E-02F)
#define P2 (-8.6563630030E-03F)

/*  Coefficients for the denominator.                                         */
#define Q0 (+1.0000000000E+00F)
#define Q1 (-7.0662963390E-01F)

/*  Function for computing the (4, 2) minimax approximation of acos(x).       */
TMPL_INLINE_DECL
float tmpl_Float_Arccos_Rat_Remez(float x)
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const float x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const float p = P0 + x2*(P1 + x2*P2);
    const float q = Q0 + x2*Q1;
    const float r = x2*p/q;

    /*  p/q is the minimax approximation for (acos(x) - pi/2 + x) / x^3.      */
    return tmpl_Pi_By_Two_F - (x + x*r);
}
/*  End of tmpl_Float_Arccos_Rat_Remez.                                       */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P2
#undef P1
#undef P0
#undef Q1
#undef Q0

#endif
/*  End of include guard.                                                     */
