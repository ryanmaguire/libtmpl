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
 *                             tmpl_arctan_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-tangent function at double precision.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arctan                                                    *
 *  Purpose:                                                                  *
 *      Computes atan(x), the inverse tangent function.                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (double):                                                      *
 *          The arc-tangent of x.                                             *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available.                                *
 *      If not, the following are called.                                     *
 *          tmpl_Double_Is_NaN (tmpl_math.h)                                  *
 *              Determines if a double is NaN.                                *
 *          tmpl_Double_Is_Inf (tmpl_math.h)                                  *
 *              Determines if a double is infinity.                           *
 *  Method:                                                                   *
 *      Check if the input is is NaN or infinity. Return NaN if it is         *
 *      NaN, and sign(x) * pi / 2 if it is +/- infinity.                      *
 *                                                                            *
 *      Next, use the fact that atan(x) is odd to reduce to the case          *
 *      x >= 0. For small values, use the MacLaurin series. For values in     *
 *      certain ranges, use formula 4.4.34 from Abramowitz and Stegun to      *
 *      reduce the argument to a smaller value. This formula states that:     *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) - atan(v) = atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *      With the portable method, use the following:                          *
 *          x in [0.0,    0.4375)  polynomial.                                *
 *          x in [0.4375, 0.6875)  u = x, v = 1/2, reduce and use polynomial. *
 *          x in [0.6875, 1.1875)  u = x, v = 1, reduce and use polynomial.   *
 *          x in [1.1875, 2.4375)  u = x, v = 3/2, reduce and use polynomial. *
 *          x in [2.4375, inf)     atan(x) = pi/2 + atan(-1/x).               *
 *                                                                            *
 *      x > 2.4375 uses the asymptotic expansion, a polynomial in 1/x. This   *
 *      converges very quickly to pi/2 as x gets larger.                      *
 *                                                                            *
 *      The IEEE-754 method can get a big speed boost. Extract the exponent   *
 *      of the input x. That is, given:                                       *
 *                                                                            *
 *          x = s * 1.m * 2^e                                                 *
 *                                                                            *
 *      where s is the sign, m the mantissa, and e the exponent, extract the  *
 *      value e. Precompute 7 values of atan(v) and use the value e to index  *
 *      this list (e varies from -3 to 3, corresponding to 0.125 to 8. For    *
 *      e < -3 we have |x| < 0.125, so use the MacLaurin series. For e > 3 we *
 *      have |x| > 8, so use the asymptotic expansion). Values of |x| lying   *
 *      between 2^e and 2^{e+1} will use these precomputed values in the      *
 *      formula above from Abramowitz and Stegun. Because of this we can skip *
 *      most of the if-then statements used in the portable method.           *
 *                                                                            *
 *      The following values were obtained via guess-and-check to reduce the  *
 *      relative error to below 2 * 10^-16 ~= 2^-52 = double epsilon.         *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *          x in [0.0, 1/8) u = x, v = 0.18, reduce and use polynomial.       *
 *          x in [1/8, 1/4) u = x, v = 0.35, reduce and use polynomial.       *
 *          x in [1/4, 1/2) u = x, v = 0.72, reduce and use polynomial.       *
 *          x in [1/2, 1)   u = x, v = 1.35, reduce and use polynomial.       *
 *          x in [1, 2)     u = x, v = 2.50, reduce and use polynomial.       *
 *          x in [2, 4)     u = x, v = 4.00, reduce and use polynomial.       *
 *          x in [4, 8)     u = x, v = 8.00, reduce and use polynomial.       *
 *          x >= 8          atan(x) = pi/2 + atan(-1/x).                      *
 *                                                                            *
 *      Very small values need the first 8 terms of the MacLaurin series.     *
 *      Very large values need 6 terms of the asymptotic expansion. All other *
 *      intervals need the first 9 terms.                                     *
 *                                                                            *
 *  Notes:                                                                    *
 *      There are three special cases. If the input is NaN, the output will   *
 *      also be NaN. If the input is positive infinity, the limit is used and *
 *      pi/2 is returned. If the input is negative infinity, the limit is     *
 *      used and -pi/2 is returned.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 09, 2021                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/09/12: Ryan Maguire                                                  *
 *      Added IEEE-754 version. This yields a 2.3x speed boost.               *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  Formula 4.4.34 from Abramowitz and Stegun states:                         *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *  The values v and atan(v) are pre-computed below for the calculation.      */
static const double tmpl_atan_double_v[8] = {
    0.05,
    0.18,
    0.35,
    0.72,
    1.35,
    2.5,
    4.0,
    8.0
};

