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
 *                             tmpl_arccos_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-cosine function at long double precision.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arccos                                                   *
 *  Purpose:                                                                  *
 *      Computes acos(x), the inverse cosine function.                        *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (long double):                                                 *
 *          The arc-cosine of x.                                              *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/auxiliary/                                               *
 *              tmpl_LDouble_Arccos_Maclaurin:                                *
 *                  Computes acos via a Maclaurin series for small x.         *
 *              tmpl_LDouble_Arccos_Rat_Remez:                                *
 *                  Computes acos via a minimax approximation for |x| < 0.5.  *
 *              tmpl_LDouble_Arccos_Tail_End:                                 *
 *                  Computes acos(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          The words "tiny" and "small" used below are dependent on how      *
 *          long double is implemented:                                       *
 *                                                                            *
 *              long double type           | tiny   | small                   *
 *              -------------------------------------------                   *
 *              64-bit double              | 2^-57  | 2^-3                    *
 *              80-bit extended / portable | 2^-65  | 2^-3                    *
 *              128-bit double-double      | 2^-105 | 2^-4                    *
 *              128-bit quaduple           | 2^-116 | 2^-4                    *
 *                                                                            *
 *          0 <= |x| < "tiny":                                                *
 *              return pi / 2. The error is O(x). This avoids unnecessary     *
 *              underflow in the computation.                                 *
 *          "tiny" <= |x| < "small":                                          *
 *              Use a Maclaurin series. This is of the form pi / 2 - p(x)     *
 *              where p(x) is an odd function. The degree N approximation     *
 *              needs only (N + 1) / 2 non-zero terms. The value for N varies *
 *              with how long double is implemented:                          *
 *                                                                            *
 *                  long double type           | N                            *
 *                  -------------------------------                           *
 *                  64-bit double              | 15                           *
 *                  80-bit extended / portable | 19                           *
 *                  128-bit double-double      | 25                           *
 *                  128-bit quadruple          | 27                           *
 *                                                                            *
 *          "small" <= |x| < 2^-1:                                            *
 *              Use a rational Remez approximation for the function:          *
 *                                                                            *
 *                  R(x) = -(acos(x) - pi/2 + x) / x^3                        *
 *                                                                            *
 *              This function is is even, so the degree (N, M) rational Remez *
 *              approximation requires N/2+1 non-zero terms in the numerator  *
 *              and M/2+1 non-zero terms in the denominator. acos(x) is       *
 *              computed via:                                                 *
 *                                                                            *
 *                  acos(x) = pi/2 - (x + x^3 * P(x) / Q(x))                  *
 *                                                                            *
 *              where P(x) is the numerator and Q(x) is the denominator for   *
 *              the rational Remez approximation of R(x), respectively.       *
 *              The values for N and M are given in the table below.          *
 *                                                                            *
 *                  long double type           | N  | M                       *
 *                  ------------------------------------                      *
 *                  64-bit double              | 8  | 8                       *
 *                  80-bit extended / portable | 10 | 10                      *
 *                  128-bit double-double      | 18 | 16                      *
 *                  128-bit quadruple          | 18 | 18                      *
 *                                                                            *
 *          2^-1 <= x < 1:                                                    *
 *              Compute using the reflection formula:                         *
 *                                                                            *
 *                  acos(x) = 2 * asin(sqrt((1 - x) / 2))                     *
 *                                                                            *
 *              Note that as x tends to 1, sqrt((1 - x) / 2) tends to zero.   *
 *              Since acos(1) = 0, using this trick allows us to maintain     *
 *              excellent relative error as the argument approaches 1.        *
 *                                                                            *
 *              asin(z) is computed using a rational Remez approximation for: *
 *                                                                            *
 *                  R(z) = (asin(z) - z) / z^3                                *
 *                                                                            *
 *              This function is even, meaning N/2 + 1 non-zero terms are     *
 *              required for the numerator, and M/2 + 1 for the denominator.  *
 *              asin(z) is computed via:                                      *
 *                                                                            *
 *                  asin(z) = z + z^3 * P(z) / Q(z)                           *
 *                                                                            *
 *              where P(z) is the numerator and Q(z) is the denominator of    *
 *              the rational Remez approximation of R(z), respectively. The   *
 *              value acos(x) is then computed by:                            *
 *                                                                            *
 *                  acos(x) = 2 * asin(z)                                     *
 *                                                                            *
 *              with z = sqrt((1 - x) / 2). The values for N and M are:       *
 *                                                                            *
 *                  long double type           | N  | M                       *
 *                  ------------------------------------                      *
 *                  64-bit double              | 8  | 8                       *
 *                  80-bit extended / portable | 10 | 10                      *
 *                  128-bit double-double      | 18 | 16                      *
 *                  128-bit quaduple           | 18 | 18                      *
 *                                                                            *
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
 *      Error (64-bit Double):                                                *
 *          Based on 788,968,857 samples with -1 < x < 1.                     *
 *              max relative error: 2.2204459059627917e-16                    *
 *              rms relative error: 8.3796804351081161e-17                    *
 *              max absolute error: 4.4408920985006262e-16                    *
 *              rms absolute error: 1.4737238548161158e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *      Error (80-bit Extended):                                              *
 *          Based on 394,484,428 samples with -1 < x < 1.                     *
 *              max relative error: 2.1646973539415815e-19                    *
 *              rms relative error: 4.0762969454067788e-20                    *
 *              max absolute error: 2.1684043449710089e-19                    *
 *              rms absolute error: 6.9155008767105195e-20                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-19).                                    *
 *      Error (128-bit Quadruple):                                            *
 *          Based on 10,000,000 samples with -1 < x < 1.                      *
 *              max relative error: 2.1493423806776799e-34                    *
 *              rms relative error: 7.1883692991558038e-35                    *
 *              max absolute error: 1.9259299443872359e-34                    *
 *              rms absolute error: 5.3481009953614647e-35                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-34).                                    *
 *      Error (128-bit Double-Double):                                        *
 *          Based on 10,000,000 samples with -1 < x < 1.                      *
 *              max relative error: 4.8287083179936863e-32                    *
 *              rms relative error: 5.8808472000117189e-33                    *
 *              max absolute error: 7.0874221953450279e-32                    *
 *              rms absolute error: 9.0797583993958255e-33                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~5 x 10^-32).                                    *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/                                                         *
 *              tmpl_LDouble_Abs:                                             *
 *                  Computes the absolute value of a real number.             *
 *          src/math/auxiliary/                                               *
 *              tmpl_LDouble_Arccos_Maclaurin:                                *
 *                  Computes acos via a Maclaurin series for small x.         *
 *              tmpl_LDouble_Arccos_Rat_Remez:                                *
 *                  Computes acos via a minimax approximation for |x| < 0.5.  *
 *              tmpl_LDouble_Arccos_Tail_End:                                 *
 *                  Computes acos(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          Similar to the IEEE-754 version, but determine the size of the    *
 *          input using the absolute value function and comparing the output  *
 *          to the numbers 0.5 and 1.0.                                       *
 *      Error:                                                                *
 *          Based on 394,484,428 samples with -1 < x < 1.                     *
 *              max relative error: 2.1646973539415815e-19                    *
 *              rms relative error: 4.0762969454067788e-20                    *
 *              max absolute error: 2.1684043449710089e-19                    *
 *              rms absolute error: 6.9155008767105195e-20                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-19).                                    *
 *  Notes:                                                                    *
 *      The only distinction between the IEEE-754 method and the portable one *
 *      is how the size of the input x is determined. The IEEE-754 method     *
 *      examines the exponent of the input, the portable method computes the  *
 *      absolute value and compares the size of x directly with the numbers   *
 *      0.5 and 1.0. The IEEE-754 method is hence slightly faster on most     *
 *      computers.                                                            *
 *                                                                            *
 *      Both methods detect if the input is NaN or infinity. The IEEE-754     *
 *      detects NaN and Inf since the exponents of NaN and Inf are large, and *
 *      the portable method detects NaN since NaN should always evaluate      *
 *      false when a comparison is made (==, <, >, etc.).                     *
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
 *  2.) tmpl_nan_ldouble.h:                                                   *
 *          Header file providing long double precision NaN (Not-a-Number).   *
 *  3.) tmpl_math_constants.h:                                                *
 *          Header file providing pi and pi / 2.                              *
 *  4.) tmpl_ieee754_ldouble.h:                                               *
 *          Header file where the tmpl_IEEE754_LDouble type is defined.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 03, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/13: Ryan Maguire                                                  *
 *      Added comments, algorithm description, and fixed error values.        *
 *  2023/05/31: Ryan Maguire                                                  *
 *      Added optimizations for small x and denormal values.                  *
 *  2024/10/28: Ryan Maguire                                                  *
 *      Replacing use of const variables with macros for multiples of pi.     *
 *  2025/04/05: Ryan Maguire                                                  *
 *      Removed tmpl_math.h as a dependency. A forward declaration is now     *
 *      provided for the function in this file and NAN is included directly.  *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Forward declaration for the function, also found in tmpl_math.h.          */
