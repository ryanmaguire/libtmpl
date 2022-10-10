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
 *                              tmpl_cbrt_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing cubic roots at double precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cbrt                                                      *
 *  Purpose:                                                                  *
 *      Computes y = cbrt(x), the unique number y such that x = y^3.          *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cbrt_x (double):                                                      *
 *          The cubic root of x at double precision.                          *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and libtmpl algorithms have     *
 *      been requested. cbrt from math.h otherwise.                           *
 *  Method:                                                                   *
 *      Use a combination of cubic root rules, Taylor series, and Newton's    *
 *      method. That is, cbrt(x) is computed as follows:                      *
 *                                                                            *
 *          If x = +/- NaN, +/- Inf, or +/- 0, return x.                      *
 *          If x is subnormal (denormal), normalize by 2^52.                  *
 *          If x < 0, return -cbrt(-x) since cbrt is an odd function.         *
 *                                                                            *
 *          cbrt(x) = cbrt(1.m * 2^b)                                         *
 *                  = cbrt(1.m) * cbrt(2^b)                                   *
 *                  = cbrt(1.m) * 2^{b/3}                                     *
 *                  = cbrt(u) * 2^{b/3}     with u = 1.m                      *
 *                  = cbrt(ut/t) * 2^{b/3}  with t = 1 + k/128 for some k.    *
 *                  = cbrt(u/t) * cbrt(t) * 2^{b/3}                           *
 *                                                                            *
 *      Choose t = 1 + k/128 by choosing k to be the largest integer such     *
 *      that 1 + k/128 <= u. Precompute cbrt(t) and 1/t in a table. The       *
 *      value u/t is now between 1 and 1 + 1/128. Compute cbrt(u/t) by:       *
 *                                                                            *
 *                                                                            *
 *          y = cbrt(u/t)                                                     *
 *            = cbrt(1 + s)             with s = u/t - 1.                     *
 *            ~ 1 + (1/3)s - (1/9)s^2 + (5/81)s^3                             *
 *                                                                            *
 *      y is now accurate to at least 8 decimals. We can double this to at    *
 *      least 16 decimals using 1 iteration of Newton's method. We have:      *
 *                                                                            *
 *                y ~ cbrt(x)                                                 *
 *          y^3 - x ~ 0                                                       *
 *             f(y) = y^3 - x                                                 *
 *            f'(y) = 3y^2                                                    *
 *                                                                            *
 *      Apply Newton's method for 1 iteration:                                *
 *                                                                            *
 *              out = y - f(y)/f'(y)                                          *
 *                  = y - (y^{3} - x)/(3y^{2})                                *
 *                  = (3y^{3} - y^{3} + x)/(3y^{2})                           *
 *                  = (2y^{3} + x)/(3y^{2})                                   *
 *                  = 0.3333*(2y + x/y^2)                                     *
 *                                                                            *
 *      Lastly, since 2^{b/3} is not an integer for some values of b write    *
 *      b = 3k + r, with r = 0, 1, 2. Then 2^{b/3} is 2^{k}2^{r/3}. If r = 0  *
 *      we are done. If r = 1, multiply by cbrt(2). If r = 2, multiply by     *
 *      2^{2/3}. Precompute these two values and multiply if needed.          *
 *  Error:                                                                    *
 *      Based on 1,051,958,476 samples with -10^6 < x < 10^6.                 *
 *          max rel error: 7.0469763017409916e-16                             *
 *          rms rel error: 1.5775644974028550e-16                             *
 *          max abs error: 1.4210854715202004e-14                             *
 *          rms abs error: 2.6790772954468324e-15                             *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 *  2.) tmpl_math_cbrt_lookup_table.h:                                        *
 *          Lookup table with pre-computed values of cbrt(x).                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 22, 2022                                             *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

#define CBRT_2 (1.2599210498948731647672106072782)
#define CBRT_2_SQ (1.5874010519681994747517056392722)
#define ONE_THIRD (0.333333333333333333333333333333)

static const double tmpl_double_cbrt_data[3] = {1.0, CBRT_2, CBRT_2_SQ};

/*  Check for IEEE-754 support. This is significantly faster.                 */
#if TMPL_HAS_IEEE754_DOUBLE == 1

#define A0 (1.0)
#define A1 (0.333333333333333333333333333333)
#define A2 (-0.11111111111111111111111111111)
#define A3 (0.061728395061728395061728395061)

/*  Pre-computed values of cbrt(x) found here.                                */
#include <libtmpl/include/math/tmpl_math_cbrt_lookup_table.h>

/*  The values 1/(1 + k/128) for 0 <= k < 128 found here.                     */
#include <libtmpl/include/math/tmpl_math_rcpr_table.h>

