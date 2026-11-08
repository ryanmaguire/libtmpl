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
 *                  tmpl_arcsin_aux_shifted_rat_remez_float                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a degree (3, 2) rational Remez approximation for asin(x)     *
 *      centered about 5/8 on the interval [1/2, 3/4].                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arcsin_Aux_Shifted_Rat_Remez                               *
 *  Purpose:                                                                  *
 *      Computes a degree (3, 2) rational Remez approximation for asin(x)     *
 *      on the interval [1/2, 3/4] by shifting the input by 5/8.              *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number in the interval [1/2, 3/4].                         *
 *  Output:                                                                   *
 *      asin_x (float):                                                       *
 *          asin(x) to single precision.                                      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the degree (3, 2) rational Remez approximation   *
 *      on the interval [-1/8, 1/8] for the function                          *
 *                                                                            *
 *                 asin(x + 5/8) - asin(5/8)                                  *
 *          f(x) = -------------------------                                  *
 *                             x                                              *
 *                                                                            *
 *      have been pre-computed. asin(x) is computed using                     *
 *                                                                            *
 *          asin(x) = asin(5/8) + (x - 5/8) * r(x - 5/8)                      *
 *                                                                            *
 *      where r is the rational Remez approximation.                          *
 *  Notes:                                                                    *
 *      1.) Accurate to single precision for 1/2 <= x <= 3/4. There are no    *
 *          checks that the input falls within this interval.                 *
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
#define A00 (+1.2810252643511039209155474397854746088635500558517E+00F)
#define A01 (-2.9440103181850467651568689096733454711816716105581E+00F)
#define A02 (+1.0992998775292394508683037845115063222475803144392E+00F)
#define A03 (-2.2148281233964916311115213068861649129856926058803E-01F)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (-2.8109890591967050579295796146135007359303089216531E+00F)
#define B02 (+1.5002318717882009178136984333405138056215117732293E+00F)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z * (A01 + z * (A02 + z * A03))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z * (B01 + z * B02)

/*  Computes a degree (3, 2) Remez approximation for asin(x) on [1/2, 3/4].   */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float
tmpl_Float_Arcsin_Aux_Shifted_Rat_Remez(const float x)
TMPL_UNSEQUENCED
{
    /*  asin(5/8) to extra precision using two float.                         */
    const float asin_three_eigths_hi = +6.75131559371948242187500000000000E-01F;
    const float asin_three_eigths_lo = -2.64349165949784437347056119857958E-08F;

    /*  The Remez approximation is evaluated on the interval [-1/8, +1/8].    *
     *  The input lies in the interval [1/2, 3/4], shift by 5/8.              */
    const float x_shift = x - 0.625;

    /*  Evaluate the rational Remez approximation using Horner's method.      */
    const float p = TMPL_NUM_EVAL(x_shift);
    const float q = TMPL_DEN_EVAL(x_shift);
    const float rat = p / q;

    /*  The approximation is for (asin(x) - asin(5/8)) / (x - 5/8). Compute   *
     *  asin(x) from this.                                                    */
    const float low_bits = asin_three_eigths_lo + x_shift * rat;
    return asin_three_eigths_hi + low_bits;
}
/*  End of tmpl_Float_Arcsin_Aux_Shifted_Rat_Remez.                           */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