extern long double tmpl_LDouble_Arccos(const long double x);

/*  Mathematical constants like pi and pi / 2 are found here.                 */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  TMPL_NANL macro found here which provides long double precision NaN.      */
#include <libtmpl/include/nan/tmpl_nan_ldouble.h>

/*  TMPL_HAS_IEEE754_LDOUBLE macro and tmpl_IEEE754_LDouble type given here.  */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Maclaurin expansion provided here.                                        */
#include "auxiliary/tmpl_arccos_maclaurin_ldouble.h"

/*  Rational Remez minimax approximation for arccos.                          */
#include "auxiliary/tmpl_arccos_rat_remez_ldouble.h"

/*  Tail-end arccos function that uses the reflection formula with arcsin.    */
#include "auxiliary/tmpl_arccos_tail_end_ldouble.h"

/******************************************************************************
 *                              Constant Values                               *
 ******************************************************************************/

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  The trade off from very tiny to very small to small depends on how long   *
 *  double is implemented. Save these values as macros.                       */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  acos(x) = pi / 2 to double precision for |x| < 2^-57.                     */
#define TMPL_ARCCOS_TINY_EXPONENT (TMPL_LDOUBLE_UBIAS - 57U)

/*  For 64-bit double the Maclaurin series is accurate to double precision    *
 *  for |x| < 0.15 meaning we can safely use this for |x| < 2^-3.             */
