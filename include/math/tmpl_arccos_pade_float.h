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
 *                           tmpl_arccos_pade_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (4, 4) Pade approximant of acos(x) at single precision.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arccos_Pade                                                *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of order (4, 4) for arccos.             *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (float):                                                       *
 *          The Pade approximation of acos(x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *          acos(x)+x-pi/2   a0 + a1*x^2 + a2*x^4                             *
 *          -------------- = --------------------                             *
 *               x^3          1 + b1*x^2 + a2*x^4                             *
 *  Notes:                                                                    *
 *      Accurate to single precision for |x| < 0.5. For |x| < 0.9 the peak    *
 *      error is bounded by 10^-3. Not accurate for |x| near 1.               *
 *                                                                            *
 *      It is a lot faster (~3-4x) to call this function than the main        *
 *      arccos routine. If you don't need perfect accuracy, and if |x| is not *
 *      near 1, you may benefit from using this.                              *
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
 *  2023/05/14: Ryan Maguire                                                  *
 *      Changed so that this computes an actual Pade approximant. It was a    *
 *      Remez rational minimax approximation before, improperly labelled.     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_PADE_FLOAT_H
#define TMPL_ARCCOS_PADE_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P0 (+1.6666666666666666666666666666666666666666666666667E-01F)
#define P1 (-1.1262038994597134132017852948085506225041108762039E-01F)
#define P2 (+4.3770531076732627120224019448825650376037972937198E-03F)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q0 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define Q1 (-1.1257223396758280479210711768851303735024665257223E+00F)
#define Q2 (+2.6498022864301934069375929841046120115887557748023E-01F)

/*  Function for computing the (4, 4) Pade approximant of acos(x).            */
TMPL_INLINE_DECL
float tmpl_Float_Arccos_Pade(float x)
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const float x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const float p = P0 + x2*(P1 + x2*P2);
    const float q = Q0 + x2*(Q1 + x2*Q2);
    const float r = x2*p/q;

    /*  p/q is the Pade approximant for (acos(x) - pi/2 + x) / x^3.           */
    return tmpl_Pi_By_Two_F - (x + x*r);
}
/*  End of tmpl_Float_Arccos_Pade.                                            */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P2
#undef P1
#undef P0
#undef Q2
#undef Q1
#undef Q0

#endif
/*  End of include guard.                                                     */
