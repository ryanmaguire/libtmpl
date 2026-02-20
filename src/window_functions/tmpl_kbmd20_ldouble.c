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
 *                             tmpl_kbmd20_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window with alpha = 2.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_KBMD20                                                   *
 *  Purpose:                                                                  *
 *      Computes the Kaiser-Bessel window with alpha = 2. This is defined in  *
 *      terms of the zeroth modified Bessel function, I_0:                    *
 *                                                                            *
 *                              -             ___________ -                   *
 *                             |             /    -   - 2  |                  *
 *                             |            /    | 2 x |   |                  *
 *                          I  | 2 pi \    / 1 - | --- |   | - 1              *
 *                           0 |       \  /      |  w  |   |                  *
 *                             |        \/        -   -    |                  *
 *                              -                         -                   *
 *          KBMD20(x, w) =  ------------------------------------              *
 *                                         -    -                             *
 *                                        |      |                            *
 *                                     I  | 2 pi | - 1                        *
 *                                      0 |      |                            *
 *                                         -    -                             *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number, the input data value.                              *
 *      width (const long double):                                            *
 *          The width of the window. Units are the same as x.                 *
 *  Output:                                                                   *
 *      kbmd20_xw (long double):                                              *
 *          The modified Kaiser-Bessel window evaluated at x / width.         *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/                                                         *
 *              tmpl_LDouble_Abs:                                             *
 *                  Computes the absolute value of a real number.             *
 *          src/window_functions/auxiliary/                                   *
 *              tmpl_LDouble_KBMD20_Remez:                                    *
 *                  Computes KBMD20(x) using a Remez polynomial.              *
 *              tmpl_LDouble_KBMD20_Rat_Remez:                                *
 *                  Computes KBMD20(x) using a rational Remez approximation.  *
 *              tmpl_LDouble_KBMD20_Tail_End:                                 *
 *                  Computes KBMD20(x) using a Remez expansion in x - 1 / 2.  *
 *      Method:                                                               *
 *          Set x = x / width, then do the following.                         *
 *          x is NaN:                                                         *
 *              Return NaN.                                                   *
 *          |x| < 2^-deg:                                                     *
 *              Return 1. Error is O(x^2), accurate to long double precision. *
 *              deg depends on how long double is implemented:                *
 *                                                                            *
 *                  Implementation        | deg                               *
 *                  ---------------------------                               *
 *                  64-bit double         |  30                               *
 *                  80-bit extended       |  34                               *
 *                  128-bit double-double |  56                               *
 *                  128-bit quadruple     |  69                               *
 *                                                                            *
 *          |x| < 2^-5:                                                       *
 *              Use a degree N Remez polynomial for:                          *
 *                                                                            *
 *                         KBMD20(x) - 1                                      *
 *                  f(x) = -------------                                      *
 *                                2                                           *
 *                               x                                            *
 *                                                                            *
 *              Return 1 + x^2 P(x) where P is the degree N Remez polynomial  *
 *              for f. Note, since f is even, only (N / 2)+1 of the terms in  *
 *              P are  non-zero. The value for N is given below.              *
 *                                                                            *
 *                  Implementation        | Degree                            *
 *                  ------------------------------                            *
 *                  64-bit double         |      8                            *
 *                  80-bit extended       |     10                            *
 *                  128-bit double-double |     16                            *
 *                  128-bit quadruple     |     16                            *
 *                                                                            *
 *          |x| < 2^-2:                                                       *
 *              Use a degree (N, M) rational Remez approximation. Since the   *
 *              window is even, there are only (N/2)+1 non-zero terms in the  *
 *              numerator and (M/2)+1 non-zero terms in the denominator. N    *
 *              and M are given by:                                           *
 *                                                                            *
 *                  Implementation        | Numerator | Denominator           *
 *                  -----------------------------------------------           *
 *                  64-bit double         |        10 |           8           *
 *                  80-bit extended       |        10 |          10           *
 *                  128-bit double-double |        16 |          14           *
 *                  128-bit quadruple     |        16 |          16           *
 *                                                                            *
 *          2^-2 <= x < 2^-1:                                                 *
 *              Use a rational Remez approximation in terms of x - 1 / 2 for  *
 *              the function:                                                 *
 *                                                                            *
 *                         KBMD20(x + 1 / 2)                                  *
 *                  g(x) = -----------------                                  *
 *                                 x                                          *
 *                                                                            *
 *              We shift the argument x using:                                *
 *                                                                            *
 *                                                                            *
 *                             1                                              *
 *                  t(x) = x - -                                              *
 *                             2                                              *
 *                                                                            *
 *              and then return t(x) * P(t(x)) / Q(t(x)), where P and Q are   *
 *              the numerator and denominator, respectively, for the degree   *
 *              (N, M) rational Remez approximation for g on the interval     *
 *              [-1/4, 0]. Since t(x) tends to zero as x approaches 1 / 2,    *
 *              this method ensures the endpoints of the window are zero.     *
 *              N and M are given by:                                         *
 *                                                                            *
 *                  Implementation        | Numerator | Denominator           *
 *                  -----------------------------------------------           *
 *                  64-bit double         |         8 |           6           *
 *                  80-bit extended       |         8 |           8           *
 *                  128-bit double-double |        12 |          12           *
 *                  128-bit quadruple     |        14 |          12           *
 *                                                                            *
 *          -2^-1 < x <= -2^-2:                                               *
 *              Compute |x| by setting the sign bit of x to zero, and then    *
 *              use the previous case since 2^-2 <= |x| < 2^-1.               *
 *          |x| >= 2^-1 (including + / - infinity):                           *
 *              Return 0.                                                     *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/                                                         *
 *              tmpl_LDouble_Abs:                                             *
 *                  Computes the absolute value of a real number.             *
 *              tmpl_LDouble_Is_NaN:                                          *
 *                  Determines if a long double is Not-a-Number.              *
 *          src/window_functions/auxiliary/                                   *
 *              tmpl_LDouble_KBMD20_Remez:                                    *
 *                  Computes KBMD20(x) using a Remez polynomial.              *
 *              tmpl_LDouble_KBMD20_Rat_Remez:                                *
 *                  Computes KBMD20(x) using a rational Remez approximation.  *
 *              tmpl_LDouble_KBMD20_Tail_End:                                 *
 *                  Computes KBMD20(x) using a Remez expansion in x - 1 / 2.  *
 *      Method:                                                               *
 *          Same as the IEEE-754 method but check for NaN using the Is_NaN    *
 *          function, and compute the absolute value using the Abs function.  *
 *  Error:                                                                    *
 *          Based on 100,000 samples with -1/2 < x < 1/2 and w = 1            *
 *              max relative error: 2.4161819325413287E-19                    *
 *              rms relative error: 5.1212833655092076E-20                    *
 *              max absolute error: 1.2567243193193376E-19                    *
 *              rms absolute error: 2.6449198885812206E-20                    *
 *          Values were computed using the Python library mpmath with 224     *
 *          bits of precision (1 ULP ~= 10^-68) and assume 80-bit extended    *
 *          precision long double. Similar error values (1-2 ULP) are found   *
 *          for double, double-double, and quadruple precisions.              *
 *  Notes:                                                                    *
 *      1.) Accurate to long double precision.                                *
 *                                                                            *
 *      2.) There are no checks for negative window widths, or zero widths.   *
 *          Negative window widths have no effect since the window function   *
 *          is even, and hence KBMD20(x / w) = KBMD20(x / -w). Zero windows   *
 *          produce division-by-zero, and may result in an output that is     *
 *          either NaN (if x = 0) or 0 (if |x| > 0 and |x| / 0 is treated as  *
 *          infinity).                                                        *
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
 *      3.) Marouf, E., Tyler, G., Rosen, P. (June 1986)                      *
 *          Profiling Saturn's Rings by Radio Occultation                     *
 *          Icarus Vol. 68, Pages 120-166.                                    *
 *                                                                            *
 *          A description of the (normal) Kaiser-Bessel window is provided    *
 *          here, and how it is used in Fourier optics.                       *
 *                                                                            *
 *      4.) Kaiser, James, Schafer, Ronald (1980)                             *
 *          On the Use of the I0-Sinh Window for Spectrum Analysis            *
 *          IEEE Transactions on Acoustics, Speech, and Signal Processing     *
 *          Vol 28, Pages 105-107                                             *
 *                                                                            *
 *          The original paper describing the (normal) Kaiser window.         *
 *          The original window tends to 1 / I0(alpha * pi) at the endpoints, *
 *          which is not zero. The modification here makes the endpoints tend *
 *          to zero, exactly, at the endpoints.                               *
 *                                                                            *
 *      5.) https://en.wikipedia.org/wiki/Kaiser_window                       *
 *                                                                            *
 *          Wikipedia article discussing the (normal) Kaiser window.          *
 *                                                                            *
 *      6.) https://en.wikipedia.org/wiki/Window_function                     *
 *                                                                            *
 *          Wikipedia article discussing tapers in general.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_nan_ldouble.h:                                                   *
 *          Header file providing long double precision NaN (Not-a-Number).   *
 *  2.) tmpl_ieee754_ldouble.h:                                               *
 *          Header file where the tmpl_IEEE754_LDouble type is defined.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 27, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/05: Ryan Maguire                                                  *
 *      Changed algorithm from Taylor series to Pade approximant.             *
 *  2023/01/06: Ryan Maguire                                                  *
 *      Added license and comments.                                           *
 *  2026/02/19: Ryan Maguire                                                  *
 *      Swapped Pade approximants for Remez polynomials and rational minimax  *
 *      approximations, ensuring the function tends to zero at the endpoints, *
 *      and improving the performance.                                        *
 ******************************************************************************/

