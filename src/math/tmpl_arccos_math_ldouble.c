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
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (long double):                                                 *
 *          The arc-cosine of x.                                              *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_LDouble_Arccos_Maclaurin:                                *
 *                  Computes acos via a Maclaurin series for small x.         *
 *              tmpl_LDouble_Arccos_Rat_Remez:                                *
 *                  Computes acos via a minimax approximation for |x| < 0.5.  *
 *              tmpl_LDouble_Arccos_Tail_End:                                 *
 *                  Computes acos(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          For tiny x return pi / 2. For small x use a Maclaurin series.     *
 *          For |x| < 0.5 use a minimax approximation.                        *
 *          For 0.5 <= x < 1 use the reflection formula:                      *
 *                                                                            *
 *              acos(x) = 2*asin(sqrt((1-x)/2))                               *
 *                                                                            *
 *          Compute this using a minimax approximation. For values            *
 *          -1 < x <= -0.5 use the negation formula:                          *
 *                                                                            *
 *              acos(x) = pi - acos(-x)                                       *
 *                                                                            *
 *          Use this and compute acos(-x) via the tail-end function.          *
 *          For |x| > 1 return NaN, and lastly the special cases of x = +/- 1 *
 *          return acos(-1) = pi and acos(1) = 0.                             *
 *                                                                            *
 *          "Tiny" and "small" depends on how long double is implemented.     *
 *              64-bit double:                                                *
 *                  Tiny:   |x| < 2^-57                                       *
 *                  Small:  |x| < 2^-3                                        *
 *              128-bit double-double:                                        *
 *                  Tiny:   |x| < 2^-105                                      *
 *                  Small:  |x| < 2^-4                                        *
 *              128-bit quadruple:                                            *
 *                  Tiny:   |x| < 2^-116                                      *
 *                  Small:  |x| < 2^-4                                        *
 *              80-bit extended / portable:                                   *
 *                  Tiny:   |x| < 2^-65                                       *
 *                  Small:  |x| < 2^-3                                        *
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
 *          tmpl_math.h:                                                      *
 *              tmpl_LDouble_Abs:                                             *
 *                  Computes the absolute value of a real number.             *
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
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
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
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

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

/*  The limit at zero is pi / 2, and the negation formula needs pi as well.   */
#define TMPL_ONE_PI (+3.14159265358979323846264338327950288419716939937511E+00L)
#define TMPL_PI_BY_TWO (+1.57079632679489661923132169163975144209858469969E+00L)

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
long double tmpl_LDouble_Arccos(long double x)
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
            return TMPL_PI_BY_TWO;

        /*  For small x the Maclaurin series is sufficient.                   */
        else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_ARCCOS_SMALL_EXPONENT)
            return tmpl_LDouble_Arccos_Maclaurin(x);

        /*  For all other x with |x| < 0.5 use the minimax approximation.     */
        return tmpl_LDouble_Arccos_Rat_Remez(x);
    }

    /*  For |x| < 1 use the tail end formula acos(x) = 2asin(sqrt(1-x)/2).    */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (TMPL_LDOUBLE_IS_NEGATIVE(w))
            return TMPL_ONE_PI - tmpl_LDouble_Arccos_Tail_End(-x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_LDouble_Arccos_Tail_End(x);
    }

    /*  acos(-1) = pi and acos(1) = 0. Use this.                              */
    if (x == -1.0L)
        return TMPL_ONE_PI;
    else if (x == 1.0L)
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

/*  Long double precision inverse cosine (acosl equivalent).                  */
long double tmpl_LDouble_Arccos(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const long double abs_x = tmpl_LDouble_Abs(x);

    /*  Small inputs, |x| < 0.5.                                              */
    if (abs_x < 0.5L)
    {
        /*  For very small inputs return pi / 2.                              */
        if (abs_x < 2.710505431213760E-20L)
            return TMPL_PI_BY_TWO;

        /*  Small inputs, |x| < 0.125, use the Maclaurin series.              */
        else if (abs_x < 0.125L)
            return tmpl_LDouble_Arccos_Maclaurin(x);

        /*  Otherwise use the Remez rational minimax function.                */
        return tmpl_LDouble_Arccos_Rat_Remez(x);
    }

    /*  For |x| < 1 use the tail end formula acos(x) = 2asin(sqrt(1-x)/2).    */
    else if (abs_x < 1.0L)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (x < 0.0L)
            return TMPL_ONE_PI - tmpl_LDouble_Arccos_Tail_End(abs_x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_LDouble_Arccos_Tail_End(abs_x);
    }

    /*  acos(-1) = pi and acos(1) = 0. Use this.                              */
    if (x == -1.0L)
        return TMPL_ONE_PI;
    else if (x == 1.0L)
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
