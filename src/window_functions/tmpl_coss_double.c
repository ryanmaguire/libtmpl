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
 *                              tmpl_coss_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the squared cosine window.                                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Coss                                                      *
 *  Purpose:                                                                  *
 *      Computes the squared cosine window:                                   *
 *                                                                            *
 *                            -     -  2                                      *
 *                           |    x  |                                        *
 *          coss(x, w) = cos | pi -  |                                        *
 *                           |    w  |                                        *
 *                            -     -                                         *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number, the input data value.                              *
 *      width (const double):                                                 *
 *          The width of the window. Units are the same as x.                 *
 *  Output:                                                                   *
 *      coss_xw (double):                                                     *
 *          The squared cosine window evaluated at x / width.                 *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          src/window_functions/auxiliary/                                   *
 *              tmpl_Double_Coss_Remez:                                       *
 *                  Computes Coss(x) using a Remez polynomial.                *
 *              tmpl_Double_Coss_Rat_Remez:                                   *
 *                  Computes Coss(x) using a rational Remez approximation.    *
 *              tmpl_Double_Coss_Tail_End:                                    *
 *                  Computes Coss(x) using a Remez expansion in x - 1 / 2.    *
 *      Method:                                                               *
 *          Set x = x / width, then do the following.                         *
 *          x is NaN:                                                         *
 *              Return NaN.                                                   *
 *          |x| < 2^-30:                                                      *
 *              Return 1. Error is O(x^2), accurate to double precision.      *
 *          |x| < 2^-5:                                                       *
 *              Use a degree 8 Remez polynomial for:                          *
 *                                                                            *
 *                         Coss(x) - 1                                        *
 *                  f(x) = -----------                                        *
 *                              2                                             *
 *                             x                                              *
 *                                                                            *
 *              Return 1 + x^2 P(x) where P is the degree 8 Remez polynomial  *
 *              for f. Note, since f is even, only 5 of the terms in P are    *
 *              non-zero.                                                     *
 *          |x| < 2^-2:                                                       *
 *              Use a degree (8, 8) rational Remez approximation. Since the   *
 *              window is even, there are only 5 non-zero terms in the        *
 *              numerator and 5 non-zero terms in the denominator.            *
 *          2^-2 <= x < 2^-1:                                                 *
 *              Use a rational Remez approximation in terms of x - 1 / 2 for  *
 *              the function:                                                 *
 *                                                                            *
 *                         Coss(x + 1 / 2)                                    *
 *                  g(x) = ---------------                                    *
 *                                2                                           *
 *                               x                                            *
 *                                                                            *
 *              We shift the argument x using:                                *
 *                                                                            *
 *                                                                            *
 *                             1                                              *
 *                  t(x) = x - -                                              *
 *                             2                                              *
 *                                                                            *
 *              and then return t(x)^2 * P(t(x)) / Q(t(x)), where P and Q are *
 *              the numerator and denominator, respectively, for the degree   *
 *              (6, 6) rational Remez approximation for g on the interval     *
 *              [-1/4, 0]. Since t(x) tends to zero as x approaches 1 / 2,    *
 *              this method ensures the endpoints of the window are zero.     *
 *          -2^-1 < x <= -2^-2:                                               *
 *              Compute |x| by setting the sign bit of x to zero, and then    *
 *              use the previous case since 2^-2 <= |x| < 2^-1.               *
 *          |x| >= 2^-1 (including + / - infinity):                           *
 *              Return 0.                                                     *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/                                                         *
 *              tmpl_Double_Abs:                                              *
 *                  Computes the absolute value of a real number.             *
 *              tmpl_Double_Is_NaN:                                           *
 *                  Determines if a double is Not-a-Number.                   *
 *          src/window_functions/auxiliary/                                   *
 *              tmpl_Double_Coss_Remez:                                       *
 *                  Computes Coss(x) using a Remez polynomial.                *
 *              tmpl_Double_Coss_Rat_Remez:                                   *
 *                  Computes Coss(x) using a rational Remez approximation.    *
 *              tmpl_Double_Coss_Tail_End:                                    *
 *                  Computes Coss(x) using a Remez expansion in x - 1 / 2.    *
 *      Method:                                                               *
 *          Same as the IEEE-754 method but check for NaN using the Is_NaN    *
 *          function, and compute the absolute value using the Abs function.  *
 *  Error:                                                                    *
 *      Based on 100,000 samples with -1/2 < x < 1/2 and w = 1                *
 *          max relative error: 4.4768082656804111E-16                        *
 *          rms relative error: 1.2047284579047005E-16                        *
 *          max absolute error: 2.2204460492503130E-16                        *
 *          rms absolute error: 5.8481680453745493E-17                        *
 *      Values were computed using the Python library mpmath with 224         *
 *      bits of precision (1 ULP ~= 10^-68).                                  *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision.                                     *
 *                                                                            *
 *      2.) There are no checks for negative window widths, or zero widths.   *
 *          Negative window widths have no effect since the window function   *
 *          is even, and hence Coss(x / w) = Coss(x / -w). Zero windows       *
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
 *          A description of the squared cosine window is provided            *
 *          here, and how it is used in Fourier optics.                       *
 *                                                                            *
 *      4.) https://en.wikipedia.org/wiki/Window_function                     *
 *                                                                            *
 *          Wikipedia article discussing tapers in general.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_ieee754_double.h:                                                *
 *          Header file where the tmpl_IEEE754_Double type is defined.        *
 *  2.) tmpl_math.h:                                                          *
 *          Contains abs and isnan function (used in portable version only).  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 19, 2020                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/04/07: Ryan Maguire                                                  *
 *      Changed algorithm to use Remez polynomials and rational minimax       *
 *      functions, and ensure the function goes to zero at the endpoints.     *
 ******************************************************************************/

