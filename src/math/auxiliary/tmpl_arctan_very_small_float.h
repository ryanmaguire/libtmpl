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
 *                    tmpl_arctan_very_small_float_inline                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) at single precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arctan_Very_Small                                          *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) for very small values x.     *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (float):                                                       *
 *          The Maclaurin series of atan(x).                                  *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                      infty                                                 *
 *                      -----                                                 *
 *                      \         (-1)^n                                      *
 *          atan(x) =   /        -------- * x^{2n+1}                          *
 *                      -----    (2n + 1)                                     *
 *                      n = 0                                                 *
 *                                                                            *
 *      Use the first 4 terms (0 <= n <= 3) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for very small values. For |x| < 1/32 this function is  *
 *      accurate to single precision (10^-8 relative error). The larger       *
 *      the input is, the worse the error. By the alternating series theorem, *
 *      the absolute error is bounded by (1/9)*|x|^9.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 22, 2022                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCTAN_VERY_SMALL_FLOAT_H
#define TMPL_ARCTAN_VERY_SMALL_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the computation of the polynomial approximation. The     *
 *  coefficients for the Taylor series are 1 / (1 + 2n).                      */
#define A0 (+1.00000000000000000000000000000E+00F)
#define A1 (-3.33333333333333333333333333333E-01F)
#define A2 (+2.00000000000000000000000000000E-01F)
#define A3 (-1.42857142857142857142857142857E-01F)

/*  Maclaurin expansion for atan at single precision for small values.        */
TMPL_STATIC_INLINE
float tmpl_Float_Arctan_Very_Small(float x)
{
    /*  The series is in terms of x^{2n+1} = x*{x^2}^{n}. Compute x^2.        */
    const float x2 = x*x;

    /*  Use Horner's method to efficiently evaluate the polynomial.           */
    return x*(A0 + x2*(A1 + x2*(A2 + x2*A3)));
}
/*  End of tmpl_Float_Arctan_Very_Small.                                      */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3

#endif
/*  End of include guard.                                                     */
