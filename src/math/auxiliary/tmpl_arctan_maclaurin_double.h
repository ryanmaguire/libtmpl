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
 *                        tmpl_arctan_maclaurin_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) at double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arctan_Maclaurin                                          *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) for small values x.          *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (double):                                                      *
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
 *      Use the first 9 terms (0 <= n <= 8) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for small values. For |x| < 0.15 this function is       *
 *      accurate to double precision (10^-16 relative error). The larger      *
 *      the input is, the worse the error. By the alternating series theorem, *
 *      the absolute error is bounded by (1/19)*|x|^19.                       *
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
#ifndef TMPL_ARCTAN_MACLAURIN_DOUBLE_H
#define TMPL_ARCTAN_MACLAURIN_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Maclaurin series at double precision.                */
#define A00 (+1.00000000000000000000000000000E+00)
#define A01 (-3.33333333333333333333333333333E-01)
#define A02 (+2.00000000000000000000000000000E-01)
#define A03 (-1.42857142857142857142857142857E-01)
#define A04 (+1.11111111111111111111111111111E-01)
#define A05 (-9.09090909090909090909090909090E-02)
#define A06 (+7.69230769230769230769230769231E-02)
#define A07 (-6.66666666666666666666666666667E-02)
#define A08 (+5.88235294117647058823529411765E-02)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Maclaurin series for arctan, double precision, to 9 terms.                */
TMPL_STATIC_INLINE
double tmpl_Double_Arctan_Maclaurin(double x)
{
    /*  Declare necessary variables.                                          */
    const double x2 = x*x;

    /*  Use Horner's method to evaluate the polynomial.                       */
    const double poly = TMPL_POLY_EVAL(x2);
    return x*poly;
}
/*  End of tmpl_Double_Arctan_Maclaurin.                                      */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
