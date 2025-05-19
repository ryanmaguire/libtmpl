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
 *                           tmpl_cbrt_remez_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Remez minimax polynomial for cbrt(x) about x = 1.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cbrt_Remez                                                *
 *  Purpose:                                                                  *
 *      Computes the Remez minimax polynomial of degree 2 for cbrt(x) on the  *
 *      interval 1 <= x <= 1 + 1/128.                                         *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cbrt_x (double):                                                      *
 *          The evaluation of the Remez minimax polynomial for cbrt(x).       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *  Notes:                                                                    *
 *      Only accurate for values near 1. Peak relative error on the interval  *
 *      [1, 1 + 1/28] is 10^-9. Much less than double precision, but double   *
 *      precision is attained in the cbrt function by using Newton's method   *
 *      after calling this routine.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 8, 2023                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CBRT_REMEZ_DOUBLE_H
#define TMPL_CBRT_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Remez minimax polynomial at x = 1.                   */
#define A00 (+1.00000000090941443242060478073980568322005875164904015776472E+00)
#define A01 (+3.33331233712890189943879124271000459100797541938160614930922E-01)
#define A02 (-1.10392493085468935087723379189564640328689673130626030290442E-01)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*A02)

/*  Function for computing the Remez polynomial of cbrt on [1, 1 + 1/128].    */
TMPL_STATIC_INLINE
double tmpl_Double_Cbrt_Remez(double x)
{
    /*  The series is computed at x = 1. Shift the input.                     */
    const double xs = x - 1.0;

    /*  Use Horner's method to evaluate the polynomial.                       */
    return TMPL_POLY_EVAL(xs);
}
/*  End of tmpl_Double_Cbrt_Remez.                                            */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
