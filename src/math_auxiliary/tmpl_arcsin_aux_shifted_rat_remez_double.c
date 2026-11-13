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
 *                  tmpl_arcsin_aux_shifted_rat_remez_double                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a degree (6, 6) rational Remez approximation for asin(x)     *
 *      centered about 5/8 on the interval [1/2, 3/4].                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arcsin_Aux_Shifted_Rat_Remez                              *
 *  Purpose:                                                                  *
 *      Computes a degree (6, 6) rational Remez approximation for asin(x)     *
 *      on the interval [1/2, 3/4] by shifting the input by 5/8.              *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [1/2, 3/4].                         *
 *  Output:                                                                   *
 *      asin_x (double):                                                      *
 *          asin(x) to double precision.                                      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the degree (6, 6) rational Remez approximation   *
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
 *      1.) Accurate to double precision for 1/2 <= x <= 3/4. There are no    *
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
#define A00 (+1.3344436835559487348879135985582150040851448769023E-01)
#define A01 (+1.5850939460118861753591253554779128424296717122239E-01)
#define A02 (-3.4790105454763919490052872718956943507568538724053E+00)
#define A03 (-9.5282886310808523032328658836945258814661045992240E+00)
#define A04 (-2.7006880781573085081467861751393518552136158294742E+00)
#define A05 (+5.2980266507821478008609558491657694598239515554822E+00)
#define A06 (+2.4082762004951195142121460286855491545618532260509E-01)
#define A07 (-1.8158698171024473479509877346031357114353500823549E-01)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+8.8862317583292433340168770413977011829374945999071E+00)
#define B02 (+2.6238110506827359465626951188932136194423073185919E+01)
#define B03 (+2.6414492435708310281248923902571653364992722983936E+01)
#define B04 (-1.0145185203393713450355580878493330719365504477551E+00)
#define B05 (-8.4842995242438348748321092852306806413581401753003E+00)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * (\
                        A06 + z * A07\
                    )\
                )\
            )\
        )\
    )\
)

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
B00 + z * (\
    B01 + z * (\
        B02 + z * (\
            B03 + z * (\
                B04 + z * B05\
            )\
        )\
    )\
)

/*  Computes a degree (6, 6) Remez approximation for asin(x) on [1/2, 3/4].   */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Arcsin_Aux_Shifted_Rat_Remez(const double x)
TMPL_UNSEQUENCED
{
    /*  asin(5/8) to extra precision using two doubles.                       */
    const double asin_five_eigths_hi = +6.75131532937031653140991238615243E-01;
    const double asin_five_eigths_lo = -5.93193497332085475014956678498079E-18;

    /*  The Remez approximation is evaluated on the interval [0, 1/4], the    *
     *  The input lies in the interval [1/2, 3/4], shift by 3/4.              */
    const double x_shift = 0.75 - x;

    /*  The approximation is centered about 5/8, compute the shift.           */
    const double h = x - 0.625;

    /*  Evaluate the rational Remez approximation using Horner's method.      */
    const double num = TMPL_NUM_EVAL(x_shift);
    const double den = TMPL_DEN_EVAL(x_shift);
    const double rat = num / den;

    /*  The approximation is for (asin(x) - asin(5/8)) / (x - 5/8). Compute   *
     *  asin(x) from this.                                                    */
    const double low_bits = asin_five_eigths_lo + h * rat;
    return asin_five_eigths_hi + (1.25 * h + low_bits);
}
/*  End of tmpl_Double_Arcsin_Aux_Shifted_Rat_Remez.                          */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
