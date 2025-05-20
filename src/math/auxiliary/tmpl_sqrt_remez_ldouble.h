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
 *                          tmpl_sqrt_remez_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez minimax polynomial for sqrt(x) on [1, 1 + 1/128].    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Sqrt_Remez                                               *
 *  Purpose:                                                                  *
 *      Computes a Remez polynomial for sqrt(x) on [1, 1 + 1/128].            *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (long double):                                                 *
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
 *                                                                            *
 *      For 64-bit long double we use a degree 2 polynomial, and for all      *
 *      other long double representations we use a degree 3 polynomial.       *
 *  Notes:                                                                    *
 *      1.) The degree 2 polynomial is accurate to about 9 decimals. To       *
 *          achieve double precision we apply Newton's method once.           *
 *      2.) The degree 3 polynomial is accurate to about 11 or 12 decimals.   *
 *          The achieve extended precision, we apply Newton's method once. To *
 *          obtain quadruple or double-double precision, we apply Halley's    *
 *          method once.                                                      *
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
#ifndef TMPL_SQRT_REMEZ_LDOUBLE_H
#define TMPL_SQRT_REMEZ_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (+4.9999952710402341176619144737945297154350813287950E-01L)
#define A02 (-1.2451433174963825931999964469903198888523489420988E-01L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*A02)

#else
/*  Else for 64-bit long double version.                                      */

/******************************************************************************
 *   80-Bit Extended / 128-bit Quadruple / 128-bit Double-Double / Portable   *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (+4.9999999942481026927692750049708879562340746546217E-01L)
#define A02 (-1.2499867190909895062418178436426601160231476013599E-01L)
#define A03 (+6.2045392121239172989223618371410282893180578034924E-02L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*A03))

#endif
/*  End difference between 64-bit long double and higher precisions.          */

/*  Evaluates sqrt(x) for 1 <= x < 1 + 1/128 using a Remez polynomial.        */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Sqrt_Remez(long double x)
{
    /*  The expansion is computed at x = 1. Shift the input.                  */
    const long double xs = x - 1.0L;

    /*  Use Horner's method to evaluate the polynomial.                       */
    return TMPL_POLY_EVAL(xs);
}
/*  End of tmpl_LDouble_Sqrt_Remez.                                           */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
