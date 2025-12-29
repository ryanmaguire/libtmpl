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
 *                        tmpl_arccos_maclaurin_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Maclaurin series for acos(x) at double precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arccos_Maclaurin                                          *
 *  Purpose:                                                                  *
 *      Computes the degree 15 Maclaurin series for acos(x).                  *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (double):                                                      *
 *          The degree 15 Maclaurin series of acos(x).                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *  Notes:                                                                    *
 *      Accurate to double precision for |x| < 0.15. For |x| < 0.5 the        *
 *      approximation is accurate to 7 decimals. The computation is very fast *
 *      and can easily be inlined.                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 13, 2023                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_MACLAURIN_DOUBLE_H
#define TMPL_ARCCOS_MACLAURIN_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Only the odd non-constant terms have non-zero coefficients.               */
#define A00 (1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (1.6666666666666666666666666666666666666666666666667E-01)
#define A02 (7.5000000000000000000000000000000000000000000000000E-02)
#define A03 (4.4642857142857142857142857142857142857142857142857E-02)
#define A04 (3.0381944444444444444444444444444444444444444444444E-02)
#define A05 (2.2372159090909090909090909090909090909090909090909E-02)
#define A06 (1.7352764423076923076923076923076923076923076923077E-02)
#define A07 (1.3964843750000000000000000000000000000000000000000E-02)

/*  The constant Pi / 2.                                                      */
extern const double tmpl_double_pi_by_two;

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*(A05 + z*(A06 + z*A07))))))

/*  Computes the degree 15 Maclaurin polynomial for acos(x).                  */
TMPL_STATIC_INLINE
double tmpl_Double_Arccos_Maclaurin(double x)
{
    /*  The non-constant terms are odd, powers are x^{2n+1}.                  */
    const double x2 = x*x;

    /*  Compute the Maclaurin series of asin(x) / x.                          */
    const double poly = TMPL_POLY_EVAL(x2);

    /*  acos(x) = pi/2 - asin(x). Compute using this.                         */
    return tmpl_double_pi_by_two - x*poly;
}
/*  End of tmpl_Double_Arccos_Maclaurin.                                      */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
