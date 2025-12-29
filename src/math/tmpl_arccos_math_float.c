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
 *                             tmpl_arccos_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-cosine function at single precision.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arccos                                                     *
 *  Purpose:                                                                  *
 *      Computes acos(x), the inverse cosine function.                        *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (float):                                                       *
 *          The arc-cosine of x.                                              *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/auxiliary/                                               *
 *              tmpl_Float_Arccos_Maclaurin:                                  *
 *                  Computes acos via a Maclaurin series for |x| < 0.25.      *
 *              tmpl_Float_Arccos_Rat_Remez:                                  *
 *                  Computes acos via a minimax approximation for |x| < 0.5.  *
 *              tmpl_Float_Arccos_Tail_End:                                   *
 *                  Computes acos(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          0 <= |x| < 2^-26:                                                 *
 *              return pi / 2. The error is O(x). This avoids unnecessary     *
 *              underflow in the computation.                                 *
 *          2^-26 <= |x| < 2^-2:                                              *
 *              Use a degree 9 Maclaurin series. Only 5 non-zero terms are    *
 *              needed for the expansion.                                     *
 *          2^-2 <= |x| < 2^-1:                                               *
 *              Use the degree (4, 2) rational Remez approximation for the    *
 *              function R(x) = -(acos(x) - pi/2 + x)/x^3. This function is   *
 *              is even, so the degree (4, 2) rational Remez approximation    *
 *              requires 3 non-zero terms in the numerator and 2 non-zero     *
 *              terms in the denominator, 5 non-zero terms total. acos(x)     *
 *              is computed via:                                              *
 *                                                                            *
 *                  acos(x) = pi/2 - (x + x^3 * P(x) / Q(x))                  *
 *                                                                            *
 *              where P(x) is the numerator and Q(x) is the denominator for   *
 *              the rational Remez approximation of R(x), respectively.       *
 *          2^-1 <= x < 1:                                                    *
 *              Compute using the reflection formula:                         *
 *                                                                            *
 *                  acos(x) = 2 * asin(sqrt((1 - x) / 2))                     *
 *                                                                            *
 *              Note that as x tends to 1, sqrt((1 - x) / 2) tends to zero.   *
 *              Since acos(1) = 0, using this trick allows us to maintain     *
 *              excellent relative error as the argument approaches 1.        *
 *                                                                            *
 *              asin(z) is computed using a degree (4, 2) rational Remez      *
 *              approximation for R(z) = (asin(z) - z) / z^3. This function   *
 *              is even, meaning 3 non-zero terms are required for the        *
 *              numerator, and 2 for the denominator, 5 non-zero terms are    *
 *              needed in total. asin(z) is computed via:                     *
 *                                                                            *
 *                  asin(z) = z + z^3 * P(z) / Q(z)                           *
 *                                                                            *
 *              where P(z) is the numerator and Q(z) is the denominator of    *
 *              the rational Remez approximation of R(z), respectively. The   *
 *              value acos(x) is then computed by:                            *
 *                                                                            *
 *                  acos(x) = 2 * asin(z)                                     *
 *                                                                            *
 *              with z = sqrt((1 - x) / 2).                                   *
 *          -1 < x <= -2^-1:                                                  *
 *              Compute using the negation formula:                           *
 *                                                                            *
 *                  acos(x) = pi - acos(-x)                                   *
 *                                                                            *
 *              we then have 2^-1 <= -x < 1, and hence can use the reflection *
 *              formula found in the previous case.                           *
 *          x = -1:                                                           *
 *              return pi.                                                    *
 *          x = 1:                                                            *
 *              return 0.                                                     *
 *          |x| > 1 (including x = +/- infinity) or x is Not-a-Number:        *
 *              return NaN.                                                   *
 *      Error:                                                                *
 *          Based on 1,577,937,714 samples with -1 < x < 1.                   *
 *              max relative error: 1.1920928955078125e-07                    *
 *              rms relative error: 5.0596198794068018e-08                    *
 *              max absolute error: 2.3841857910156250e-07                    *
 *              rms absolute error: 9.1275731819690602e-08                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-7).                                     *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/                                                         *
 *              tmpl_Float_Abs:                                               *
 *                  Computes the absolute value of a real number.             *
 *          src/math/auxiliary/                                               *
 *              tmpl_Float_Arccos_Maclaurin:                                  *
 *                  Computes acos via a Maclaurin series for |x| < 0.25.      *
 *              tmpl_Float_Arccos_Rat_Remez:                                  *
 *                  Computes acos via a minimax approximation for |x| < 0.5.  *
 *              tmpl_Float_Arccos_Tail_End:                                   *
 *                  Computes acos(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          Similar to the IEEE-754 version, but determine the size of the    *
 *          input using the absolute value function and comparing the output  *
 *          to the numbers 2^-26, 2^-2, 2^-1, and 1.0.                        *
 *      Error:                                                                *
 *          Based on 1,577,937,714 samples with -1 < x < 1.                   *
 *              max relative error: 1.1920928955078125e-07                    *
 *              rms relative error: 5.0596198794068018e-08                    *
 *              max absolute error: 2.3841857910156250e-07                    *
 *              rms absolute error: 9.1275731819690602e-08                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-7).                                     *
 *  Notes:                                                                    *
 *      1.) The only distinction between the IEEE-754 method and the portable *
 *          one is how the size of the input x is determined. The IEEE-754    *
 *          method examines the exponent of the input, the portable method    *
 *          computes the absolute value and compares the size of x directly   *
 *          with the numbers 2^-26, 2^-3, 2^-1, and 1. The IEEE-754 method is *
 *          hence slightly faster on most computers.                          *
 *                                                                            *
 *      2.) Both methods detect if the input is NaN or infinity. The IEEE-754 *
 *          detects NaN and Inf since the exponents of NaN and Inf are large, *
 *          and the portable method detects NaN since NaN should always       *
 *          produce false when a comparison is made (==, <, >, etc.).         *
 *  References:                                                               *
 *      1.) Maguire, Ryan (2024)                                              *
 *          tmpld                                                             *
 *          https://github.com/ryanmaguire/libtmpl_data                       *
 *                                                                            *
 *          Python library providing an implementation of the rational        *
 *          Remez exchange algorithm. The coefficients for the                *
 *          approximations used by this function were computed using this.    *
 *                                                                            *
 *      2.) Tasissa, Abiy (2019)                                              *
 *          Function Approximation and the Remez Exchange Algorithm.          *
 *          https://sites.tufts.edu/atasissa/files/2019/09/remez.pdf          *
 *                                                                            *
 *          Survey of the Remez polynomial and Remez exchange algorithm,      *
 *          including an excellent discussion on the rational Remez exchange  *
 *          algorithm. The implementation in tmpld is based on these notes.   *
 *                                                                            *
 *      3.) Abramowitz, Milton and Stegun, Irene (1964)                       *
 *          Handbook of Mathematical Functions                                *
 *          Applied Mathematics Series Volume 55,                             *
 *          National Bureau of Standards                                      *
 *                                                                            *
 *          Standard reference for formulas on mathematical functions. The    *
 *          inverse trigonometric functions are found in chapter 4 section 4. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_nan_float.h:                                                     *
 *          Header file providing single precision NaN (Not-a-Number).        *
 *  3.) tmpl_math_constants.h:                                                *
 *          Header file providing pi and pi / 2.                              *
 *  4.) tmpl_ieee754_float.h:                                                 *
 *          Header file where the tmpl_IEEE754_Float type is defined.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 03, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/13: Ryan Maguire                                                  *
 *      Added comments, algorithm description, and fixed error values.        *
 *  2023/05/31: Ryan Maguire                                                  *
 *      Added optimizations for small x, |x| < 0.25, and denormal values.     *
 *  2024/10/28: Ryan Maguire                                                  *
 *      Replacing use of const variables with macros for multiples of pi.     *
 *  2025/02/13: Ryan Maguire                                                  *
 *      Removed redundant "else", introduced tmpl_math_constants.h, improved  *
 *      explanation of algorithm, added references.                           *
 *  2025/04/05: Ryan Maguire                                                  *
 *      Removed tmpl_math.h as a dependency. A forward declaration is now     *
 *      provided for the function in this file and NAN is included directly.  *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Forward declaration for the function, also found in tmpl_math.h.          */
