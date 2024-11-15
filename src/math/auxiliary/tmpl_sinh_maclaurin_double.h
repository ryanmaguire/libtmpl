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
 *                      tmpl_cosh_maclaurin_double_inline                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of hyperbolic cosine.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cosh_Maclaurin                                            *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of cosh for small values x.             *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cosh_x (double):                                                      *
 *          The Maclaurin series of hyperbolic cosh.                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \          1                                        *
 *          cosh(x)   =   /        ----- * x^{2n}                             *
 *                        -----    (2n)!                                      *
 *                        n = 0                                               *
 *                                                                            *
 *      Use the first 4 terms (0 <= n <= 3) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for values near 0.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 25, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SINH_MACLAURIN_DOUBLE_H
#define TMPL_SINH_MACLAURIN_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (+1.6666666666666666666666666666666666666666666666667E-01)
#define A02 (+8.3333333333333333333333333333333333333333333333333E-03)
#define A03 (+1.9841269841269841269841269841269841269841269841270E-04)
#define A04 (+2.7557319223985890652557319223985890652557319223986E-06)

/*  Maclaurin series of hyperbolic cosine to 3 terms.                         */
TMPL_STATIC_INLINE
double tmpl_Double_Sinh_Maclaurin(double x)
{
    /*  The function is odd and the series is in terms of x^{2n+1}.           */
    const double x2 = x*x;

    /*  Compute the polynomial via Horner's method and return.                */
    return x*(A00 + x2*(A01 + x2*(A02 + x2*(A03 + x2*A04))));
}
/*  End of tmpl_Double_Sinh_Maclaurin.                                        */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