/*  Function prototype / forward declaration.                                 */
extern long double
tmpl_LDouble_KBMD20(const long double x, const long double width);

/*  TMPL_NAN macro found here which provides long double precision NaN.       */
#include <libtmpl/include/nan/tmpl_nan_ldouble.h>

/*  TMPL_HAS_IEEE754_LDOUBLE macro and tmpl_IEEE754_LDouble type given here.  */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  Check for inline support.                                                 */
#if TMPL_USE_INLINE == 1

/*  The absolute value function is small and should be inlined.               */
#include <libtmpl/include/inline/math/tmpl_abs_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern long double tmpl_LDouble_Abs(const long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Remez polynomial for the modified Kaiser-Bessel window.                   */
#include "auxiliary/tmpl_kbmd20_remez_ldouble.h"

/*  Rational Remez approximation for the modified Kaiser-Bessel window.       */
#include "auxiliary/tmpl_kbmd20_rat_remez_ldouble.h"

/*  Tail-end expansion using a shifted rational Remez approximation.          */
#include "auxiliary/tmpl_kbmd20_tail_end_ldouble.h"

/*  With IEEE-754 support we can check if the input falls within the window   *
 *  more efficiently. This gives a slight performance boost.                  */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  The threshold for small values depends on how long double is represented. */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  52-bit mantissa, threshold for small values is 2^-30.                     */
