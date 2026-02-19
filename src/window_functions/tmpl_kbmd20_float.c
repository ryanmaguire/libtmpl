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
 *                             tmpl_kbmd20_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window with alpha = 2.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_KBMD20                                                     *
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
 *      x (const float):                                                      *
 *          A real number, the input data value.                              *
 *      width (const float):                                                  *
 *          The width of the window. Units are the same as x.                 *
 *  Output:                                                                   *
 *      kbmd20_xw (float):                                                    *
 *          The modified Kaiser-Bessel window evaluated at x / width.         *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          src/window_functions/auxiliary/                                   *
 *              tmpl_Float_KBMD20_Remez:                                      *
 *                  Computes KBMD20(x) using a Remez polynomial.              *
 *              tmpl_Float_KBMD20_Rat_Remez:                                  *
 *                  Computes KBMD20(x) using a rational Remez approximation.  *
 *              tmpl_Float_KBMD20_Tail_End:                                   *
 *                  Computes KBMD20(x) using a Remez expansion in x - 1 / 2.  *
 *      Method:                                                               *
 *          Set x = x / width, then do the following.                         *
 *          x is NaN:                                                         *
 *              Return NaN.                                                   *
 *          |x| < 2^-15:                                                      *
 *              Return 1. Error is O(x^2), accurate to single precision.      *
 *          |x| < 2^-5:                                                       *
 *              Use a degree 4 Remez polynomial for:                          *
 *                                                                            *
 *                         KBMD20(x) - 1                                      *
 *                  f(x) = -------------                                      *
 *                                2                                           *
 *                               x                                            *
 *                                                                            *
 *              Return 1 + x^2 P(x) where P is the degree 4 Remez polynomial  *
 *              for f. Note, since f is even, only 3 of the terms in P are    *
 *              non-zero.                                                     *
 *          |x| < 2^-2:                                                       *
 *              Use a degree (6, 4) rational Remez approximation. Since the   *
 *              window is even, there are only 4 non-zero terms in the        *
 *              numerator and 3 non-zero terms in the denominator.            *
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
 *              (4, 3) rational Remez approximation for g on the interval     *
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
 *              tmpl_Float_Abs:                                               *
 *                  Computes the absolute value of a real number.             *
 *              tmpl_Float_Is_NaN:                                            *
 *                  Determines if a float is Not-a-Number.                    *
 *          src/window_functions/auxiliary/                                   *
 *              tmpl_Float_KBMD20_Remez:                                      *
 *                  Computes KBMD20(x) using a Remez polynomial.              *
 *              tmpl_Float_KBMD20_Rat_Remez:                                  *
 *                  Computes KBMD20(x) using a rational Remez approximation.  *
 *              tmpl_Float_KBMD20_Tail_End:                                   *
 *                  Computes KBMD20(x) using a Remez expansion in x - 1 / 2.  *
 *      Method:                                                               *
 *          Same as the IEEE-754 method but check for NaN using the Is_NaN    *
 *          function, and compute the absolute value using the Abs function.  *
 *  Error:                                                                    *
 *          Based on 100,000 samples with -1/2 < x < 1/2 and w = 1            *
 *              max relative error: 3.7227902705101654E-07                    *
 *              rms relative error: 7.7574008765223670E-08                    *
 *              max absolute error: 1.1831117390820891E-07                    *
 *              rms absolute error: 2.7601964705094504E-08                    *
 *          Values were computed using the Python library mpmath with 224     *
 *          bits of precision (1 ULP ~= 10^-68).                              *
 *  Notes:                                                                    *
 *      1.) Accurate to single precision.                                     *
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
 *  1.) tmpl_nan_float.h:                                                     *
 *          Header file providing single precision NaN (Not-a-Number).        *
 *  2.) tmpl_ieee754_float.h:                                                 *
 *          Header file where the tmpl_IEEE754_Float type is defined.         *
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
extern float tmpl_Float_KBMD20(const float x, const float width);

/*  TMPL_NAN macro found here which provides single precision NaN.            */
#include <libtmpl/include/nan/tmpl_nan_float.h>

/*  TMPL_HAS_IEEE754_FLOAT macro and tmpl_IEEE754_Float type given here.      */
#include <libtmpl/include/types/tmpl_ieee754_float.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Remez polynomial for the modified Kaiser-Bessel window.                   */
#include "auxiliary/tmpl_kbmd20_remez_float.h"

/*  Rational Remez approximation for the modified Kaiser-Bessel window.       */
#include "auxiliary/tmpl_kbmd20_rat_remez_float.h"

