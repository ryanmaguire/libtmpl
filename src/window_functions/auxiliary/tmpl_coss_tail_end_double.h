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
 *                         tmpl_coss_tail_end_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the squared cosine window for x near 1 / 2.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Coss_Tail_End                                             *
 *  Purpose:                                                                  *
 *      Computes the squared cosine window using a rational Remez             *
 *      approximation for 1 / 4 <= x <= 1 / 2.                                *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      coss_x (double):                                                      *
 *          The squared cosine of x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The squared cosine window can be expanded about x = 1 / 2 in terms    *
 *      of x - 1 / 2. The coefficients for the (6, 6) rational Remez          *
 *      approximation for the function:                                       *
 *                                                                            *
 *                 Coss(x + 1 / 2)                                            *
 *          f(x) = ---------------                                            *
 *                        2                                                   *
 *                       x                                                    *
 *                                                                            *
 *      on the interval [-1/4, 0] (the limit of f at zero is used to avoid a  *
 *      division by zero), where Coss represents the squared cosine window,   *
 *      have been pre-computed below. Given x with 1 / 4 <= x <= 1 / 2, we    *
 *      translate x into this interval using:                                 *
 *                                                                            *
 *                     1                                                      *
 *          t(x) = x - -                                                      *
 *                     2                                                      *
 *                                                                            *
 *      and then return t(x)^2 * P(t(x)) / Q(t(x)), where P and Q are the     *
 *      numerator and denominator, respectively, for the degree (6, 6)        *
 *      rational minimax approximation for f.                                 *
 *                                                                            *
 *      Note that since we scale the result by t(x)^2, the approximation is   *
 *      zero, exact, when x = 1 / 2. That is, the window goes to zero at the  *
 *      right endpoint in the window.                                         *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for 0.25 <= x <= 0.5.                *
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
#ifndef TMPL_COSS_TAIL_END_DOUBLE_H
#define TMPL_COSS_TAIL_END_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.8696044010893586824329547474673439140231054116780E+00)
#define A01 (+4.1647184904568528445364666288540106779119337166960E-01)
#define A02 (-2.4136360656962329950727086127689298722114082152450E+01)
#define A03 (-9.5448863792651996029791063270767758721509615075691E-01)
#define A04 (+1.8647970303817305011034580719878434061915137689507E+01)
#define A05 (+5.9632459933589183805630582645746132153056504681312E-01)
#define A06 (-4.3418192157556894760118122867013711529066539213096E+00)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+4.2197420699013371567416842553524757201407202681295E-02)
#define B02 (+8.4434350311280177014393653960965466579522394674775E-01)
#define B03 (+4.2114030951057903183272843119015208642281408199238E-02)
#define B04 (+3.3792026629994898311416323969857683590745206390916E-01)
#define B05 (+1.6284730518041398561273679141628350855706280155634E-02)
#define B06 (+6.8410307571893272522513404516975144026427994193341E-02)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*(A05 + z*A06)))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
B00 + z*(B01 + z*(B02 + z*(B03 + z*(B04 + z*(B05 + z*B06)))))

/*  Computes the squared cosine window via a rational Remez expansion.        */
TMPL_STATIC_INLINE
double tmpl_Double_Coss_Tail_End(const double x)
{
    /*  The polynomials are in terms of x - 1 / 2. Compute.                   */
    const double shift = x - 0.5;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const double numer = TMPL_NUM_EVAL(shift);
    const double denom = TMPL_DEN_EVAL(shift);

    /*  The squared cosine window is the ratio scaled by the translation.     */
    return shift * shift * numer / denom;
}
/*  End of tmpl_Double_Coss_Tail_End.                                         */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
