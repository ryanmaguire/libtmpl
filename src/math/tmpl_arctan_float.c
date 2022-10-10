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
 *                             tmpl_arctan_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-tangent function at single precision.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arctan:                                                    *
 *  Purpose:                                                                  *
 *      Computes atan(x), the inverse tangent function.                       *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (float):                                                       *
 *          The arc-tangent of x.                                             *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available.                                *
 *      If not, the following are called.                                     *
 *          tmpl_Float_Is_NaN (tmpl_math.h)                                   *
 *              Determines if a float is NaN.                                 *
 *          tmpl_Float_Is_Inf (tmpl_math.h)                                   *
 *              Determines if a float is infinity.                            *
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
 *      relative error to below 10^-7 ~= 2^-23 = single epsilon.              *
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
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 09, 2021                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/09/13: Ryan Maguire                                                  *
 *      Added IEEE-754 version. This yields a 2x speed boost.                 *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 support.                                               */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

#include <libtmpl/include/math/tmpl_math_arctan_tables.h>

/*  Single precision inverse tangent (atanf equivalent).                      */
float tmpl_Float_Arctan(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;
    float arg, out, v, atan_v;
    unsigned int ind;

    /*  Set the float part of the word to the input.                          */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (w.bits.expo == TMPL_FLOAT_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if (TMPL_FLOAT_IS_NAN(w))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -tmpl_Pi_By_Two_F;
        else
            return tmpl_Pi_By_Two_F;
    }

    /*  Small values, |x| < 1/8. Use the MacLaurin series to 8 terms.         */
    else if (w.bits.expo < TMPL_FLOAT_BIAS - 4U)
        return tmpl_Float_Arctan_Very_Small(x);

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.sign = 0x00U;

    /*  For |x| > 8, use the asymptotic expansion.                            */
    if (w.bits.expo > TMPL_FLOAT_BIAS + 3U)
    {
        out = tmpl_Float_Arctan_Asymptotic(w.r);
        return (x < 0.0F ? -out : out);
    }

    /*  The exponent tells us the index for the tables tmpl_atan_float_v and  *
     *  tmpl_atan_float_atan_of_v that correspond to x. The index is simply   *
     *  the exponent plus three (since the lowest value is 1/8 = 2^-3, we     *
     *  need to shift up by 3). The exponent has a bias, per the IEEE-754     *
     *  format, so we must subtract this off to get the correct index.        */
    ind = (w.bits.expo + 4U) - TMPL_FLOAT_BIAS;
    v = tmpl_atan_float_v[ind];
    atan_v = tmpl_atan_float_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (w.r - v) / (1.0F + w.r*v);
    out = atan_v + tmpl_Float_Arctan_Maclaurin(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    return (x < 0.0F ? -out : out);
}
/*  End of tmpl_Float_Arctan.                                                 */

/*  Undefine all of the macros.                                               */
#undef A0
#undef A1
#undef A2
#undef A3

#else
/*  #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1.       */

/*  Precompute atan(1/2), atan(1), and atan(3/2).                             */
#define ATAN_OF_ONE_HALF 0.46364760900080611621425623146121440202853705F
#define ATAN_OF_ONE 0.78539816339744830961566084581987572104929234F
#define ATAN_OF_THREE_HALFS 0.98279372324732906798571061101466601449687745F

/*  Single precision inverse tangent.                                         */
float tmpl_Float_Arctan(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float arg, sgn_x;

    /*  If the input is NaN, return NaN.                                      */
    if (tmpl_Float_Is_NaN(x))
        return x;

    /*  atan(x) has limits of +/- pi/2 as |x| -> infinity. Check for this.    */
    if (tmpl_Float_Is_Inf(x))
    {
        if (x > 0.0F)
            return tmpl_Pi_By_Two_F;
        else
            return -tmpl_Pi_By_Two_F;
    }

    /*  For all other x, use the fact that atan is an odd function to reduce  *
     *  to the case of x >= 0.                                                */
    if (x < 0.0F)
    {
        sgn_x = -1.0F;
        arg = -x;
    }
    else
    {
        sgn_x = 1.0F;
        arg = x;
    }

    /*  For small values, use the polynomial provided above.                  */
    if (arg < 0.4375F)
        return sgn_x * tmpl_Float_Arctan_Maclaurin(arg);

    /*  Following Abramowitz and Stegun, equation 4.4.34, we can reduce the   *
     *  argument to a smaller value using:                                    *
     *      atan(x) - atan(y) = atan((x - y) / (1 + xy)) (mod pi).            */
    else if (arg < 0.6875F)
    {
        /*  Use the above formula with atan(1/2).                             */
        arg = (2.0F * arg - 1.0F) / (2.0F + arg);
        return sgn_x * (ATAN_OF_ONE_HALF + tmpl_Float_Arctan_Maclaurin(arg));
    }

    /*  Same reduction, but with 1 instead of 1/2.                            */
    else if (arg < 1.1875F)
    {
        arg = (arg - 1.0F) / (arg + 1.0F);
        return sgn_x * (ATAN_OF_ONE + tmpl_Float_Arctan_Maclaurin(arg));
    }

    /*  Same reduction, but with 3/2 instead of 1.                            */
    else if (arg < 2.4375F)
    {
        arg = (2.0F * arg - 3.0F) / (2.0F + 3.0F * arg);
        return sgn_x * (ATAN_OF_THREE_HALFS + tmpl_Float_Arctan_Maclaurin(arg));
    }

    /*  For larger values, the expansion at infinity is sufficient. We use    *
     *  the polynomial for small values with input -1 / arg and precompute    *
     *  atan(infinity), which is pi / 2.                                      */
    else
    {
        arg = -1.0F / arg;
        return sgn_x * (tmpl_Pi_By_Two_F + tmpl_Float_Arctan_Maclaurin(arg));
    }
}
/*  End of tmpl_Float_Arctan.                                                 */

/*  Undefine all of the macros.                                               */
#undef ATAN_OF_ONE_HALF
#undef ATAN_OF_ONE
#undef ATAN_OF_THREE_HALFS

#endif
/*  #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1.       */

#endif
/*  #if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1.   */
