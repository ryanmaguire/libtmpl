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
 *                          tmpl_coss_tail_end_float                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the squared cosine window for x near 1 / 2.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Coss_Tail_End                                              *
 *  Purpose:                                                                  *
 *      Computes the squared cosine window using a rational Remez             *
 *      approximation for 1 / 4 <= x <= 1 / 2.                                *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      coss_x (float):                                                       *
 *          The squared cosine of x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The squared cosine window can be expanded about x = 1 / 2 in terms    *
 *      of x - 1 / 2. The coefficients for the (4, 3) rational Remez          *
 *      approximation for the function:                                       *
 *                                                                            *
 *                 Coss(x + 1 / 2)                                            *
 *          f(x) = ---------------                                            *
 *                        2                                                   *
 *                       x                                                    *
 *                                                                            *
 *      on the interval [-1/4, 0] (the limit of f at zero is used to avoid a  *
 *      division-by-zero), where Coss represents the squared cosine window,   *
 *      have been pre-computed below. Given x with 1 / 4 <= x <= 1 / 2, we    *
 *      translate x into this interval using:                                 *
 *                                                                            *
 *                     1                                                      *
 *          t(x) = x - -                                                      *
 *                     2                                                      *
 *                                                                            *
 *      and then return t(x)^2 * P(t(x)) / Q(t(x)), where P and Q are the     *
 *      numerator and denominator, respectively, for the degree (4, 3)        *
 *      rational minimax approximation for f.                                 *
 *                                                                            *
 *      Note that since we scale the result by t(x)^2, the approximation is   *
 *      zero, exact, when x = 1 / 2. That is, the window goes to zero at the  *
 *      right endpoint in the window.                                         *
 *  Notes:                                                                    *
 *      1.) Accurate to single precision for 0.25 <= x <= 0.5.                *
 *                                                                            *
 *      2.) This function assumes a normalized window of width 1 is being     *
 *          used on the interval [-1/2, 1/2].                                 *
 *                                                                            *
 *      3.) This function does not accept negative inputs. Use the absolute   *
 *          value of the input if -1/2 <= x <= -1/4.                          *
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
#ifndef TMPL_COSS_TAIL_END_FLOAT_H
#define TMPL_COSS_TAIL_END_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.8696044061688375074196906992080760207323347107432E+00F)
#define A01 (-3.9482057633325015108999650832214997112484606258062E+00F)
#define A02 (-2.6476317540211562755681573218884357189772571002431E+01F)
#define A03 (+8.0791893232786401693160131711793194525206899824950E+00F)
#define A04 (+2.3120822297099184130870778716697345730858312488177E+01F)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (-4.0003714392576009761845432172436386453510420448588E-01F)
#define B02 (+6.0723418309791417014714834303220093888726467269893E-01F)
#define B03 (-4.9818395626363871012852858986496663904001906717768E-01F)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*B03))

/*  Computes the squared cosine window via a rational Remez expansion.        */
TMPL_STATIC_INLINE
float tmpl_Float_Coss_Tail_End(const float x)
{
    /*  The polynomials are in terms of x - 1 / 2. Compute.                   */
    const float shift = x - 0.5F;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const float numer = TMPL_NUM_EVAL(shift);
    const float denom = TMPL_DEN_EVAL(shift);

    /*  The squared cosine window is the ratio scaled by the translation.     */
    return shift * shift * numer / denom;
}
/*  End of tmpl_Float_Coss_Tail_End.                                          */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
