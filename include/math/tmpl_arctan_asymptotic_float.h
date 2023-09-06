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
 *                        tmpl_arctan_asymptotic_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of atan(x) at single precision.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arctan_Asymptotic                                          *
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of atan(x) for large positive x.    *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (float):                                                       *
 *          The asymptotic expansion of x.                                    *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the reciprocal of x, and the square of this, and use Horner's *
 *      method to efficiently evaluate the polynomial.                        *
 *                                                                            *
 *                             infty                                          *
 *                             -----                                          *
 *                    pi       \         (-1)^n        1                      *
 *          atan(x) ~ ---  -   /       --------- * ---------     x --> infty  *
 *                     2       -----    (2n + 1)    x^{2n+1}                  *
 *                             n = 0                                          *
 *                                                                            *
 *      Use the first 4 terms (0 <= n <= 3) of this expansion to compute.     *
 *  Notes:                                                                    *
 *      Only accurate for large POSITIVE values. For x > 16, this function    *
 *      is accurate to single precision (10^-8 relative error). The closer    *
 *      the input is to 0, the worse the error.                               *
 *                                                                            *
 *      This function can be used for large negative values via:              *
 *          atan(x) ~= -tmpl_Float_Arctan_Asymptotic(-x).                     *
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
#ifndef TMPL_ARCTAN_ASYMPTOTIC_FLOAT_H
#define TMPL_ARCTAN_ASYMPTOTIC_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the asymptotic expansion. The expansion is a polynomial  *
 *  of degree 3 in terms of 1/x^{2n+1}. The coefficients are (-1)^n / (2n+1). */
#define A0 (+1.00000000000000000000000000000E+00F)
#define A1 (-3.33333333333333333333333333333E-01F)
#define A2 (+2.00000000000000000000000000000E-01F)
#define A3 (-1.42857142857142857142857142857E-01F)

/*  The constant Pi / 2.                                                      */
#define TMPL_PI_BY_TWO (+1.5707963267948966192313216916397514420985846996F)

/*  This function computes arctan(x) via the asymptotic expansion.            */
TMPL_STATIC_INLINE
float tmpl_Float_Arctan_Asymptotic(float x)
{
    /*  Declare necessary variables.                                          */
    const float z = 1.0F / x;
    const float z2 = z*z;

    /*  Use Horner's method to compute the polynomial.                        */
    return TMPL_PI_BY_TWO - z*(A0 + z2*(A1 + z2*(A2 + z2*A3)));
}
/*  End of tmpl_Float_Arctan_Asymptotic.                                      */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3
#undef TMPL_PI_BY_TWO

#endif
/*  End of include guard.                                                     */