#define TMPL_SMALL_THRESHOLD (TMPL_LDOUBLE_UBIAS - 0x1EU)

/*  128-bit double-double needs a much smaller threshold.                     */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  104-bit mantissa, threshold for small values is 2^-56.                    */
#define TMPL_SMALL_THRESHOLD (TMPL_LDOUBLE_UBIAS - 0x38U)

/*  128-bit quadruple, slightly smaller threshold than double-double.         */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/*  112-bit mantissa, threshold for small values is 2^-60.                    */
#define TMPL_SMALL_THRESHOLD (TMPL_LDOUBLE_UBIAS - 0x3CU)

/*  80-bit extended needs a slightly smaller threshold than 64-bit double.    */
#else

/*  63-bit mantissa, threshold for small values is 2^-34.                     */
#define TMPL_SMALL_THRESHOLD (TMPL_LDOUBLE_UBIAS - 0x22U)

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

/*  Long double precision Kaiser-Bessel window with alpha = 2.                */
long double tmpl_LDouble_KBMD20(const long double x, const long double width)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;

    /*  The interval [-w/2, w/2] is compressed to [-1/2, 1/2] by computing    *
     *  the ratio of the inputs. This is the main argument for the window.    */
    w.r = x / width;

    /*  If |x| < 1 / 4, use one of the Remez approximations.                  */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 0x02U)
    {
        /*  Avoid underflow, check for small inputs, |x| < 1 / 32.            */
        if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 0x05U)
        {
            /*  For very small inputs, return 1. The error is O(x^2), the     *
             *  value of the window is 1 to long double precision.            */
            if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_SMALL_THRESHOLD)
                return 1.0L;

            /*  Otherwise, use a Remez polynomial with a few terms.           */
            return tmpl_LDouble_KBMD20_Remez(w.r);
        }

        /*  For 1 / 32 <= |x| < 1 / 4, use a rational Remez approximation.    */
        return tmpl_LDouble_KBMD20_Rat_Remez(w.r);
    }

    /*  For arguments on the tail-end of the window, we use an expansion in   *
     *  terms of x - 1 / 2. This helps ensure the window goes to zero at the  *
     *  endpoints.                                                            */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 0x01U)
    {
        /*  The tail-end function assumes 1 / 4 <= x <= 1 / 2. Since the      *
         *  window function is symmetric, we can handle negative values by    *
         *  using the absolute value. Set the sign bit to zero.               */
        w.r = tmpl_LDouble_Abs(w.r);

        /*  Compute using a rational Remez approximation that is expanded in  *
         *  terms of x - 1 / 2.                                               */
        return tmpl_LDouble_KBMD20_Tail_End(w.r);
    }

    /*  Special case, if the input is NaN, then the output is too.            */
    if (TMPL_LDOUBLE_IS_NAN(w))
        return w.r;

    /*  All other values (including + / - infinity) fall outside of the       *
     *  domain of the window. Return zero.                                    */
    return 0.0L;
}
/*  End of tmpl_LDouble_KBMD20.                                               */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_SMALL_THRESHOLD

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Long double precision Kaiser-Bessel window with alpha = 2.                */
long double tmpl_LDouble_KBMD20(const long double x, const long double width)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double abs_arg;

    /*  The interval [-w/2, w/2] is compressed to [-1/2, 1/2] by computing    *
     *  the ratio of the inputs. This is the main argument for the window.    */
    const long double arg = x / width;

    /*  Special case, if the argument is NaN, return NaN.                     */
    if (tmpl_LDouble_Is_NaN(arg))
        return arg;

    /*  The window function is even, compute the absolute value and use that. */
    abs_arg = tmpl_LDouble_Abs(arg);

    /*  If |x| < 1 / 4, use one of the Remez approximations.                  */
    if (abs_arg < 0.25L)
    {
        /*  Avoid underflow, check for small inputs, |x| < 1 / 32.            */
        if (abs_arg < 0.03125L)
        {
            /*  For very small inputs, |x| < 2^-30, return 1. The error is    *
             *  O(x^2), the value of the window is 1 to double precision.     */
            if (abs_arg < 5.82076609134674072265625E-11L)
                return 1.0L;

            /*  Otherwise, use a Remez polynomial with a few terms.           */
            return tmpl_LDouble_KBMD20_Remez(abs_arg);
        }

        /*  For 1 / 32 <= |x| < 1 / 4, use a rational Remez approximation.    */
        return tmpl_LDouble_KBMD20_Rat_Remez(abs_arg);
    }

    /*  For arguments on the tail-end of the window, we use an expansion in   *
     *  terms of x - 1 / 2. This helps ensure the window goes to zero at the  *
     *  endpoints.                                                            */
    if (abs_arg < 0.5L)
        return tmpl_LDouble_KBMD20_Tail_End(abs_arg);

    /*  All other values (including + / - infinity) fall outside of the       *
     *  domain of the window. Return zero.                                    */
    return 0.0L;
}
/*  End of tmpl_LDouble_KBMD20.                                               */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
