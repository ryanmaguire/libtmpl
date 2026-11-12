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
#define A00 (+1.2810252304406972486120109535816568934847264625400E+00)
#define A01 (-4.0484052648574630462581331912608769396074592922513E+00)
#define A02 (-4.7972532776743966087173847292196857298797697019924E+00)
#define A03 (+2.4424574932939250732516808901118164990997677343368E+01)
#define A04 (-1.6804320822570014076769180928327851026907536501678E+01)
#define A05 (-3.3311938222189006681631968216993613706183079115091E+00)
#define A06 (+2.3300469518272892996538826310339664734701331835423E+00)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (-3.6731058597880585471659357686838038961868829899774E+00)
#define B02 (-2.6606846391928424735802870740486381412339686695071E+00)
#define B03 (+2.2061950193310168293427078933270091574344541746879E+01)
#define B04 (-1.9974282302319488739647035513096559624368403266214E+01)
#define B05 (-2.4025119038699931555070688372327351814284720795078E+00)
#define B06 (+4.5414368669168018480544500989011482168218305220203E+00)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * A06\
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
                B04 + z * (\
                    B05 + z * B06\
                )\
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

    /*  The Remez approximation is evaluated on the interval [-1/8, +1/8].    *
     *  The input lies in the interval [1/2, 3/4], shift by 5/8.              */
    const double x_shift = x - 0.625;

    /*  Evaluate the rational Remez approximation using Horner's method.      */
    const double p = TMPL_NUM_EVAL(x_shift);
    const double q = TMPL_DEN_EVAL(x_shift);
    const double rat = p / q;

    /*  The approximation is for (asin(x) - asin(5/8)) / (x - 5/8). Compute   *
     *  asin(x) from this.                                                    */
    const double low_bits = asin_five_eigths_lo + x_shift * rat;
    return asin_five_eigths_hi + low_bits;
}
/*  End of tmpl_Double_Arcsin_Aux_Shifted_Rat_Remez.                          */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
