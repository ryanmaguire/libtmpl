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
 *                 tmpl_normalized_fresnel_sin_maclaurin_float                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine for small values.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Normalized_Fresnel_Sin_Maclaurin                           *
 *  Purpose:                                                                  *
 *      Computes C(x) for |x| < 1/4.                                          *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      S_x (float):                                                          *
 *          The normalized Fresnel sine of x.                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the Maclaurin series for |x| < 1 / 4 using the first 3 terms  *
 *      (0 <= n <= 2). The series is defined by:                              *
 *                                                                            *
 *                 infty                                                      *
 *                 -----       n  4n+1  -   -  2n                             *
 *                 \       (-1)  x     | pi  |                                *
 *          C(x) = /       ----------- | --- |                                *
 *                 -----   (4n+1)(2n)!  - 2 -                                 *
 *                 n = 0                                                      *
 *                                                                            *
 *      The sum is performed using Horner's method.                           *
 *  Notes:                                                                    *
 *      This function assumes the input is bounded by 1/4.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 24, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_SIN_MACLAURIN_FLOAT_H
#define TMPL_NORMALIZED_FRESNEL_SIN_MACLAURIN_FLOAT_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define A01 (-2.4674011002723396547086227499690377838284248518102E-01F)
#define A02 (+2.8185500877894223737395929597426247468092472706217E-02F)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*A02)

/*  Computes the normalized Fresnel sine for |x| < 1/4.                       */
TMPL_STATIC_INLINE
float tmpl_Float_Normalized_Fresnel_Sin_Maclaurin(float x)
{
    /*  The series is in terms of x^4. Compute this.                          */
    const float xsq = x*x;
    const float xqt = xsq*xsq;

    /*  Evaluate using Horner's method and return.                            */
    const float poly = TMPL_POLY_EVAL(xqt);
    return x*poly;
}
/*  End of tmpl_Float_Normalized_Fresnel_Sin_Maclaurin.                       */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
