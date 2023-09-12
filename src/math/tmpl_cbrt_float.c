/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                              tmpl_cbrt_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing cubic roots at single precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Cbrt                                                       *
 *  Purpose:                                                                  *
 *      Computes y = cbrt(x), the unique number y such that x = y^3.          *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cbrt_x (float):                                                       *
 *          The cubic root of x at single precision.                          *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and libtmpl algorithms have     *
 *      been requested. cbrt from math.h otherwise.                           *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_cbrt_remez_float.h                                           *
 *              tmpl_Float_Cbrt_Remez:                                        *
 *                  Computes a Remez minimax approximation of cbrt near x = 1.*
 *      Method:                                                               *
 *          Use a combination of cube root rules and polynomials.             *
 *                                                                            *
 *              If x = +/- NaN, +/- Inf, or +/- 0, return x.                  *
 *              If x is subnormal (denormal), normalize by 2^23.              *
 *              If x < 0, return -cbrt(-x) since cbrt is an odd function.     *
 *                                                                            *
 *              cbrt(x) = cbrt(1.m * 2^b)                                     *
 *                      = cbrt(1.m) * cbrt(2^b)                               *
 *                      = cbrt(1.m) * 2^{b/3}                                 *
 *                      = cbrt(u) * 2^{b/3}    with u = 1.m                   *
 *                      = cbrt(ut/t) * 2^{b/3} with t = 1 + k/128 for some k. *
 *                      = cbrt(u/t) * cbrt(t) * 2^{b/3}                       *
 *                                                                            *
 *          Choose t = 1 + k/128 by choosing k to be the largest integer such *
 *          that 1 + k/128 <= u. Precompute cbrt(t) and 1/t in a table. The   *
 *          value u/t is now between 1 and 1 + 1/128. Compute cbrt(u/t) by:   *
 *                                                                            *
 *              y = cbrt(u/t)                                                 *
 *              = cbrt(1 + s)             with s = u/t - 1.                   *
 *              ~ 1 + (1/3)s - (1/9)s^2 + (5/81)s^3                           *
 *                                                                            *
 *          y is now accurate to at least 8 decimals. Note, a Remez minimax   *
 *          approximation is used instead of a Taylor series. The             *
 *          coefficients are slightly different.                              *
 *                                                                            *
 *          Lastly, since 2^{b/3} is not an integer for some values of b      *
 *          write b = 3k + r, with r = 0, 1, 2. Then 2^{b/3} is 2^{k}2^{r/3}. *
 *          If r = 0 we are done. If r = 1, multiply by cbrt(2). If r = 2,    *
 *          multiply by 2^{2/3}. Precompute these two values and multiply if  *
 *          needed.                                                           *
 *      Error:                                                                *
 *          Based on 1,051,958,476 samples with -10^6 < x < 10^6.             *
 *              max rel error: 7.6293943607197434e-08                         *
 *              rms rel error: 7.6293943607172487e-08                         *
 *              max abs error: 7.6293945312500000e-06                         *
 *              rms abs error: 7.6293945312500000e-06                         *
 *          Error values assume 100% accuracy in glibc. Actual error is       *
 *          around 1 ULP (~10^-7 relative error).                             *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_cbrt_pade_float.h:                                           *
 *              tmpl_Float_Cbrt_Pade:                                         *
 *                  Computes a Pade approximant of cbrt near x = 1.           *
 *          tmpl_math.h:                                                      *
 *              tmpl_Float_Is_NaN_Or_Inf:                                     *
 *                  Determines if a float is NaN or infinity.                 *
 *              tmpl_Float_Base2_Mant_and_Exp:                                *
 *                  Gets the input into scientific form, |x| = m * 2^b with   *
 *                  1 <= m < 2 and b an integer.                              *
 *              tmpl_Float_Pow2:                                              *
 *                  Quickly computes an integer power of 2 as a float.        *
 *      Method:                                                               *
 *          Reduce to x >= 0 since cbrt is an odd function. Convert x to      *
 *          scientific notation x = m * 2^b with 1 <= m < 2 and b an integer. *
 *          Use the Pade approximant on m and multiply by 2^{b/3}. Finish by  *
 *          performing one iteration of Newton's method.                      *
 *      Error:                                                                *
 *          Based on 1,051,958,476 samples with -10^6 < x < 10^6.             *
 *              max rel error: 2.3733362297662097e-07                         *
 *              rms rel error: 5.7575034070871672e-08                         *
 *              max abs error: 1.5258789062500000e-05                         *
 *              rms abs error: 4.4232975581690239e-06                         *
 *          Error values assume 100% accuracy in glibc. Actual error is       *
 *          around 1 ULP (~10^-7 relative error).                             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 *  2.) tmpl_cbrt_remez_float.h:                                              *
 *          Used in the IEEE-754 version. Remez approximation for cbrt.       *
 *  3.) tmpl_cbrt_pade_float.h:                                               *
 *          Used in the portable version. Pade approximant for cbrt.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 22, 2022                                             *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  The values 2^{0/3}, 2^{1/3}, and 2^{2/3}.                                 */
