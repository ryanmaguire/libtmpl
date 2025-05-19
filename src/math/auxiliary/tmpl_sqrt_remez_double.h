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
 *                           tmpl_sqrt_remez_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez minimax polynomial for sqrt(x) on [1, 1 + 1/128].    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sqrt_Remez                                                *
 *  Purpose:                                                                  *
 *      Computes a degree 2 Remez polynomial for sqrt(x) on [1, 1 + 1/128].   *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (double):                                                      *
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
 *      For 1 <= x <= 1 + 1/128 this returns sqrt(x) to 8 decimals. To obtain *
 *      double precision we apply Newton's method after the Remez polynomial. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 27, 2024                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/05/19: Ryan Maguire                                                  *
 *      Changed coefficients so that sqrt(1) = 1, exact. The Remez polynomial *
 *      is now computed for (sqrt(x + 1) - 1) / x on the interval [0, 1/128]. *
 *      Labeling this P(x), the output is 1 + (x - 1) * P(x - 1), and hence   *
 *      sqrt(1) = 1, exact. Previously the Remez polynomial was computed for  *
 *      sqrt(x + 1), the constant term being 1.00000000092137931324220803332, *
 *      about 10^-10 off from 1. The resulting polynomial, combined with      *
 *      Newton's method in the main sqrt routine, produced a value that did   *
 *      indeed round to 1 (meaning tmpl_Double_Sqrt(1.0) = 1.0 previously),   *
 *      but by modifying the coefficients slightly we can very easily verify  *
 *      that sqrt(1.0) = 1.0 will occur without relying on the rouding mode,  *
 *      and no penalty to the accuracy or performance of the function occurs. *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SQRT_REMEZ_DOUBLE_H
#define TMPL_SQRT_REMEZ_DOUBLE_H

/*  TMPL_STATIC_INLINE found here.                                            */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (+4.9999952710402341176619144737945297154350813287950E-01)
#define A02 (-1.2451433174963825931999964469903198888523489420988E-01)

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
