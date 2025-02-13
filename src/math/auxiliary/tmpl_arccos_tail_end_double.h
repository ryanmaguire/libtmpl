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
 *                        tmpl_arccos_tail_end_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes acos(x) for 0.5 <= x < 1 at double precision.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arccos_Tail_End                                           *
 *  Purpose:                                                                  *
 *      Computes arccos for 0.5 <= x < 1.0.                                   *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (double):                                                      *
 *          The inverse cosine of x.                                          *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Sqrt:                                                 *
 *              Computes the square root of a number.                         *
 *  Method:                                                                   *
 *      Use the following trig identity:                                      *
 *                                                                            *
 *          acos(x) = 2 * asin(sqrt((1 - x) / 2))                             *
 *                                                                            *
 *      The function f(z) = (asin(z) - z) / z^3 is even, meaning the degree   *
 *      (8, 8) rational Remez approximation R(z) requires 5 non-zero terms in *
 *      the numerator and 5 non-zero terms in the denominator, 10 non-zero    *
 *      terms total. asin(z) is computed via:                                 *
 *                                                                            *
 *          asin(z) = z + z^3 * P(z) / Q(z)                                   *
 *                                                                            *
 *      where P(z) is the numerator and Q(z) is the denominator of R(z),      *
 *      respectively. acos(x) is the computed by:                             *
 *                                                                            *
 *          acos(x) = 2 * asin(z)                                             *
 *                                                                            *
 *      with z = sqrt((1 - x) / 2).                                           *
 *  Notes:                                                                    *
 *      Accurate for 0.5 <= x < 1.0.                                          *
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
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_tail_end_double.c to include this file.  *
 *  2024/11/08: Ryan Maguire                                                  *
 *      Updating coefficients to use the (8, 8) approximant.                  *
 *  2025/02/13: Ryan Maguire                                                  *
 *      Added references and a more detailed description of the algorithm.    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_TAIL_END_DOUBLE_H
#define TMPL_ARCCOS_TAIL_END_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  The compiler needs to know about the sqrt function.                       */
extern double tmpl_Double_Sqrt(double x);

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
#define TMPL_POLYA_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))
#define TMPL_POLYB_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  Function for computing acos(x) for 0.5 <= x < 1.0.                        */
TMPL_STATIC_INLINE
double tmpl_Double_Arccos_Tail_End(double x)
{
    /*  The rational function is computed in terms of (1 - x) / 2.            */
    const double z = 0.5 * (1.0 - x);

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const double p = TMPL_POLYA_EVAL(z);
    const double q = TMPL_POLYB_EVAL(z);

    /*  p(z) / q(z) is the rational minimax approximation for                 *
     *  (asin(sqrt(z)) - sqrt(z)) / z^{3/2}. We need to multiply by z^{3/2}.  */
    const double sqrt_z = tmpl_Double_Sqrt(z);
    const double t = sqrt_z * z * p / q;

    /*  We now have t = asin(sqrt(z)) - sqrt(z). We need 2*asin(sqrt(z)).     */
    return 2.0 * (sqrt_z + t);
}
/*  End of tmpl_Double_Arccos_Tail_End.                                       */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