static const double tmpl_atan_double_atan_of_v[8] = {
    0.0499583957219427614100063,
    0.178092938231197549667920,
    0.336674819386727181396699,
    0.624023052976756847589791,
    0.933247528656203869893663,
    1.19028994968253173292773,
    1.32581766366803246505924,
    1.44644133224813518419997
};

/*  Check for IEEE-754 support.                                               */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

/*  Double precision inverse tangent (atan equivalent).                       */
double tmpl_Double_Arctan(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;
    double arg, out, v, atan_v;
    unsigned int ind;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (w.bits.expo == TMPL_DOUBLE_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if ((w.bits.man0 != 0x0U || w.bits.man1 != 0x0U))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -tmpl_Pi_By_Two;
        else
            return tmpl_Pi_By_Two;
    }

    /*  Small values, |x| < 1/16. Use the MacLaurin series to 6 terms.        */
    else if (w.bits.expo < TMPL_DOUBLE_BIAS - 4U)
    {
        const double x_sq = x*x;
        return x * (
            1.0 + x_sq * (
                -3.33333333333329318027E-01 + x_sq * (
                    1.99999999998764832476E-01 + x_sq * (
                        -1.42857142725034663711E-01 + x_sq * (
                            1.11111104054623557880E-01 + x_sq *
                                -9.09088713343650656196E-02
                        )
                    )
                )
            )
        );
    }

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.sign = 0x00U;

    /*  For |x| > 8, use the asymptotic expansion.                            */
    if (w.bits.expo > TMPL_DOUBLE_BIAS + 3U)
    {
        out = tmpl_Double_Arctan_Asymptotic(w.r);
        return (x < 0.0 ? -out : out);
    }

    /*  The exponent tells us the index for the tables tmpl_atan_double_v and *
     *  tmpl_atan_double_atan_of_v that correspond to x. The index is simply  *
     *  the exponent plus four (since the lowest value is 1/16 = 2^-4, we     *
     *  need to shift up by 4). The exponent has a bias, per the IEEE-754     *
     *  format, so we must subtract this off to get the correct index.        */
    ind = (w.bits.expo + 4U) - TMPL_DOUBLE_BIAS;
    v = tmpl_atan_double_v[ind];
    atan_v = tmpl_atan_double_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (w.r - v) / (1.0 + w.r*v);
    out = atan_v + tmpl_Double_Arctan_Maclaurin(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    return (x < 0.0 ? -out : out);
}
/*  End of tmpl_Double_Arctan.                                                */

#else
/*  #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1.     *
 *  Portable version of arctan function.                                      */

/*  Double precision inverse tangent (atan equivalent).                       */
double tmpl_Double_Arctan(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double abs_x, arg, out, v, atan_v;
    unsigned int ind;

    /*  Special cases, NaN and INF.                                           */
    if (tmpl_Double_Is_NaN(x))
        return x;
    else if (tmpl_Double_Is_Inf(x))
        return (x < 0.0 ? -tmpl_Pi_By_Two : tmpl_Pi_By_Two);

    abs_x = tmpl_Double_Abs(x);

    /*  Small values, |x| < 1/16. Use the MacLaurin series to 6 terms.        */
    if (abs_x < 0.0625)
    {
        const double x_sq = x*x;
        return x * (
            1.0 + x_sq * (
                -3.33333333333329318027E-01 + x_sq * (
                    1.99999999998764832476E-01 + x_sq * (
                        -1.42857142725034663711E-01 + x_sq * (
                            1.11111104054623557880E-01 + x_sq *
                                -9.09088713343650656196E-02
                        )
                    )
                )
            )
        );
    }
    else if (abs_x < 0.125)
        ind = 0U;
    else if (abs_x < 0.25)
        ind = 1U;
    else if (abs_x < 0.5)
        ind = 2U;
    else if (abs_x < 1.0)
        ind = 3U;
    else if (abs_x < 2.0)
        ind = 4U;
    else if (abs_x < 4.0)
        ind = 5U;
    else if (abs_x < 8.0)
        ind = 6U;
    else if (abs_x < 16.0)
        ind = 7U;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    else
    {
        out = tmpl_Double_Arctan_Asymptotic(abs_x);
        return (x < 0.0 ? -out : out);
    }

    v = tmpl_atan_double_v[ind];
    atan_v = tmpl_atan_double_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (abs_x - v) / (1.0 + abs_x*v);
    out = atan_v + tmpl_Double_Arctan_Maclaurin(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    return (x < 0.0 ? -out : out);
}
/*  End of tmpl_Double_Arctan.                                                */

#endif
/*  End #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1. */

#endif
/*  #if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1.   */
