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
 *                       tmpl_arctan_asymptotic_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of atan(x) at double precision.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arctan_Asymptotic                                         *
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of atan(x) for large positive x.    *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (double):                                                      *
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
 *      Use the first 6 terms (0 <= n <= 5) of this expansion to compute.     *
 *  Notes:                                                                    *
 *      Only accurate for large POSITIVE values. For x > 16, this function    *
 *      is accurate to double precision (10^-16 relative error). The closer   *
 *      the input is to 0, the worse the error.                               *
 *                                                                            *
 *      This function can be used for large negative values via:              *
 *          atan(x) ~= -tmpl_Double_Arctan_Asymptotic(-x).                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 20, 2022                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/09/22: Ryan Maguire                                                  *
 *      Added license.                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCTAN_ASYMPTOTIC_DOUBLE_H
#define TMPL_ARCTAN_ASYMPTOTIC_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the asymptotic expansion. The expansion is a polynomial  *
 *  of degree 5 in terms of 1/x^{2n+1}. The coefficients are (-1)^n / (2n+1). */
#define A00 (+1.00000000000000000000000000000E+00)
#define A01 (-3.33333333333333333333333333333E-01)
#define A02 (+2.00000000000000000000000000000E-01)
#define A03 (-1.42857142857142857142857142857E-01)
#define A04 (+1.11111111111111111111111111111E-01)
#define A05 (-9.09090909090909090909090909090E-02)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

/*  The constant Pi / 2.                                                      */
#define TMPL_PI_BY_TWO (+1.5707963267948966192313216916397514420985846996)

/*  Asymptotic expansion for the inverse tangent function.                    */
TMPL_STATIC_INLINE
double tmpl_Double_Arctan_Asymptotic(double x)
{
    /*  Declare necessary variables.                                          */
    const double z = 1.0 / x;
    const double z2 = z*z;

    /*  Use Horner's method to compute the polynomial.                        */
    const double poly = TMPL_POLY_EVAL(z2);
    return TMPL_PI_BY_TWO - z*poly;
}
/*  End of tmpl_Double_Arctan_Asymptotic.                                     */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
