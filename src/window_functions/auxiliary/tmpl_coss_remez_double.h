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
 *                           tmpl_coss_remez_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the squared cosine window for small x.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Coss_Remez                                                *
 *  Purpose:                                                                  *
 *      Computes the squared cosine window using a Remez polynomial for very  *
 *      small arguments.                                                      *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      coss_x (double):                                                      *
 *          The squared cosine window of x.                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the degree 8 Remez polynomial for the function f *
 *      given by:                                                             *
 *                                                                            *
 *                 Coss(x) - 1                                                *
 *          f(x) = -----------                                                *
 *                      2                                                     *
 *                     x                                                      *
 *                                                                            *
 *      where Coss is the squared cosine window, have been pre-computed on    *
 *      the interval [-1/32, 1/32]. Since this function is even, only 5 of    *
 *      the terms in this polynomial are non-zero. We compute this polynomial *
 *      using Horner's method and then return the expression 1 + x^2 P(x),    *
 *      where P is the Remez polynomial for f.                                *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for |x| < 0.03125.                   *
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
#ifndef TMPL_COSS_REMEZ_DOUBLE_H
#define TMPL_COSS_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (-9.8696044010893586119836260840774741547271037159709E+00)
#define A01 (+3.2469697011333794966195903621248838725905850741607E+01)
#define A02 (-4.2728408600473142670686338279929914223019474160613E+01)
#define A03 (+3.0122312445849250846578813021034951028609016100578E+01)
#define A04 (-1.3203483943106073019872003713083216380928644648296E+01)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z * (A01 + z * (A02 + z * (A03 + z * A04)))

/*  Computes the squared cosine window using a Remez polynomial.              */
TMPL_STATIC_INLINE
double tmpl_Double_Coss_Remez(const double x)
{
    /*  The coss function is even, the polynomial is in terms of x^2.         */
    const double x2 = x * x;

    /*  Evaluate the polynomial using Horner's method.                        */
    const double poly = TMPL_POLY_EVAL(x2);

    /*  The polynomial is for (Coss(x) - 1) / x^2. Compute Coss from this.    */
    return 1.0 + x2 * poly;
}
/*  End of tmpl_Double_Coss_Remez.                                            */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
