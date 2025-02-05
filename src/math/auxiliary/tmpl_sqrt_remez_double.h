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
 *                        tmpl_arccos_maclaurin_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Maclaurin series for acos(x) at double precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sqrt_Remez                                                *
 *  Purpose:                                                                  *
 *      Computes the degree 2 Remez polynomial for sqrt(x) on [1, 1 + 1/128]. *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (double):                                                      *
 *          The degree 2 Remez polynomial for sqrt(x).                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *  Notes:                                                                    *
 *      For 1 <= x <= 1 + 1/128, this return sqrt(x) to 9 decimals. To obtain *
 *      double precision, we apply Newton's method after the Remez polynomial.*
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 27, 2024                                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SQRT_REMEZ_DOUBLE_H
#define TMPL_SQRT_REMEZ_DOUBLE_H

/*  TMPL_STATIC_INLINE found here.                                            */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.0000000009213793132422080333230191911611046603122E+00)
#define A01 (+4.9999787298570402278901738280028337776415357546897E-01)
#define A02 (-1.2427211443985097757833168706757977964507907886005E-01)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*A02)

/*  Evaluates sqrt(x) for 1 <= x < 1 + 1/128 using a Remez polynomial.        */
TMPL_STATIC_INLINE
double tmpl_Double_Sqrt_Remez(double x)
{
    /*  The expansion is computed at x = 1. Shift the input.                  */
    const double xs = x - 1.0;

    /*  Use Horner's method to evaluate the polynomial.                       */
    return TMPL_POLY_EVAL(xs);
}
/*  End of tmpl_Double_Sqrt_Remez.                                            */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