/*  Function for computing square roots at double precision.                  */
double tmpl_Double_Cbrt(double x)
{
    /*  Union of a double and the bits representing a double.                 */
    tmpl_IEEE754_Double w, tmp;

    /*  Integer for indexing the arrays defined above.                        */
    unsigned int ind;

    /*  The exponent part of the input x.                                     */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 3.                              */
    unsigned int parity;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Save the sign of x by copying w into tmp.                             */
    tmp = w;

    /*  cbrt is an odd function. If x is negative, compute -cbrt(-x).         */
    w.bits.sign = 0x00U;

    /*  Subnormal number or zero.                                             */
    if (w.bits.expo == 0x00U)
    {
        /*  cbrt(0) = 0.0.                                                    */
        if (w.r == 0.0)
            return x;

        /*  Non-zero subnormal number. Normalize by multiplying by 2^52,      *
         *  which is 4.503599627370496 x 10^15.                               */
        w.r *= 4.503599627370496E15;

        /*  The parity is computed by expo mod 3. We have added 52 to the     *
         *  exponent to normalize the input, but 52 mod 2 is 1, not 0. Add 2  *
         *  to expo, and subtract 2 from exponent (in a few lines) to ensure  *
         *  the parity variable is correctly computed.                        */
        w.bits.expo += 2U;

        /*  Compute the exponent. Since we multiplied by 2^52, subtract 52    *
         *  from the value. We also added 2 to expo, so subtract 2 more. To   *
         *  compute the correctly rounded exponent after division by 3, add 2 *
         *  more to the value before dividing. The total is adding 56 to the  *
         *  input. Shift by the bias to get the correct exponent for the word.*/
        exponent = TMPL_DOUBLE_UBIAS - ((TMPL_DOUBLE_UBIAS-w.bits.expo)+56U)/3U;
    }

    /*  NaN or infinity. Return the input.                                    */
    else if (w.bits.expo == TMPL_DOUBLE_NANINF_EXP)
        return x;

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS)
        exponent = TMPL_DOUBLE_UBIAS - (TMPL_DOUBLE_UBIAS-w.bits.expo+2U)/3U;
    else
        exponent = TMPL_DOUBLE_UBIAS + (w.bits.expo-TMPL_DOUBLE_UBIAS)/3U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    parity = w.bits.expo % 3U;
    w.bits.expo = TMPL_DOUBLE_UBIAS;

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
     *  power series in the variable 1 + (u/t - 1).                           *
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
     *  array. man0 is 4 bits wide, so we need this and the first 3 bits of   *
     *  man1, the next part of the mantissa.                                  */
    ind = w.bits.man0;

    /*  Obtain the last 3 bits of man1 by shifting down 13 bits. man1 is 16   *
     *  bits wide.                                                            */
    ind = (ind << 3U) + (w.bits.man1 >> 13U);

    /*  Compute s = u/t - 1 via s = u * (1/t) - 1 using the array rcpr.       */
    w.r = w.r*tmpl_double_rcpr_table[ind] - 1.0;

    /*  Compute the polynomial to the first few terms via Horner's method.    */
    w.r = A0 + w.r*(A1 + w.r*(A2 + w.r*A3));

    /*  Get the correctly rounded down integer exponent/3.                    */
    w.bits.expo = exponent & 0x7FFU;
    w.r *= tmpl_double_cbrt_data[parity]*tmpl_double_cbrt_lookup_table[ind];

    /*  tmp still has the original sign of x. Copy this to the output.        */
    w.bits.sign = tmp.bits.sign;

    /*  Apply 1 iteration of Newton's method and return.                      */
    return ONE_THIRD*(2.0*w.r + x/(w.r*w.r));
}
/*  End of tmpl_Double_Cbrt.                                                  */

#else
/*  Else for TMPL_HAS_IEEE754_DOUBLE.                                         */

double tmpl_Double_Cbrt(double x)
{
    signed int expo, parity;
    double mant, out;

    if (tmpl_Double_Is_NaN_Or_Inf(x))
        return x;

    tmpl_Double_Base2_Mant_and_Exp(x, &mant, &expo);

    if (expo < 0)
    {
        parity = expo % 3;

        if (parity < 0)
            parity += 3;

        expo = (expo + 2)/3;
    }
    else
    {
        parity = expo % 3;
        expo = expo/3;
    }

    out = tmpl_Double_Cbrt_Pade(mant);
    out = out*tmpl_Double_Pow2(expo);
    out = out*tmpl_double_cbrt_data[parity];

    if (x < 0.0)
        out = -out;

    /*  Apply 1 iteration of Newton's method and return.                      */
    return ONE_THIRD*(2.0*out + x/(out*out));
}
/*  End of tmpl_Double_Cbrt.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef CBRT_2
#undef CBRT_2_SQ
#undef ONE_THIRD

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