/*  Tail-end expansion using a shifted rational Remez approximation.          */
#include "auxiliary/tmpl_kbmd20_tail_end_float.h"

/*  With IEEE-754 support we can check if the input falls within the window   *
 *  more efficiently. This gives a slight performance boost.                  */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Single precision Kaiser-Bessel window with alpha = 2.                     */
float tmpl_Float_KBMD20(const float x, const float width)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;

    /*  The interval [-w/2, w/2] is compressed to [-1/2, 1/2] by computing    *
     *  the ratio of the inputs. This is the main argument for the window.    */
    w.r = x / width;

    /*  If |x| < 1 / 4, use one of the Remez approximations.                  */
    if (TMPL_FLOAT_EXPO_BITS(w) < TMPL_FLOAT_UBIAS - 0x02U)
    {
        /*  Avoid underflow, check for small inputs, |x| < 1 / 32.            */
        if (TMPL_FLOAT_EXPO_BITS(w) < TMPL_FLOAT_UBIAS - 0x05U)
        {
            /*  For very small inputs, |x| < 2^-15, return 1. The error is    *
             *  O(x^2), the value of the window is 1 to single precision.     */
            if (TMPL_FLOAT_EXPO_BITS(w) < TMPL_FLOAT_UBIAS - 0x0FU)
                return 1.0F;

            /*  Otherwise, use a Remez polynomial with a few terms.           */
            return tmpl_Float_KBMD20_Remez(w.r);
        }

        /*  For 1 / 32 <= |x| < 1 / 4, use a rational Remez approximation.    */
        return tmpl_Float_KBMD20_Rat_Remez(w.r);
    }

    /*  For arguments on the tail-end of the window, we use an expansion in   *
     *  terms of x - 1 / 2. This helps ensure the window goes to zero at the  *
     *  endpoints.                                                            */
    if (TMPL_FLOAT_EXPO_BITS(w) < TMPL_FLOAT_UBIAS - 0x01U)
    {
        /*  The tail-end function assumes 1 / 4 <= x <= 1 / 2. Since the      *
         *  window function is symmetric, we can handle negative values by    *
         *  using the absolute value. Set the sign bit to zero.               */
        w.bits.sign = 0x00U;

        /*  Compute using a rational Remez approximation that is expanded in  *
         *  terms of x - 1 / 2.                                               */
        return tmpl_Float_KBMD20_Tail_End(w.r);
    }

    /*  Special case, if the input is NaN, then the output is too.            */
    if (TMPL_FLOAT_IS_NAN(w))
        return w.r;

    /*  All other values (including + / - infinity) fall outside of the       *
     *  domain of the window. Return zero.                                    */
    return 0.0F;
}
/*  End of tmpl_Float_KBMD20.                                                 */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Single precision Kaiser-Bessel window with alpha = 2.                     */
float tmpl_Float_KBMD20(const float x, const float width)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float abs_arg;

    /*  The interval [-w/2, w/2] is compressed to [-1/2, 1/2] by computing    *
     *  the ratio of the inputs. This is the main argument for the window.    */
    const float arg = x / width;

    /*  Special case, if the argument is NaN, return NaN.                     */
    if (tmpl_Float_Is_NaN(arg))
        return arg;

    /*  The window function is even, compute the absolute value and use that. */
    abs_arg = tmpl_Float_Abs(arg);

    /*  If |x| < 1 / 4, use one of the Remez approximations.                  */
    if (abs_arg < 0.25F)
    {
        /*  Avoid underflow, check for small inputs, |x| < 1 / 32.            */
        if (abs_arg < 0.03125F)
        {
            /*  For very small inputs, |x| < 2^-15, return 1. The error is    *
             *  O(x^2), the value of the window is 1 to single precision.     */
            if (abs_arg < 3.0517578125E-05F)
                return 1.0F;

            /*  Otherwise, use a Remez polynomial with a few terms.           */
            return tmpl_Float_KBMD20_Remez(abs_arg);
        }

        /*  For 1 / 32 <= |x| < 1 / 4, use a rational Remez approximation.    */
        return tmpl_Float_KBMD20_Rat_Remez(abs_arg);
    }

    /*  For arguments on the tail-end of the window, we use an expansion in   *
     *  terms of x - 1 / 2. This helps ensure the window goes to zero at the  *
     *  endpoints.                                                            */
    if (abs_arg < 0.5F)
        return tmpl_Float_KBMD20_Tail_End(abs_arg);

    /*  All other values (including + / - infinity) fall outside of the       *
     *  domain of the window. Return zero.                                    */
    return 0.0F;
}
/*  End of tmpl_Float_KBMD20.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */
