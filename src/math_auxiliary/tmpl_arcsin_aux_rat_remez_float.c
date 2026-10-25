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
 *                      tmpl_arcsin_aux_rat_remez_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a degree (6, 2) rational Remez approximation for             *
 *      (asin(x) - x) / x at single precision.                                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arcsin_Aux_Rat_Remez                                       *
 *  Purpose:                                                                  *
 *      Computes a degree (6, 2) rational Remez approximation for             *
 *      (asin(x) - x) / x at single precision with |x| < 1/2.                 *
 *  Arguments:                                                                *
 *      x_sq (const float):                                                   *
 *          The square of a real number in the interval [-1/2, 1/2].          *
 *  Output:                                                                   *
 *      asin_aux_x (float):                                                   *
 *          (asin(x) - x) / x to single precision.                            *
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
 *      is even, so the degree (4, 2) rational Remez approximation for f(x)   *
 *      on [-1/2, 1/2] only requires 2 + 1 = 3 non-zero terms in the          *
 *      numerator and 1 + 1 = 2 non-zero terms in the denominator. The        *
 *      polynomials are evaluated using Horner's method and then x^2 * r(x)   *
 *      is returned, where r is the rational Remez approximation.             *
 *  Notes:                                                                    *
 *      1.) Accurate to single precision for |x| < 1/2. There are no checks   *
 *          that the input falls within this interval.                        *
 *                                                                            *
 *      2.) This function takes in the square of x, not x. This is to avoid   *
 *          precision loss when used in the tail-end acos and asin functions  *
 *          since these use z = sqrt((1 - |x|) / 2). It is more accurate      *
 *          (and less redundant) to evaluate using (1 - |x|) / 2 directly,    *
 *          rather than accepting z as an input and then using z * z for the  *
 *          rational Remez approximation. Because of floating-point round-off *
 *          it is possible that z * z and (1 - |x|) / 2 are not identical.    *
 *          Accepting the square of the input as the argument avoids this.    *
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
#define A00 (+1.6666657332654782511630744878585859634321997276656E-01F)
#define A01 (-4.2035660448040502977938914900697450640872894337286E-02F)
#define A02 (-8.2125492968317658201629446415138054874693066700587E-03F)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (-7.0227698493007347430817019567204548858969498944150E-01F)

/*  Helper macros for evaluating polynomials using Horner's method.           */
#define TMPL_NUM_EVAL(z) A00 + z * (A01 + z * A02)
#define TMPL_DEN_EVAL(z) B00 + z * B01

/*  Computes a degree (6, 2) Remez approximation for (asin(x) - x) / x.       */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float
tmpl_Float_Arcsin_Aux_Rat_Remez(const float x_sq)
TMPL_UNSEQUENCED
{
    /*  Evaluate the rational Remez approximation using Horner's method.      */
    const float num = TMPL_NUM_EVAL(x_sq);
    const float den = TMPL_DEN_EVAL(x_sq);
    const float rat = num / den;

    /*  (asin(x) - x) / x is given by scaling the rational function by x^2.   */
    return x_sq * rat;
}
/*  End of tmpl_Float_Arcsin_Aux_Rat_Remez.                                   */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
