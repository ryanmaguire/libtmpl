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
 *                        tmpl_kbmd20_tail_end_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2).               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_KBMD20_Tail_End                                           *
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) using a        *
 *      rational Remez approximation for 1 / 4 <= x <= 1 / 2.                 *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      kbmd20_x (double):                                                    *
 *          The Kaiser-Bessel window (alpha = 2) of x.                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The modified Kaiser-Bessel window can be expanded about x = 1 / 2 in  *
 *      terms of x - 1 / 2. The coefficients for the (8, 6) rational Remez    *
 *      approximation for the function:                                       *
 *                                                                            *
 *                 KBMD20(x + 1 / 2)                                          *
 *          f(x) = -----------------                                          *
 *                         x                                                  *
 *                                                                            *
 *      on the interval [-1/4, 0] (the limit of f at zero is used to avoid a  *
 *      division by zero), where KBMD20 represents the modified Kaiser-Bessel *
 *      window with alpha = 2, have been pre-computed below. Given x with     *
 *      1 / 4 <= x <= 1 / 2, we translate x into this interval using:         *
 *                                                                            *
 *                     1                                                      *
 *          t(x) = x - -                                                      *
 *                     2                                                      *
 *                                                                            *
 *      and then return t(x) * P(t(x)) / Q(t(x)), where P and Q are the       *
 *      numerator and denominator, respectively, for the degree (8, 6)        *
 *      rational minimax approximation for f.                                 *
 *                                                                            *
 *      Note that since we scale the result by t(x), the approximation is     *
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
 *  Date:       February 18, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_KBMD20_TAIL_END_DOUBLE_H
#define TMPL_KBMD20_TAIL_END_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (-4.5847288850771500899519121342862207284106326971267E-01)
#define A01 (+3.7703430459325869351666011886888007493805010737097E+00)
#define A02 (-9.2748851460735770070873687837606018595281772953278E+00)
#define A03 (-3.8267011521033769098516401710300698080047799965873E+00)
#define A04 (+3.3241952707923226984534441308247753279970050447856E+01)
#define A05 (-8.8023196313354674135314845279407756721537549999632E+00)
#define A06 (-4.3525180967189236054858575836264308737025742917772E+01)
#define A07 (+1.2013007956983332028738370656593394262634958622036E+01)
#define A08 (+2.3806275613935762858840601619804706484041671686613E+01)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+6.4590537669403026293698188389403347665806182276329E-01)
#define B02 (+2.4051579740584122995183821213142052648841929286432E+00)
#define B03 (+1.2777876092667613335039744181571401022051044423763E+00)
#define B04 (+2.3792291101954749461991531959571485074038718990322E+00)
#define B05 (+8.1892168756447741399149509936664863887984649458537E-01)
#define B06 (+9.2248073688651589231687136340824688169125570621861E-01)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*A08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
B00 + z*(\
    B01 + z*(\
        B02 + z*(\
            B03 + z*(\
                B04 + z*(\
                    B05 + z*B06\
                )\
            )\
        )\
    )\
)

/*  Computes the modified Kaiser-Bessel window via a rational Remez expansion.*/
TMPL_STATIC_INLINE
double tmpl_Double_KBMD20_Tail_End(const double x)
{
    /*  The polynomials are in terms of x - 1 / 2. Compute.                   */
    const double shift = x - 0.5;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const double numer = TMPL_NUM_EVAL(shift);
    const double denom = TMPL_DEN_EVAL(shift);

    /*  The Kaiser-Bessel window is the ratio scaled by the translation.      */
    return shift * numer / denom;
}
/*  End of tmpl_Double_KBMD20_Tail_End.                                       */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
