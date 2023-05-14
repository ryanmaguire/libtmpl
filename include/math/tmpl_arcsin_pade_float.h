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
 *                           tmpl_arcsin_pade_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (4, 2) Pade approximant of asin(x) at single precision.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arcsin_Pade                                                *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of order (4, 2) for arcsin.             *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      asin_x (float):                                                       *
 *          The Pade approximation of asin(x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *          asin(x) - x   a0 + a1*x^2 + a2*x^4                                *
 *          ----------- = --------------------                                *
 *              x^3            1 + b1*x^2                                     *
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
 *  Date:       May 9, 2023                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCSIN_PADE_FLOAT_H
#define TMPL_ARCSIN_PADE_FLOAT_H

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

/*  Function for computing the (4, 2) Pade approximant of asin(x).            */
TMPL_INLINE_DECL
float tmpl_Float_Arcsin_Pade(float x)
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const float x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const float p = P0 + x2*(P1 + x2*P2);
    const float q = Q0 + x2*Q1;
    const float r = x2*p/q;

    /*  p/q is the Pade approximant for (asin(x) - x) / x^3.                  */
    return x + x*r;
}
/*  End of tmpl_Float_Arcsin_Pade.                                            */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P2
#undef P1
#undef P0
#undef Q1
#undef Q0

#endif
/*  End of include guard.                                                     */
