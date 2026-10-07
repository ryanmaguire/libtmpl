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
 *                      tmpl_arcsin_aux_rat_remez_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a degree (10, 8) rational Remez approximation for            *
 *      (asin(x) - x) / x at double precision.                                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arcsin_Aux_Rat_Remez                                      *
 *  Purpose:                                                                  *
 *      Computes a degree (10, 8) rational Remez approximation for            *
 *      (asin(x) - x) / x at double precision with |x| < 1/2.                 *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [-1/2, 1/2].                        *
 *  Output:                                                                   *
 *      asin_aux_x (double):                                                  *
 *          (asin(x) - x) / x to double precision.                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The function                                                          *
 *                                                                            *
 *                 asin(x) - x                                                *
 *          f(x) = -----------                                                *
 *                       3                                                    *
 *                      x                                                     *
 *                                                                            *
 *      is even, so the degree (8, 8) rational Remez approximation for f(x)   *
 *      on [-1/2, 1/2] only requires 4 + 1 = 5 non-zero terms in both the     *
 *      numerator and denominator. The polynomials are evaluated using        *
 *      Horner's method and then x^2 * r(x) is returned, where r is the       *
 *      rational Remez approximation.                                         *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for |x| < 1/2. There are no checks   *
 *          that the input falls within this interval.                        *
 *  References:                                                               *
 *      1.) Maguire, Ryan (2024)                                              *
 *          tmpld                                                             *
 *          https://github.com/ryanmaguire/libtmpl_data                       *
 *                                                                            *
 *          Python library providing an implementation of the rational        *
 *          Remez exchange algorithm. The coefficients for the                *
 *          approximation used by this function were computed using this.     *
 *                                                                            *
 *      2.) Tasissa, Abiy (2019)                                              *
 *          Function Approximation and the Remez Exchange Algorithm.          *
 *          https://sites.tufts.edu/atasissa/files/2019/09/remez.pdf          *
 *                                                                            *
 *          Survey of the Remez polynomial and Remez exchange algorithm.      *
 *          The implementation in tmpld is based on these notes.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_math_auxiliary.h:                                                *
 *          Contains the function prototype / forward declaration.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 6, 2026                                               *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+1.6666666666666675172610409335401762495970069423667E-01)
#define A01 (-2.9647442738212244852684254810912673101657174481766E-01)
#define A02 (+1.6001969221867813049084016184632874497094695883901E-01)
#define A03 (-2.5510481570872249173776491491771394448907125511346E-02)
#define A04 (+2.6066097969323856113412749790103952111930280796716E-04)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (-2.2288465642924490579275829949790393075345284377974E+00)
#define B02 (+1.6952419643599424152439428142515867324057155650851E+00)
#define B03 (-5.0120096652328631713045487959099718175996563925832E-01)
#define B04 (+4.5088915315077310386265964807853660211534733521946E-02)

/*  Helper macros for evaluating polynomials using Horner's method.           */
#define TMPL_NUM_EVAL(z) A00 + z * (A01 + z * (A02 + z * (A03 + z * A04)))
#define TMPL_DEN_EVAL(z) B00 + z * (B01 + z * (B02 + z * (B03 + z * B04)))

/*  Computes a degree (10, 8) Remez approximation for (asin(x) - x) / x.      */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Arcsin_Aux_Rat_Remez(const double x)
TMPL_UNSEQUENCED
{
    /*  The Remez approximation for (asin(x) - x) / x^3 is even. Compute x^2. */
    const double x2 = x * x;

    /*  Evaluate the rational Remez approximation using Horner's method.      */
    const double num = TMPL_NUM_EVAL(x2);
    const double den = TMPL_DEN_EVAL(x2);
    const double rat = num / den;

    /*  (asin(x) - x) / x is given by scaling the rational function by x^2.   */
    return x2 * rat;
}
/*  End of tmpl_Double_Arcsin_Aux_Rat_Remez.                                  */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
