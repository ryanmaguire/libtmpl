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
 *                         tmpl_arccos_tail_end_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes acos(x) for 0.5 <= x < 1 at single precision.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arccos_Tail_End                                            *
 *  Purpose:                                                                  *
 *      Computes arccos for 0.5 <= x < 1.0.                                   *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (float):                                                       *
 *          The inverse cosine of x.                                          *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Float_Sqrt:                                                  *
 *              Computes the square root of a number.                         *
 *  Method:                                                                   *
 *      Use the following trig identity:                                      *
 *                                                                            *
 *          acos(x) = 2 * asin(sqrt((1 - x) / 2))                             *
 *                                                                            *
 *      The function f(z) = (asin(z) - z) / z^3 is even, meaning the degree   *
 *      (4, 2) rational Remez approximation R(z) requires 3 non-zero terms in *
 *      the numerator and 2 non-zero terms in the denominator, 5 non-zero     *
 *      terms total. asin(z) is computed via:                                 *
 *                                                                            *
 *          asin(z) = z + z^3 * P(z) / Q(z)                                   *
 *                                                                            *
 *      where P(z) is the numerator and Q(z) is the denominator of R(z),      *
 *      respectively. acos(x) is then computed by:                            *
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
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_tail_end_float.c to include this file.   *
 *  2024/11/08: Ryan Maguire                                                  *
 *      Changed coefficients to be the exact output of the Python scripts in  *
 *      libtmpl_data. This is to improve reproducibility of the results.      *
 *  2026/06/12: Ryan Maguire                                                  *
 *      Added references.                                                     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_TAIL_END_FLOAT_H
#define TMPL_ARCCOS_TAIL_END_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  The compiler needs to know about the sqrt function.                       */
TMPL_CONST_FUNC
extern float tmpl_Float_Sqrt(const float x)
TMPL_UNSEQUENCED;

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.6666657332654782511630744878585859634321997276656E-01F)
#define A01 (-4.2035660448040502977938914900697450640872894337286E-02F)
#define A02 (-8.2125492968317658201629446415138054874693066700587E-03F)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (-7.0227698493007347430817019567204548858969498944150E-01F)

/*  Helper macros for evaluating polynomials using Horner's method.           */
#define TMPL_NUM_EVAL(z) A00 + z * (A01 + z * A02)
#define TMPL_DEN_EVAL(z) B00 + z * B01

/*  Function for computing acos(x) for 0.5 <= x < 1.0.                        */
TMPL_CONST_FUNC
TMPL_STATIC_INLINE
float tmpl_Float_Arccos_Tail_End(const float x)
TMPL_UNSEQUENCED
{
    /*  Rational function is computed in terms of (1 - x)/2.                  */
    const float z = 0.5F * (1.0F - x);

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const float p = TMPL_NUM_EVAL(z);
    const float q = TMPL_DEN_EVAL(z);

    /*  p(z) / q(z) is the rational minimax approximant for                   *
     *  (asin(sqrt(z)) - sqrt(z)) / z^{3/2}. We need to multiply by z^{3/2}.  */
    const float r = z * p / q;
    const float sqrt_z = tmpl_Float_Sqrt(z);
    const float t = r * sqrt_z;

    /*  We now have t = asin(sqrt(z)) - sqrt(z). We need 2*asin(sqrt(z)).     */
    return 2.0F * (sqrt_z + t);
}
/*  End of tmpl_Float_Arccos_Tail_End.                                        */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
