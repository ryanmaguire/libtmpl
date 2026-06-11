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
 *                        tmpl_arccos_maclaurin_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Maclaurin series for acos(x) at single precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arccos_Maclaurin                                           *
 *  Purpose:                                                                  *
 *      Computes the degree 9 Maclaurin series for acos(x).                   *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (float):                                                       *
 *          The degree 9 Maclaurin series of acos(x).                         *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *  Notes:                                                                    *
 *      Accurate to single precision for |x| < 0.35. For |x| < 0.5 the        *
 *      approximation is accurate to 5 decimals. The computation is very fast *
 *      and can easily be inlined.                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 13, 2023                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_MACLAURIN_FLOAT_H
#define TMPL_ARCCOS_MACLAURIN_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  The constant Pi / 2.                                                      */
extern const float tmpl_float_pi_by_two;

/*  Only the odd non-constant terms have non-zero coefficients.               */
#define A00 (1.0000000000000000000000000000000000000000000000000E+00F)
#define A01 (1.6666666666666666666666666666666666666666666666667E-01F)
#define A02 (7.5000000000000000000000000000000000000000000000000E-02F)
#define A03 (4.4642857142857142857142857142857142857142857142857E-02F)
#define A04 (3.0381944444444444444444444444444444444444444444444E-02F)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z * (A01 + z * (A02 + z * (A03 + z * A04)))

/*  Computes the degree 9 Maclaurin polynomial for acos(x).                   */
TMPL_CONST_FUNC
TMPL_STATIC_INLINE
float tmpl_Float_Arccos_Maclaurin(const float x)
TMPL_UNSEQUENCED
{
    /*  The non-constant terms are odd, powers are x^{2n+1}.                  */
    const float x2 = x * x;

    /*  Compute the Maclaurin series of asin(x) / x.                          */
    const float poly = TMPL_POLY_EVAL(x2);

    /*  acos(x) = pi/2 - asin(x). Compute using this.                         */
    return tmpl_float_pi_by_two - x * poly;
}
/*  End of tmpl_Float_Arccos_Maclaurin.                                       */

/*  Undefine everything to avoid collisions with other macros.                */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