#define TMPL_ARCCOS_SMALL_EXPONENT (TMPL_LDOUBLE_UBIAS - 3U)

/*  128-bit double-double uses much smaller exponents.                        */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  For |x| < 2^-105 acos(x) = pi / 2 to double-double precision.             */
#define TMPL_ARCCOS_TINY_EXPONENT (TMPL_LDOUBLE_UBIAS - 105U)

/*  The Maclaurin series is accurate to double-double precision for |x|       *
 *  bounded by 2^-4.                                                          */
#define TMPL_ARCCOS_SMALL_EXPONENT (TMPL_LDOUBLE_UBIAS - 4U)

/*  128-bit quadruple requires even smaller exponents.                        */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/*  For |x| < 2^-116 acos(x) = pi / 2 to quadruple precision.                 */
#define TMPL_ARCCOS_TINY_EXPONENT (TMPL_LDOUBLE_UBIAS - 116U)

/*  The Maclaurin series is accurate to quadruple precision for |x| < 0.1 so  *
 *  it is safe to use for |x| < 2^-4.                                         */
#define TMPL_ARCCOS_SMALL_EXPONENT (TMPL_LDOUBLE_UBIAS - 4U)

/*  Lastly, extended precision. 15-bit exponent and 64 bit mantissa.          */
#else

/*  For |x| < 2^-65 acos(x) = pi / 2 to extended precision.                   */
#define TMPL_ARCCOS_TINY_EXPONENT (TMPL_LDOUBLE_UBIAS - 65U)

/*  The Maclaurin series is accurate to extended precision for |x| < 0.17.    *
 *  The function is thus safe to use for |x| < 2^-3.                          */
#define TMPL_ARCCOS_SMALL_EXPONENT (TMPL_LDOUBLE_UBIAS - 3U)

