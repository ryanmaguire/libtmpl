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
 *                          tmpl_cbrt_remez_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Remez polynomial of cbrt(x) at long double precision.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Cbrt_Remez                                               *
 *  Purpose:                                                                  *
 *      Computes the Remez minimax polynomial of degree 2 for cbrt(x) on the  *
 *      interval 1 <= x <= 1 + 1/128.                                         *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cbrt_x (long double):                                                 *
 *          The evaluation of the Remez minimax polynomial for cbrt(x).       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *  Notes:                                                                    *
 *      Only accurate for values near 1. Peak relative error on the interval  *
 *      [1, 1 + 1/28] is 10^-9 for 64-bit and 10^-12 for all others. Much     *
 *      less than the respective precisions, but long double precision is     *
 *      attained in the cbrt function by calling this routine and then        *
 *      applying one iteration of either Newton's method or Halley's method.  *
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
#ifndef TMPL_CBRT_REMEZ_LDOUBLE_H
#define TMPL_CBRT_REMEZ_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A0 (+1.00000000090941443242060478073980568322005875164904015776471E+00L)
#define A1 (+3.33331233712890189943879124271000459100797541938160614930922E-01L)
#define A2 (-1.10392493085468935087723379189564640328689673130626030290441E-01L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A0 + z*(A1 + z*A2)

#else
/*  Else for 64-bit long double version.                                      */

/******************************************************************************
 *   80-Bit Extended / 128-bit Quadruple / 128-bit Double-Double / Portable   *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A0 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A1 (+3.3333333272768627036888324386090748485988668539868E-01L)
#define A2 (-1.1110971257432758665370444206545152220252533224039E-01L)
#define A3 (+6.1249616452718722146312202258519141199160261252326E-02L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A0 + z*(A1 + z*(A2 + z*A3))

#endif
/*  End difference between 64-bit long double and higher precisions.          */

/*  Function for computing the Remez polynomial of cbrt on [1, 1 + 1/128].    */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Cbrt_Remez(long double x)
{
    /*  The series is computed at x = 1. Shift the input.                     */
    const long double xs = x - 1.0L;

    /*  Use Horner's method to evaluate the polynomial.                       */
    return TMPL_POLY_EVAL(xs);
}
/*  End of tmpl_LDouble_Cbrt_Remez.                                           */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