/*  Function prototype / forward declaration.                                 */
extern double tmpl_Double_Coss(const double x, const double width);

/*  TMPL_HAS_IEEE754_DOUBLE macro and tmpl_IEEE754_Double type given here.    */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Remez polynomial for the squared cosine window.                           */
#include "auxiliary/tmpl_coss_remez_double.h"

/*  Rational Remez approximation for the squared cosine window.               */
#include "auxiliary/tmpl_coss_rat_remez_double.h"

/*  Tail-end expansion using a shifted rational Remez approximation.          */
#include "auxiliary/tmpl_coss_tail_end_double.h"

/*  With IEEE-754 support we can check if the input falls within the window   *
 *  more efficiently. This gives a slight performance boost.                  */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Double precision squared cosine window.                                   */
double tmpl_Double_Coss(const double x, const double width)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;

    /*  The interval [-w/2, w/2] is compressed to [-1/2, 1/2] by computing    *
     *  the ratio of the inputs. This is the main argument for the window.    */
    w.r = x / width;

    /*  If |x| < 1 / 4, use one of the Remez approximations.                  */
    if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 0x02U)
    {
        /*  Avoid underflow, check for small inputs, |x| < 1 / 32.            */
        if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 0x05U)
        {
            /*  For very small inputs, |x| < 2^-30, return 1. The error is    *
             *  O(x^2), the value of the window is 1 to double precision.     */
            if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 0x1EU)
                return 1.0;

            /*  Otherwise, use a Remez polynomial with a few terms.           */
            return tmpl_Double_Coss_Remez(w.r);
        }

        /*  For 1 / 32 <= |x| < 1 / 4, use a rational Remez approximation.    */
        return tmpl_Double_Coss_Rat_Remez(w.r);
    }

    /*  For arguments on the tail-end of the window, we use an expansion in   *
     *  terms of x - 1 / 2. This helps ensure the window goes to zero at the  *
     *  endpoints.                                                            */
    if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 0x01U)
    {
        /*  The tail-end function assumes 1 / 4 <= x <= 1 / 2. Since the      *
         *  window function is symmetric, we can handle negative values by    *
         *  using the absolute value. Set the sign bit to zero.               */
        w.bits.sign = 0x00U;

        /*  Compute using a rational Remez approximation that is expanded in  *
         *  terms of x - 1 / 2.                                               */
        return tmpl_Double_Coss_Tail_End(w.r);
    }

    /*  Special case, if the input is NaN, then the output is too.            */
    if (TMPL_DOUBLE_IS_NAN(w))
        return w.r;

    /*  All other values (including + / - infinity) fall outside of the       *
     *  domain of the window. Return zero.                                    */
    return 0.0;
}
/*  End of tmpl_Double_Coss.                                                  */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  tmpl_Double_Abs and tmpl_Double_Is_NaN declared here.                     */
#include <libtmpl/include/tmpl_math.h>

/*  Double precision squared cosine window.                                   */
double tmpl_Double_Coss(const double x, const double width)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double abs_arg;

    /*  The interval [-w/2, w/2] is compressed to [-1/2, 1/2] by computing    *
     *  the ratio of the inputs. This is the main argument for the window.    */
    const double arg = x / width;

    /*  Special case, if the argument is NaN, return NaN.                     */
    if (tmpl_Double_Is_NaN(arg))
        return arg;

    /*  The window function is even, compute the absolute value and use that. */
    abs_arg = tmpl_Double_Abs(arg);

    /*  If |x| < 1 / 4, use one of the Remez approximations.                  */
    if (abs_arg < 0.25)
    {
        /*  Avoid underflow, check for small inputs, |x| < 1 / 32.            */
        if (abs_arg < 0.03125)
        {
            /*  For very small inputs, |x| < 2^-30, return 1. The error is    *
             *  O(x^2), the value of the window is 1 to double precision.     */
            if (abs_arg < 9.313225746154785E-10)
                return 1.0;

            /*  Otherwise, use a Remez polynomial with a few terms.           */
            return tmpl_Double_Coss_Remez(abs_arg);
        }

        /*  For 1 / 32 <= |x| < 1 / 4, use a rational Remez approximation.    */
        return tmpl_Double_Coss_Rat_Remez(abs_arg);
    }

    /*  For arguments on the tail-end of the window, we use an expansion in   *
     *  terms of x - 1 / 2. This helps ensure the window goes to zero at the  *
     *  endpoints.                                                            */
    if (abs_arg < 0.5)
        return tmpl_Double_Coss_Tail_End(abs_arg);

    /*  All other values (including + / - infinity) fall outside of the       *
     *  domain of the window. Return zero.                                    */
    return 0.0;
}
/*  End of tmpl_Double_Coss.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