#endif
/*  End of double vs. extended vs. double-double vs. quadruple.               */

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  On most computers it is faster to check the value of the exponent of a    *
 *  long double rather than checking the entire input. This gives the         *
 *  IEEE-754 method a slight performance boost over the portable one below.   */

/*  Long double precision inverse cosine (acosl equivalent).                  */
long double tmpl_LDouble_Arccos(const long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  Small inputs, |x| < 0.5.                                              */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 1U)
    {
        /*  For very small x, acos(x) = pi / 2 to long double precision.      */
        if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_ARCCOS_TINY_EXPONENT)
            return tmpl_LDouble_Pi_By_Two;

        /*  For small x the Maclaurin series is sufficient.                   */
        if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_ARCCOS_SMALL_EXPONENT)
            return tmpl_LDouble_Arccos_Maclaurin(x);

        /*  For all other x with |x| < 0.5 use the minimax approximation.     */
        return tmpl_LDouble_Arccos_Rat_Remez(x);
    }

    /*  For |x| < 1 use the tail end formula acos(x) = 2asin(sqrt(1-x)/2).    */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (TMPL_LDOUBLE_IS_NEGATIVE(w))
            return tmpl_ldouble_pi - tmpl_LDouble_Arccos_Tail_End(-x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_LDouble_Arccos_Tail_End(x);
    }

    /*  Since cos(pi) = -1, we have acos(-1) = pi. Return pi.                 */
    if (x == -1.0L)
        return tmpl_ldouble_pi;

    /*  Similarly, since cos(0) = 1 we have acos(1) = 0. Use this.            */
    if (x == 1.0L)
        return 0.0L;

    /*  For a real input, acos(x) is undefined with |x| > 1. Return NaN. Note *
     *  this catches NaN and infinity since we are checking the exponent of   *
     *  the input, not the input. For x = NaN or Inf, the exponent is greater *
     *  than TMPL_LDOUBLE_UBIAS, so NaN will return.                          */
    return TMPL_NANL;
}
/*  End of tmpl_LDouble_Arccos.                                               */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_ARCCOS_TINY_EXPONENT
#undef TMPL_ARCCOS_SMALL_EXPONENT

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  The approximation used (Maclaurin, Remez, or reflection formula) depends  *
 *  on the size of the input. We compute this via the absolute value function.*/
#if TMPL_USE_INLINE == 1

/*  The absolute value function is small and should be inlined.               */
#include <libtmpl/include/inline/math/tmpl_abs_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern long double tmpl_LDouble_Abs(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Long double precision inverse cosine (acosl equivalent).                  */
long double tmpl_LDouble_Arccos(const long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const long double abs_x = tmpl_LDouble_Abs(x);

    /*  Small inputs, |x| < 0.5.                                              */
    if (abs_x < 0.5L)
    {
        /*  For very small inputs return pi / 2.                              */
        if (abs_x < 2.710505431213760E-20L)
            return tmpl_LDouble_Pi_By_Two;

        /*  Small inputs, |x| < 0.125, use the Maclaurin series.              */
        if (abs_x < 0.125L)
            return tmpl_LDouble_Arccos_Maclaurin(x);

        /*  Otherwise use the Remez rational minimax function.                */
        return tmpl_LDouble_Arccos_Rat_Remez(x);
    }

    /*  For 0.5 <= |x| < 1 use the formula acos(x) = 2*asin(sqrt(1 - x) / 2). */
    if (abs_x < 1.0L)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (x < 0.0L)
            return tmpl_ldouble_pi - tmpl_LDouble_Arccos_Tail_End(abs_x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_LDouble_Arccos_Tail_End(abs_x);
    }

    /*  Since cos(pi) = -1, we have acos(-1) = pi. Return pi.                 */
    if (x == -1.0L)
        return tmpl_ldouble_pi;

    /*  Similarly, since cos(0) = 1 we have acos(1) = 0. Use this.            */
    if (x == 1.0L)
        return 0.0L;

    /*  For |x| > 1 the function is undefined. Return NaN.                    */
    return TMPL_NANL;
}
/*  End of tmpl_LDouble_Arccos.                                               */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

/*  Undefine everything in case someone wants to #include this file.          */
#include "auxiliary/tmpl_math_undef.h"

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
