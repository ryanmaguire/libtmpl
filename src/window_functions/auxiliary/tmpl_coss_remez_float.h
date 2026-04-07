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
 *                           tmpl_coss_remez_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the squared cosine window for small x.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Coss_Remez                                                 *
 *  Purpose:                                                                  *
 *      Computes the squared cosine window using a Remez polynomial for very  *
 *      small arguments.                                                      *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      coss_x (float):                                                       *
 *          The squared cosine window of x.                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the degree 4 Remez polynomial for the function f *
 *      given by:                                                             *
 *                                                                            *
 *                 Coss(x) - 1                                                *
 *          f(x) = -----------                                                *
 *                      2                                                     *
 *                     x                                                      *
 *                                                                            *
 *      where Coss is the squared cosine window, have been pre-computed on    *
 *      the interval [-1/32, 1/32]. Since this function is even, only 3 of    *
 *      the terms in this polynomial are non-zero. We compute this polynomial *
 *      using Horner's method and then return the expression 1 + x^2 P(x),    *
 *      where P is the Remez polynomial for f.                                *
 *  Notes:                                                                    *
 *      1.) Accurate to single precision for |x| < 0.03125.                   *
 *                                                                            *
 *      2.) This function assumes a normalized window of width 1 is being     *
 *          used on the interval [-1/2, 1/2].                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 7, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COSS_REMEZ_FLOAT_H
#define TMPL_COSS_REMEZ_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (-9.8696044002134344726685756881956195639429304563243E+00F)
#define A01 (+3.2469680863994339243308753985312496416908920770531E+01F)
#define A02 (-4.2684306942006719234244723006281095883952442171987E+01F)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z * (A01 + z * A02)

/*  Computes the squared cosine window using a Remez polynomial.              */
TMPL_STATIC_INLINE
float tmpl_Float_Coss_Remez(const float x)
{
    /*  The coss function is even, the polynomial is in terms of x^2.         */
    const float x2 = x * x;

    /*  Evaluate the polynomial using Horner's method.                        */
    const float poly = TMPL_POLY_EVAL(x2);

    /*  The polynomial is for (Coss(x) - 1) / x^2. Compute Coss from this.    */
    return 1.0F + x2 * poly;
}
/*  End of tmpl_Float_Coss_Remez.                                             */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
