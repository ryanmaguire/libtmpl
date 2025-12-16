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
 *                             tmpl_arccos_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-cosine function at double precision.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arccos                                                    *
 *  Purpose:                                                                  *
 *      Computes acos(x), the inverse cosine function.                        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (double):                                                      *
 *          The arc-cosine of x.                                              *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/auxiliary/                                               *
 *              tmpl_Double_Arccos_Maclaurin:                                 *
 *                  Computes acos via a Maclaurin series for |x| < 0.125.     *
 *              tmpl_Double_Arccos_Rat_Remez:                                 *
 *                  Computes acos via a minimax approximation for |x| < 0.5.  *
 *              tmpl_Double_Arccos_Tail_End:                                  *
 *                  Computes acos(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          0 <= |x| < 2^-57:                                                 *
 *              return pi / 2. The error is O(x). This avoids unnecessary     *
 *              underflow in the computation.                                 *
 *          2^-57 <= |x| < 2^-3:                                              *
 *              Use a degree 15 Maclaurin series. Only 8 non-zero terms are   *
 *              needed for the expansion. This is faster than the rational    *
 *              Remez approximation since it requires fewer terms and avoids  *
 *              using floating-point division.                                *
 *          2^-3 <= |x| < 2^-1:                                               *
 *              Use the degree (8, 8) rational Remez approximation for the    *
 *              function R(x) = -(acos(x) - pi/2 + x)/x^3. This function is   *
 *              is even, so the degree (8, 8) rational Remez approximation    *
 *              requires 5 non-zero terms in the numerator and 5 non-zero     *
 *              terms in the denominator, 10 non-zero terms total. acos(x)    *
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
 *              asin(z) is computed using a degree (8, 8) rational Remez      *
 *              approximation for R(z) = (asin(z) - z) / z^3. This function   *
 *              is even, meaning 5 non-zero terms are required for the        *
 *              numerator, and 5 for the denominator, 10 non-zero terms are   *
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
 *          Based on 788,968,857 samples with -1 < x < 1.                     *
 *              max relative error: 2.2204459059627917E-16                    *
 *              rms relative error: 8.3796804351081161E-17                    *
 *              max absolute error: 4.4408920985006262E-16                    *
 *              rms absolute error: 1.4737238548161158E-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/                                                         *
 *              tmpl_Double_Abs:                                              *
 *                  Computes the absolute value of a real number.             *
 *          src/math/auxiliary/                                               *
 *              tmpl_Double_Arccos_Maclaurin:                                 *
 *                  Computes acos via a Maclaurin series for |x| < 0.125.     *
 *              tmpl_Double_Arccos_Rat_Remez:                                 *
 *                  Computes acos via a minimax approximation for |x| < 0.5.  *
 *              tmpl_Double_Arccos_Tail_End:                                  *
 *                  Computes acos(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          Similar to the IEEE-754 version, but determine the size of the    *
 *          input using the absolute value function and comparing the output  *
 *          to the numbers 2^-57, 2^-3, 2^-1, and 1.0.                        *
 *      Error:                                                                *
 *          Based on 788,968,857 samples with -1 < x < 1.                     *
 *              max relative error: 2.2204459059627917e-16                    *
 *              rms relative error: 8.3796804351081161e-17                    *
 *              max absolute error: 4.4408920985006262e-16                    *
 *              rms absolute error: 1.4737238548161158e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *  Notes:                                                                    *
 *      1.) The only distinction between the IEEE-754 method and the portable *
 *          one is how the size of the input x is determined. The IEEE-754    *
 *          method examines the exponent of the input, the portable method    *
 *          computes the absolute value and compares the size of x directly   *
 *          with the numbers 2^-57, 2^-3, 2^-1, and 1. The IEEE-754 method is *
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
 *  2.) tmpl_nan_double.h:                                                    *
 *          Header file providing double precision NaN (Not-a-Number).        *
 *  3.) tmpl_math_constants.h:                                                *
 *          Header file providing pi and pi / 2.                              *
 *  4.) tmpl_ieee754_double.h:                                                *
 *          Header file where the tmpl_IEEE754_Double type is defined.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 03, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/13: Ryan Maguire                                                  *
 *      Added comments, algorithm description, and fixed error values.        *
 *  2023/05/31: Ryan Maguire                                                  *
 *      Added optimizations for small x, |x| < 0.125, and denormal values.    *
 *  2024/10/28: Ryan Maguire                                                  *
 *      Replacing use of const variables with macros for multiples of pi.     *
 *  2025/01/25: Ryan Maguire                                                  *
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
extern double tmpl_Double_Arccos(double x);