static const float tmpl_float_cbrt_data[3] = {
    1.0000000000000000000000000000000F,
    1.2599210498948731647672106072782F,
    1.5874010519681994747517056392722F
};

/*  Check for IEEE-754 support. This is significantly faster.                 */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Remez approximation provided here.                                        */
#include <libtmpl/include/math/tmpl_cbrt_remez_float.h>

/*  Table of pre-computed values for the cbrt function.                       */
#include <libtmpl/include/math/tmpl_cbrt_table_float.h>

/*  Function for computing cube roots at single precision.                    */
float tmpl_Float_Cbrt(float x)
{
    /*  Union of a float and the bits representing a float.                   */
    tmpl_IEEE754_Float w, tmp;

    /*  Integer for indexing the pre-computed cube root array.                */
    unsigned int ind;

    /*  The exponent part of the output.                                      */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 3.                              */
    unsigned int parity;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  Save the sign of x by copying w into tmp.                             */
    tmp.bits.sign = w.bits.sign;

    /*  cbrt is an odd function. If x is negative, compute -cbrt(-x).         */
    w.bits.sign = 0x00U;

    /*  Subnormal number or zero.                                             */
    if (w.bits.expo == 0x00U)
    {
        /*  cbrt(0) = 0.0.                                                    */
        if (w.r == 0.0F)
            return x;

        /*  Non-zero subnormal number. Normalize by multiplying by 2^23,      *
         *  which is 8.388608 x 10^6.                                         */
        w.r *= TMPL_FLOAT_NORMALIZE;

        /*  The parity is computed by expo mod 3. We have added 23 to the     *
         *  exponent to normalize the input, but 23 mod 3 is 2, not 0. Add 1  *
         *  to expo, and subtract 1 from exponent (in a few lines) to ensure  *
         *  the parity variable is correctly computed.                        */
        w.bits.expo += 1U;

        /*  Compute the exponent. Since we multiplied by 2^23, subtract 23    *
         *  from the value. We also added 1 to expo, so subtract 1 more. To   *
         *  compute the correctly rounded exponent after division by 3,       *
         *  subtract 2 more from the value. The total is subtracting 26.      *
         *  Shift by the bias to get the correct exponent for the word.       */
        exponent = TMPL_FLOAT_UBIAS - ((TMPL_FLOAT_UBIAS-w.bits.expo)+26U)/3U;
    }

    /*  NaN or infinity. Return the input.                                    */
    else if (w.bits.expo == TMPL_FLOAT_NANINF_EXP)
        return x;

    /*  Normal number. Compute the exponent. This is the exponent of the      *
     *  original number divided by 3 since we are taking the cubic root. A    *
     *  little care is needed to account for the bias. The exponent is        *
     *                                                                        *
     *      b = E - B                                                         *
     *                                                                        *
     *  where B is the bias and E is the number stored in w.bits.expo. We     *
     *  want to solve for the exponent of the new number. We want:            *
     *                                                                        *
     *      b / 3 = E' - B = (E - B) / 3                                      *
     *                                                                        *
     *  where E' is the resulting number stored in the expo bits of the       *
     *  output. We compute:                                                   *
     *                                                                        *
     *      E' = (E + 2B) / 3                                                 *
     *                                                                        *
     *  The bias for 32-bit float is 127, and 2*127 = 254 is not divisible    *
     *  by 3. However, 255 is. So we write:                                   *
     *                                                                        *
     *      E' = (E + 2B) / 3                                                 *
     *         = ((E - 1) + (2B + 1)) / 3                                     *
     *         = ((E - 1) + 255) / 3                                          *
     *         = (E - 1) / 3 + 85                                             *
     *                                                                        *
     *  Note that we've already checked that E != 0, so E - 1 will not        *
     *  wrap around. That is, E - 1 >= 0. The number 85 is 0x55 in hex.       */
    else
        exponent = 0x55U + (w.bits.expo - 1U)/3U;

    /*  Compute the parity of the exponent. This tells us if we need to       *
     *  multiply the end result by 1, 2^{1/3}, or 2^{2/3}. It can be computed *
     *  by calculating expo mod 3, but we must consider the bias. The bias is *
     *  127, and 127 mod 3 is 1. If we subtract one from the exponent, the    *
     *  result mod 3 is the parity. Note that we've ensured w.bits.expo > 0   *
     *  so we may safely subtract 1 without fear of wrapping around.          */
    parity = (w.bits.expo - 1U) % 3U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_FLOAT_UBIAS;

    /*  We compute cbrt(x) via:                                               *
     *                                                                        *
     *      cbrt(x) = cbrt(1.m * 2^b)                                         *
     *              = cbrt(1.m) * cbrt(2^b)                                   *
     *              = cbrt(1.m) * 2^(b/3)                                     *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/128 such that t <= u. Precompute cbrt(t) in a table   *
     *  and then have:                                                        *
     *                                                                        *
     *      cbrt(x) = cbrt(u) * 2^(b/3)                                       *
     *              = cbrt(ut/t) * 2^(b/3)                                    *
     *              = cbrt(u/t) * cbrt(t) * 2^(b/3)                           *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/128. We compute cbrt(u/t) via a  *
     *  polynomial in the variable 1 + (u/t - 1).                             *
     *                                                                        *
     *  We compute the value t = 1 + k/128 by computing k. The value k can be *
     *  obtained from the mantissa of the input. We have:                     *
     *                                                                        *
     *           0.5 0.25 0.125 0.0625 0.03125 0.015625 0.0078125             *
     *            |   |    |     |      |       |        |                    *
     *            V   V    V     V      V       V        V                    *
     *      u = 1.a   b    c     d      e       f        g        ....        *
     *                                                                        *
     *  If we treat the abcdefg as an integer in binary, this is the number k *
     *  such that t = 1 + k/128. So we simply need to read off this value     *
     *  from the mantissa. The value 1 / (1 + k/128) is stored in the rcpr    *
     *  array. man0 for float has all of the bits we need.                    */
    ind = w.bits.man0;

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    w.r = w.r*tmpl_float_rcpr_table[ind];

    /*  Compute the Remez minimax approximation for cbrt. Peak error 10^-9.   */
    w.r = tmpl_Float_Cbrt_Remez(w.r);

    /*  Get the correctly rounded down integer exponent/3.                    */
    w.bits.expo = exponent & 0xFFU;

    /*  Compute 2^{b/3} * cbrt(t) using the two tables.                       */
    w.r *= tmpl_float_cbrt_data[parity]*tmpl_float_cbrt_table[ind];

    /*  tmp still has the original sign of x. Copy this to the output.        */
    w.bits.sign = tmp.bits.sign;

    /*  The Remez error is within single precision, and we can skip the       *
     *  Newton iteration found in the double and long double implementations. */
    return w.r;
}
/*  End of tmpl_Float_Cbrt.                                                   */