extern float tmpl_Float_Arccos(const float x);

/*  Mathematical constants like pi and pi / 2 are found here.                 */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  TMPL_NANF macro found here which provides single precision NaN.           */
#include <libtmpl/include/nan/tmpl_nan_float.h>

/*  TMPL_HAS_IEEE754_FLOAT macro and tmpl_IEEE754_Float type given here.      */
#include <libtmpl/include/types/tmpl_ieee754_float.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Maclaurin expansion provided here.                                        */
#include "auxiliary/tmpl_arccos_maclaurin_float.h"

/*  Rational Remez minimax approximation for arccos.                          */
#include "auxiliary/tmpl_arccos_rat_remez_float.h"

/*  Tail-end arccos function that uses the reflection formula with arcsin.    */
#include "auxiliary/tmpl_arccos_tail_end_float.h"

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  On most computers it is faster to check the value of the exponent of a    *
 *  float rather than checking the entire float. This gives the IEEE-754      *
 *  method a slight performance boost over the portable one below.            */

/*  Single precision inverse cosine (acosf equivalent).                       */
float tmpl_Float_Arccos(const float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the word to the input.                          */
    w.r = x;

    /*  Small inputs, |x| < 0.5.                                              */
    if (TMPL_FLOAT_EXPO_BITS(w) < TMPL_FLOAT_UBIAS - 1U)
    {
        /*  For |x| < 2^-26, acos(x) = pi / 2 to single precision.            */
        if (TMPL_FLOAT_EXPO_BITS(w) < TMPL_FLOAT_UBIAS - 26U)
            return tmpl_float_pi_by_two;

        /*  For small x, |x| < 2^-2, the Maclaurin series is sufficient.      */
        if (TMPL_FLOAT_EXPO_BITS(w) < TMPL_FLOAT_UBIAS - 2U)
            return tmpl_Float_Arccos_Maclaurin(x);

        /*  For 0.25 <= |x| < 0.5 use the minimax approximation.              */
        return tmpl_Float_Arccos_Rat_Remez(x);
    }

    /*  For 0.5 <= |x| < 1 use the formula acos(x) = 2*asin(sqrt(1 - x) / 2). */
    if (TMPL_FLOAT_EXPO_BITS(w) < TMPL_FLOAT_UBIAS)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (TMPL_FLOAT_IS_NEGATIVE(w))
            return tmpl_float_pi - tmpl_Float_Arccos_Tail_End(-x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_Float_Arccos_Tail_End(x);
    }

    /*  Since cos(pi) = -1, we have acos(-1) = pi. Return pi.                 */
    if (x == -1.0F)
        return tmpl_float_pi;

    /*  Similarly, since cos(0) = 1 we have acos(1) = 0. Use this.            */
    if (x == 1.0F)
        return 0.0F;

    /*  For a real input, acos(x) is undefined with |x| > 1. Return NaN. Note *
     *  this catches NaN and infinity since we are checking the exponent of   *
     *  the input, not the input. For x = NaN or Inf, the exponent is greater *
     *  than TMPL_FLOAT_UBIAS, hence NaN will return.                         */
    return TMPL_NANF;
}
/*  End of tmpl_Float_Arccos.                                                 */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  The approximation used (Maclaurin, Remez, or reflection formula) depends  *
 *  on the size of the input. We compute this via the absolute value function.*/
