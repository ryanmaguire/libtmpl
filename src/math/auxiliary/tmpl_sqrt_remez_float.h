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
 *                           tmpl_sqrt_remez_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez minimax polynomial for sqrt(x) on [1, 1 + 1/128].    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Sqrt_Remez                                                 *
 *  Purpose:                                                                  *
 *      Computes a degree 2 Remez polynomial for sqrt(x) on [1, 1 + 1/128].   *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (float):                                                       *
 *          sqrt(x), accurate on [1, 1 + 1/128] to about 8 decimals.          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *      To ensure that sqrt(1) = 1, exact, we use the Remez polynomial for    *
 *      the function:                                                         *
 *                                                                            *
 *                 sqrt(x + 1) - 1                                            *
 *          f(x) = ---------------                                            *
 *                        x                                                   *
 *                                                                            *
 *      We compute this on the interval [0, 1 / 128], meaning sqrt(x) is      *
 *      computed on the interval [1, 1 + 1/128]. Labeling the minimax         *
 *      polynomial P, we compute 1 + (x - 1) * P(x - 1). This ensures that    *
 *      sqrt(1) returns 1, exact, without rounding.                           *
 *  Notes:                                                                    *
 *      For 1 <= x <= 1 + 1/128, this returns sqrt(x) to 8 decimals.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 19, 2025                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SQRT_REMEZ_FLOAT_H
#define TMPL_SQRT_REMEZ_FLOAT_H

/*  TMPL_STATIC_INLINE found here.                                            */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define A01 (+4.9999952710402341176619144737945297154350813287950E-01F)
#define A02 (-1.2451433174963825931999964469903198888523489420988E-01F)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*A02)

/*  Evaluates sqrt(x) for 1 <= x < 1 + 1/128 using a Remez polynomial.        */
TMPL_STATIC_INLINE
float tmpl_Float_Sqrt_Remez(float x)
{
    /*  The expansion is computed at x = 1. Shift the input.                  */
    const float xs = x - 1.0F;

    /*  Use Horner's method to evaluate the polynomial.                       */
    return TMPL_POLY_EVAL(xs);
}
/*  End of tmpl_Float_Sqrt_Remez.                                             */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