#else
/*  Else for TMPL_HAS_IEEE754_FLOAT.                                          */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Pade approximant provided here.                                           */
#include <libtmpl/include/math/tmpl_cbrt_pade_float.h>

/*  Newton's method has a divide-by-three in the expression.                  */
#define ONE_THIRD (3.333333333333333333333333E-01F)

/*  Function for computing cube roots at single precision.                    */
float tmpl_Float_Cbrt(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    signed int expo, parity;
    float mant, out;

    /*  Special case, NaN or inf, simply return the input.                    */
    if (tmpl_Float_Is_NaN_Or_Inf(x))
        return x;

    /*  Get x into scientific form, |x| = mant * 2^expo.                      */
    tmpl_Float_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  Negative exponent, compute the parity which must be positive.         */
    if (expo < 0)
    {
        parity = expo % 3;

        /*  It's possible for parity to be -1 or -2. The correct parity is    *
         *  then 3 plus this value.                                           */
        if (parity < 0)
            parity += 3;

        /*  Get the correctly rounded down value of expo/3.                   */
        expo = (expo - 2) / 3;
    }

    /*  Exponent positive, parity and division by 3 can be performed normally.*/
    else
    {
        parity = expo % 3;
        expo = expo / 3;
    }

    /*  Since 1 <= mant < 2, the Pade approximant can accurately compute cbrt.*/
    out = tmpl_Float_Cbrt_Pade(mant);

    /*  Since cbrt(m * 2^b) = cbrt(m) * 2^{b/3}, multiply by 2^{b/3}.         */
    out *= tmpl_Float_Pow2(expo)*tmpl_float_cbrt_data[parity];

    /*  cbrt is an odd function. If the input was negative, negate the output.*/
    if (x < 0.0F)
        out = -out;

    /*  Apply 1 iteration of Newton's method and return.                      */
    return ONE_THIRD*(2.0F*out + x/(out*out));
}
/*  End of tmpl_Float_Cbrt.                                                   */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef ONE_THIRD

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