/*  Mathematical constants like pi and pi / 2 are found here.                 */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  TMPL_NAN macro found here which provides double precision NaN.            */
#include <libtmpl/include/nan/tmpl_nan_double.h>

/*  TMPL_HAS_IEEE754_DOUBLE macro and tmpl_IEEE754_Double type given here.    */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Maclaurin expansion provided here.                                        */
#include "auxiliary/tmpl_arccos_maclaurin_double.h"

/*  Rational Remez minimax approximation for arccos.                          */
#include "auxiliary/tmpl_arccos_rat_remez_double.h"

/*  Tail-end arccos function that uses the reflection formula with arcsin.    */
#include "auxiliary/tmpl_arccos_tail_end_double.h"

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  On most computers it is faster to check the value of the exponent of a    *
 *  double rather than checking the entire double. This gives the IEEE-754    *
 *  method a slight performance boost over the portable one below.            */

/*  Double precision inverse cosine (acos equivalent).                        */
double tmpl_Double_Arccos(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  Small inputs, |x| < 0.5.                                              */
    if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 1U)
    {
        /*  For |x| < 2^-57, acos(x) = pi / 2 to double precision.            */
        if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 57U)
            return tmpl_Double_Pi_By_Two;

        /*  For small x, |x| < 2^-3, the Maclaurin series is sufficient.      */
        if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 3U)
            return tmpl_Double_Arccos_Maclaurin(x);

        /*  For 0.125 <= |x| < 0.5 use the minimax approximation.             */
        return tmpl_Double_Arccos_Rat_Remez(x);
    }

    /*  For 0.5 <= |x| < 1 use the formula acos(x) = 2*asin(sqrt(1 - x) / 2). */
    if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (TMPL_DOUBLE_IS_NEGATIVE(w))
            return tmpl_Double_Pi - tmpl_Double_Arccos_Tail_End(-x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_Double_Arccos_Tail_End(x);
    }

    /*  Since cos(pi) = -1, we have acos(-1) = pi. Return pi.                 */
    if (x == -1.0)
        return tmpl_Double_Pi;

    /*  Similarly, since cos(0) = 1 we have acos(1) = 0. Use this.            */
    if (x == 1.0)
        return 0.0;

    /*  For a real input, acos(x) is undefined with |x| > 1. Return NaN. Note *
     *  this catches NaN and infinity since we are checking the exponent of   *
     *  the input, not the input. For x = NaN or Inf, the exponent is greater *
     *  than TMPL_DOUBLE_UBIAS, hence NaN will return.                        */
    return TMPL_NAN;
}
/*  End of tmpl_Double_Arccos.                                                */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  The approximation used (Maclaurin, Remez, or reflection formula) depends  *
 *  on the size of the input. We compute this via the absolute value function.*/
#if TMPL_USE_INLINE == 1

/*  The absolute value function is small and should be inlined.               */
#include <libtmpl/include/inline/math/tmpl_abs_double.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern double tmpl_Double_Abs(double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Double precision inverse cosine (acos equivalent).                        */
double tmpl_Double_Arccos(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const double abs_x = tmpl_Double_Abs(x);

    /*  Small inputs, |x| < 0.5.                                              */
    if (abs_x < 0.5)
    {
        /*  For very small inputs return pi / 2.                              */
        if (abs_x < 6.938893903907228E-18)
            return tmpl_Double_Pi_By_Two;

        /*  Small inputs, |x| < 0.125, use the Maclaurin series.              */
        if (abs_x < 0.125)
            return tmpl_Double_Arccos_Maclaurin(x);

        /*  Otherwise use the Remez rational minimax function.                */
        return tmpl_Double_Arccos_Rat_Remez(x);
    }

    /*  For 0.5 <= |x| < 1 use the formula acos(x) = 2*asin(sqrt(1 - x) / 2). */
    if (abs_x < 1.0)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (x < 0.0)
            return tmpl_Double_Pi - tmpl_Double_Arccos_Tail_End(abs_x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_Double_Arccos_Tail_End(abs_x);
    }

    /*  Since cos(pi) = -1, we have acos(-1) = pi. Return pi.                 */
    if (x == -1.0)
        return tmpl_Double_Pi;

    /*  Similarly, since cos(0) = 1 we have acos(1) = 0. Use this.            */
    if (x == 1.0)
        return 0.0;

    /*  For |x| > 1 the function is undefined. Return NaN.                    */
    return TMPL_NAN;
}
/*  End of tmpl_Double_Arccos.                                                */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
