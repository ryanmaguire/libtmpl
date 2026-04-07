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
 *                         tmpl_coss_rat_remez_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the squared cosine window for small x.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Coss_Rat_Remez                                            *
 *  Purpose:                                                                  *
 *      Computes the squared cosine window using a rational Remez             *
 *      approximation for small arguments.                                    *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      coss_x (double):                                                      *
 *          The squared cosine of x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the (8, 8) rational Remez approximation for the  *
 *      squared cosine window have been pre-computed on the interval          *
 *      [-1/4, 1/4]. Since the window is an even function, half of the        *
 *      coefficients are zero, meaning we only have 5 non-zero terms in the   *
 *      numerator and 5 non-zero terms in the denominator. The approximation  *
 *      is performed using Horner's method for the numerator and denominator, *
 *      and then returning the ratio.                                         *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for |x| < 0.25.                      *
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
 *  Date:       February 18, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COSS_RAT_REMEZ_DOUBLE_H
#define TMPL_COSS_RAT_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.9999999999999999814294167983477388606818921917447E-01)
#define A01 (-8.9909753678859383203473172175891602746773609095774E+00)
#define A02 (+2.4184740936822766200042961247244511937750797180333E+01)
#define A03 (-1.7911116274298446927652579161391059800213681918521E+01)
#define A04 (+4.1110377986602408304634553634346278069211474884566E+00)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (+8.7862903320341543362110676916516883420189191660289E-01)
#define A02 (+3.8676489852003343630654296694332946146724035323969E-01)
#define A03 (+1.0569037984474647161225234531782473681512124350968E-01)
#define A04 (+1.6120651585134203120937922938676077964136587073203E-02)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  Computes the squared cosine window via a rational Remez expansion.        */
TMPL_STATIC_INLINE
double tmpl_Double_Coss_Rat_Remez(const double x)
{
    /*  The polynomials are in terms of x^2. Compute.                         */
    const double x2 = x * x;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const double numer = TMPL_NUM_EVAL(x2);
    const double denom = TMPL_DEN_EVAL(x2);

    /*  The squared cosine window is the ratio.                               */
    return numer / denom;
}
/*  End of tmpl_Double_Coss_Rat_Remez.                                        */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