#if TMPL_USE_INLINE == 1

/*  The absolute value function is small and should be inlined.               */
#include <libtmpl/include/inline/math/tmpl_abs_float.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern float tmpl_Float_Abs(float x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Single precision inverse cosine (acosf equivalent).                       */
float tmpl_Float_Arccos(const float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const float abs_x = tmpl_Float_Abs(x);

    /*  Small inputs, |x| < 0.5.                                              */
    if (abs_x < 0.5F)
    {
        /*  For very small inputs return pi / 2.                              */
        if (abs_x < 1.4901161193847656E-08F)
            return tmpl_float_pi_by_two;

        /*  Small inputs, |x| < 0.25, use the Maclaurin series.               */
        if (abs_x < 0.25F)
            return tmpl_Float_Arccos_Maclaurin(x);

        /*  Otherwise use the Remez rational minimax function.                */
        return tmpl_Float_Arccos_Rat_Remez(x);
    }

    /*  For 0.5 <= |x| < 1 use the formula acos(x) = 2*asin(sqrt(1 - x) / 2). */
    if (abs_x < 1.0F)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (x < 0.0F)
            return tmpl_float_pi - tmpl_Float_Arccos_Tail_End(abs_x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_Float_Arccos_Tail_End(abs_x);
    }

    /*  Since cos(pi) = -1, we have acos(-1) = pi. Return pi.                 */
    if (x == -1.0F)
        return tmpl_float_pi;

    /*  Similarly, since cos(0) = 1 we have acos(1) = 0. Use this.            */
    if (x == 1.0F)
        return 0.0F;

    /*  For |x| > 1 the function is undefined. Return NaN.                    */
    return TMPL_NANF;
}
/*  End of tmpl_Float_Arccos.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
