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
 *                    tmpl_sinpi_maclaurin_double_inline                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of sin(pi x) at double precision.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_SinPi_Maclaurin                                           *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of sin(pi x) for small values x.        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sin_pix (double):                                                     *
 *          The Maclaurin series of sin(pi x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \        (-1)^n pi^{2n+1}                           *
 *          sin(pi x) =   /        ---------------- * x^{2n+1}                *
 *                        -----         (2n+1)!                               *
 *                        n = 0                                               *
 *                                                                            *
 *      Use the first 4 terms (0 <= n <= 3) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for values near 0.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 24, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SINPI_MACLAURIN_DOUBLE_H
#define TMPL_SINPI_MACLAURIN_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Maclaurin series at double precision.                */
#define A00 (+3.1415926535897932384626433832795028841972E+00)
#define A01 (-5.1677127800499700292460525111835658670375E+00)
#define A02 (+2.5501640398773454438561775836952967206692E+00)
#define A03 (-5.9926452932079207688773938354604004601536E-01)

/*  Helper macro for evaluating the polynomial via Horner's method.           */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*A03))

/*  Maclaurin series for sin(pi x), double precision, to 4 terms.             */
TMPL_STATIC_INLINE
double tmpl_Double_SinPi_Maclaurin(double x)
{
    /*  sin(pi x) is odd, the polynomial is in terms of x^{2n+1}.             */
    const double x2 = x * x;
    const double poly = TMPL_POLY_EVAL(x2);
    return x * poly;
}
/*  End of tmpl_Double_SinPi_Maclaurin.                                       */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
