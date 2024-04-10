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
 *                        tmpl_arctan_maclaurin_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) at single precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arctan_Maclaurin                                           *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) for small values x.          *
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
 *      Use the first 5 terms (0 <= n <= 4) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for small values. For |x| < 0.25 this function is       *
 *      accurate to single precision (10^-8 relative error). The larger       *
 *      the input is, the worse the error. By the alternating series theorem, *
 *      the absolute error is bounded by (1/11)*|x|^11.                       *
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
#ifndef TMPL_ARCTAN_MACLAURIN_FLOAT_H
#define TMPL_ARCTAN_MACLAURIN_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Maclaurin series, 1/(2n+1). The expansion is a
 *  polynomial of degree 9 in terms of x^{2n+1}.                              */
#define A00 (+1.00000000000000000000000000000E+00F)
#define A01 (-3.33333333333333333333333333333E-01F)
#define A02 (+2.00000000000000000000000000000E-01F)
#define A03 (-1.42857142857142857142857142857E-01F)
#define A04 (+1.11111111111111111111111111111E-01F)

/*  This function computes arctan(x) via a MacLaurin series for small |x|.    */
TMPL_STATIC_INLINE
float tmpl_Float_Arctan_Maclaurin(float x)
{
    /*  Declare necessary variables.                                          */
    const float x2 = x*x;

    /*  Use Horner's method to evaluate the polynomial.                       */
    return x*(A00 + x2*(A01 + x2*(A02 + x2*(A03 + x2*A04))));
}
/*  End of tmpl_Float_Arctan_Maclaurin.                                       */

/*  Undefine these in case someone wants to #include this file.               */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
