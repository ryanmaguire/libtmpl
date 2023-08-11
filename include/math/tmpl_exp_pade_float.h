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
 *                            tmpl_exp_pade_float                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (4, 4) Pade approximant of exp(x) at single precision.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Exp_Pade                                                   *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of order (4, 4) for exp.                *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      exp_x (float):                                                        *
 *          The Pade approximation of exp(x).                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *                     a0 + a1*x^1 + a2*x^2 + a3*x^3 + a4*x^4                 *
 *          exp(x) ~= ---------------------------------------                 *
 *                     b0 + b1*x^1 + b2*x^2 + b3*x^3 + b4*x^4                 *
 *                                                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 9, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EXP_PADE_FLOAT_H
#define TMPL_EXP_PADE_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P0 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define P1 (+5.0000000000000000000000000000000000000000000000000E-01F)
#define P2 (+1.0714285714285714285714285714285714285714285714286E-01F)
#define P3 (+1.1904761904761904761904761904761904761904761904762E-02F)
#define P4 (+5.9523809523809523809523809523809523809523809523810E-04F)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q0 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define Q1 (-5.0000000000000000000000000000000000000000000000000E-01F)
#define Q2 (+1.0714285714285714285714285714285714285714285714286E-01F)
#define Q3 (-1.1904761904761904761904761904761904761904761904762E-02F)
#define Q4 (+5.9523809523809523809523809523809523809523809523810E-04F)

/*  Function for computing the (4, 4) Pade approximant of Exp.                */
TMPL_INLINE_DECL
float tmpl_Float_Exp_Pade(float x)
{
    /*  Compute the numerator (p) and the denominator (q).                    */
    const float p = P0 + x*(P1 + x*(P2 + x*(P3 + x*P4)));
    const float q = Q0 + x*(Q1 + x*(Q2 + x*(Q3 + x*Q4)));

    /*  Return the quotient.                                                  */
    return p / q;
}
/*  End of tmpl_Float_Exp_Pade.                                               */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P0
#undef P1
#undef P2
#undef P3
#undef P4
#undef Q0
#undef Q1
#undef Q2
#undef Q3
#undef Q4

#endif
/*  End of include guard.                                                     */
