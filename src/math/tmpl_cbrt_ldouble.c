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
 *                              tmpl_cbrt_ldouble                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing cubic roots at long double precision.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Cbrt                                                     *
 *  Purpose:                                                                  *
 *      Computes y = cbrt(x), the unique number y such that x = y^3.          *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cbrt_x (long double):                                                 *
 *          The cubic root of x at long double precision.                     *
 *  64-Bit Double / 80-Bit Extended Versions:                                 *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Cbrt_Taylor (tmpl_math.h):                           *
 *              Computes the Taylor series of cbrt(x) about x = 1.            *
 *      Method:                                                               *
 *          Use a combination of cubic root rules, Taylor series, and Newton's*
 *          method. That is, cbrt(x) is computed as follows:                  *
 *                                                                            *
 *              If x = +/- NaN, +/- Inf, or +/- 0, return x.                  *
 *              If x is subnormal (denormal), normalize by 2^52.              *
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
 *          y is now accurate to a few decimals. Apply Newton's method.       *
 *                                                                            *
 *                    y ~ cbrt(x)                                             *
 *              y^3 - x ~ 0                                                   *
 *                 f(y) = y^3 - x                                             *
 *                f'(y) = 3y^2                                                *
 *                                                                            *
 *          Apply Newton's method for 1 iteration:                            *
 *                                                                            *
 *                  out = y - f(y)/f'(y)                                      *
 *                      = y - (y^{3} - x)/(3y^{2})                            *
 *                      = (3y^{3} - y^{3} + x)/(3y^{2})                       *
 *                      = (2y^{3} + x)/(3y^{2})                               *
 *                      = 0.3333*(2y + x/y^2)                                 *
 *                                                                            *
 *          Lastly, since 2^{b/3} is not an integer for some values of b      *
 *          write b = 3k + r, with r = 0, 1, 2. Then 2^{b/3} is 2^{k}2^{r/3}. *
 *          If r = 0 we are done. If r = 1, multiply by cbrt(2). If r = 2,    *
 *          multiply by 2^{2/3}. Precompute these two values and multiply if  *
 *          needed.                                                           *
 *      Error (64-bit Version):                                               *
 *          Based on 1,124,081,732 samples with -10^6 < x < 10^6.             *
 *              max rel error: 7.0469763017409916e-16                         *
 *              rms rel error: 1.5775644974028550e-16                         *
 *              max abs error: 1.4210854715202004e-14                         *
 *              rms abs error: 2.6790772954468324e-15                         *
 *      Error (80-bit Version):                                               *
 *          Based on 1,124,081,732 samples with -10^6 < x < 10^6.             *
 *              max rel error: 1.6263031802160458e-19                         *
 *              rms rel error: 5.0193793438984997e-20                         *
 *              max abs error: 1.3877787807814457e-17                         *
 *              rms abs error: 3.8916051752684035e-18                         *
 *  128-Bit Quadruple Version:                                                *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Cbrt_Taylor (tmpl_math.h):                           *
 *              Computes the Taylor series of cbrt(x) about x = 1.            *
 *      Method:                                                               *
 *          Similar to 64-bit double / 80-bit extended, but use Halley's      *
 *          method to improve the precision instead of Newton's. We have:     *
 *                                                                            *
 *                    y ~ cbrt(x)                                             *
 *              y^3 - x ~ 0                                                   *
 *                 f(y) = y^3 - x                                             *
 *                f'(y) = 3y^2                                                *
 *               f''(y) = 6y                                                  *
 *                                                                            *
 *          Apply Halley's method for 1 iteration:                            *
 *                                                                            *
 *                  out = y - 2f'(y)f(y)/(2f'(y)^2 - f(y)f''(y))              *
 *                      = y*(2x + y^3) / (x + 2y^3)                           *
 *                                                                            *
 *      Error:                                                                *
 *          Based on 10,000,000 samples with -10^6 < x < 10^6.                *
 *              max rel error: 4.1658200001486494e-34                         *
 *              rms rel error: 9.8932710080529471e-35                         *
 *              max abs error: 3.6977854932234928e-32                         *
 *              rms abs error: 7.6912561628308798e-33                         *
 *  128-Bit Double-Double Version:                                            *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Use the 64-bit double method, but with a slightly more accurate   *
 *          Taylor series. Convert the result to long double and apply 1      *
 *          iteration of Halley's method.                                     *
 *      Error:                                                                *
 *          Based on 10,000,000 samples with -10^6 < x < 10^6.                *
 *              max rel error: 1.0078655821595501e-31                         *
 *              rms rel error: 1.0989354283675196e-32                         *
 *              max abs error: 8.6774699574311299e-30                         *
 *              rms abs error: 8.5334997265454440e-31                         *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Is_NaN_Or_Inf (tmpl_math.h):                         *
 *              Determines if a long double is NaN or infinity.               *
 *          tmpl_LDouble_Base2_Mant_and_Exp (tmpl_math.h):                    *
 *              Gets the input into scientific form, |x| = m * 2^e with       *
 *              1 <= m < 2 and e an integer.                                  *
 *          tmpl_LDouble_Cbrt_Pade (tmpl_math.h):                             *
 *              Computes the Pade approximant of cbrt(x) about x = 1.         *
 *          tmpl_LDouble_Pow2 (tmpl_math.h):                                  *
 *              Quickly computes an integer power of 2 as a long double.      *
 *      Method:                                                               *
 *          Reduce to x >= 0 since cbrt is an odd function. Convert x to      *
 *          scientific notation x = m * 2^b with 1 <= m < 2 and b an integer. *
 *          Use the Pade approximant on m and multiply by 2^{b/3}. Finish by  *
 *          performing one iteration of Newton's method.                      *
 *      Error (64-bit Version):                                               *
 *          Based on 1,124,081,732 samples with -10^6 < x < 10^6.             *
 *              max rel error: 1.6263030109827658e-19                         *
 *              rms rel error: 5.0194294935883383e-20                         *
 *              max abs error: 1.3877787807814457e-17                         *
 *              rms abs error: 3.8916483493519231e-18                         *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 22, 2022                                             *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 support. This is significantly faster.                 */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  64-bit long double uses the same idea as 64-bit double.                   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

#define CBRT_2    (1.259921049894873164767210607278228350570E+00L)
#define CBRT_2_SQ (1.587401051968199474751705639272308260391E+00L)
#define ONE_THIRD (3.333333333333333333333333333333333333333E-01L)

static const long double tmpl_ldouble_cbrt_data[3] = {1.0L, CBRT_2, CBRT_2_SQ};

/*  Function for computing square roots at long double precision.             */
long double tmpl_LDouble_Cbrt(long double x)
{
    /*  Union of a double and the bits representing a long double.            */
    tmpl_IEEE754_LDouble w, tmp;

    /*  Integer for indexing the arrays defined above.                        */
    unsigned int ind;

    /*  The exponent part of the input x.                                     */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 3.                              */
    unsigned int parity;

    /*  Set the long double part of the union to the input.                   */
    w.r = x;

    /*  Save the sign of x by copying w into tmp.                             */
    tmp = w;

    /*  cbrt is an odd function. If x is negative, compute -cbrt(-x).         */
    w.bits.sign = 0x00U;

    /*  Subnormal number or zero.                                             */
    if (w.bits.expo == 0x00U)
    {
        /*  cbrt(0) = 0.0.                                                    */
        if (w.r == 0.0L)
            return x;

        /*  Non-zero subnormal number. Normalize the input.                   */
        w.r *= TMPL_LDOUBLE_NORMALIZE;

        /*  The parity is computed by expo mod 3. We have added 52 to the     *
         *  exponent to normalize the input, but 52 mod 3 is 1, not 0. Add 2  *
         *  to expo, and subtract 2 from exponent (in a few lines) to ensure  *
         *  the parity variable is correctly computed.                        */
        w.bits.expo += 2U;

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. We also added 2 to expo, so *
         *  subtract 2 more. To compute the correctly rounded exponent after  *
         *  division by 3, subtract 2 more before dividing. The total is      *
         *  subtracting 4 plus the power of two. This power of two is         *
         *  the macro TMPL_LDOUBLE_MANTISSA_ULENGTH, but evaluates to 52, so  *
         *  in total we need to add 56. Finally, shift by the bias.           */
        exponent = TMPL_LDOUBLE_UBIAS-((TMPL_LDOUBLE_UBIAS-w.bits.expo)+56U)/3U;
    }

    /*  NaN or infinity. Return the input.                                    */
    else if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
        return x;

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else if (w.bits.expo < TMPL_LDOUBLE_UBIAS)
        exponent = TMPL_LDOUBLE_UBIAS - (TMPL_LDOUBLE_UBIAS-w.bits.expo+2U)/3U;
    else
        exponent = TMPL_LDOUBLE_UBIAS + (w.bits.expo-TMPL_LDOUBLE_UBIAS)/3U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    parity = w.bits.expo % 3U;
    w.bits.expo = TMPL_LDOUBLE_UBIAS;

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

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    w.r = w.r*tmpl_ldouble_rcpr_table[ind];

    /*  Compute the Taylor series to the first few terms.                     */
    w.r = tmpl_LDouble_Cbrt_Taylor(w.r);

    /*  Get the correctly rounded down integer exponent/3.                    */
    w.bits.expo = exponent & 0x7FFU;
    w.r *= tmpl_ldouble_cbrt_data[parity]*tmpl_ldouble_cbrt_table[ind];

    /*  tmp still has the original sign of x. Copy this to the output.        */
    w.bits.sign = tmp.bits.sign;

    /*  Apply 1 iteration of Newton's method and return.                      */
    return ONE_THIRD*(2.0L*w.r + x/(w.r*w.r));
}
/*  End of tmpl_LDouble_Cbrt.                                                 */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef CBRT_2
#undef CBRT_2_SQ
#undef ONE_THIRD

/*  80-bit extended is similar, but extracts the index differently.           */
#elif \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN  || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN     || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN

/******************************************************************************
 *                          80-Bit Extended Version                           *
 ******************************************************************************/

#define CBRT_2    (1.259921049894873164767210607278228350570E+00L)
#define CBRT_2_SQ (1.587401051968199474751705639272308260391E+00L)
#define ONE_THIRD (3.333333333333333333333333333333333333333E-01L)

static const long double tmpl_ldouble_cbrt_data[3] = {1.0L, CBRT_2, CBRT_2_SQ};

/*  Function for computing square roots at long double precision.             */
long double tmpl_LDouble_Cbrt(long double x)
{
    /*  Union of a double and the bits representing a long double.            */
    tmpl_IEEE754_LDouble w, tmp;

    /*  Integer for indexing the arrays defined above.                        */
    unsigned int ind;

    /*  The exponent part of the input x.                                     */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 3.                              */
    unsigned int parity;

    /*  Set the long double part of the union to the input.                   */
    w.r = x;

    /*  Save the sign of x by copying w into tmp.                             */
    tmp = w;

    /*  cbrt is an odd function. If x is negative, compute -cbrt(-x).         */
    w.bits.sign = 0x00U;

    /*  Subnormal number or zero.                                             */
    if (w.bits.expo == 0x00U)
    {
        /*  cbrt(0) = 0.0.                                                    */
        if (w.r == 0.0L)
            return x;

        /*  Non-zero subnormal number. Normalize the input.                   */
        w.r *= TMPL_LDOUBLE_NORMALIZE;

        /*  We have added 63 to the exponent. 63 mod 3 is zero, so no need to *
         *  add anything to expo, unlike the 64-bit version above.            */

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. To compute the correctly    *
         *  rounded exponent after division by 3, subtract 2 more before      *
         *  dividing. This power of two is the macro                          *
         *  TMPL_LDOUBLE_MANTISSA_ULENGTH, but evaluates to 63, so in total   *
         *  we need to add 65. Finally, shift by the bias.                    */
        exponent = TMPL_LDOUBLE_UBIAS-((TMPL_LDOUBLE_UBIAS-w.bits.expo)+65U)/3U;
    }

    /*  NaN or infinity. Return the input.                                    */
    else if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
        return x;

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else if (w.bits.expo < TMPL_LDOUBLE_UBIAS)
        exponent = TMPL_LDOUBLE_UBIAS - (TMPL_LDOUBLE_UBIAS-w.bits.expo+2U)/3U;
    else
        exponent = TMPL_LDOUBLE_UBIAS + (w.bits.expo-TMPL_LDOUBLE_UBIAS)/3U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    parity = w.bits.expo % 3U;
    w.bits.expo = TMPL_LDOUBLE_UBIAS;

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
     *  array. man0 is 15 bits wide, so shift down by 8 bits.                 */
    ind = w.bits.man0 >> 8U;

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    w.r = w.r*tmpl_ldouble_rcpr_table[ind];

    /*  Compute the Taylor series to the first few terms.                     */
    w.r = tmpl_LDouble_Cbrt_Taylor(w.r);

    /*  Get the correctly rounded down integer exponent/3.                    */
    w.bits.expo = exponent & 0x7FFFU;
    w.r *= tmpl_ldouble_cbrt_data[parity]*tmpl_ldouble_cbrt_table[ind];

    /*  tmp still has the original sign of x. Copy this to the output.        */
    w.bits.sign = tmp.bits.sign;

    /*  Apply 1 iteration of Newton's method and return.                      */
    return ONE_THIRD*(2.0L*w.r + x/(w.r*w.r));
}
/*  End of tmpl_LDouble_Cbrt.                                                 */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef CBRT_2
#undef CBRT_2_SQ
#undef ONE_THIRD

/*  128-bit quadruple precision uses Halley's method instead of Newton's.     */
#elif \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

/******************************************************************************
 *                         128-Bit Quadruple Version                          *
 ******************************************************************************/

#define CBRT_2    (1.259921049894873164767210607278228350570E+00L)
#define CBRT_2_SQ (1.587401051968199474751705639272308260391E+00L)

static const long double tmpl_ldouble_cbrt_data[3] = {1.0L, CBRT_2, CBRT_2_SQ};

/*  Function for computing square roots at long double precision.             */
long double tmpl_LDouble_Cbrt(long double x)
{
    /*  Union of a double and the bits representing a long double.            */
    tmpl_IEEE754_LDouble w, tmp;

    /*  Integer for indexing the arrays defined above.                        */
    unsigned int ind;

    /*  The exponent part of the input x.                                     */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 3.                              */
    unsigned int parity;

    /*  Variable used in Halley's method at the end.                          */
    long double w3;

    /*  Set the long double part of the union to the input.                   */
    w.r = x;

    /*  Save the sign of x by copying w into tmp.                             */
    tmp = w;

    /*  cbrt is an odd function. If x is negative, compute -cbrt(-x).         */
    w.bits.sign = 0x00U;

    /*  Subnormal number or zero.                                             */
    if (w.bits.expo == 0x00U)
    {
        /*  cbrt(0) = 0.0.                                                    */
        if (w.r == 0.0L)
            return x;

        /*  Non-zero subnormal number. Normalize the input.                   */
        w.r *= TMPL_LDOUBLE_NORMALIZE;

        /*  The parity is computed by expo mod 3. We have added 112 to the    *
         *  exponent to normalize the input, but 112 mod 3 is 1, not 0. Add 2 *
         *  to expo, and subtract 2 from exponent (in a few lines) to ensure  *
         *  the parity variable is correctly computed.                        */
        w.bits.expo += 2U;

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. We also added 2 to expo, so *
         *  subtract 2 more. To compute the correctly rounded exponent after  *
         *  division by 3, subtract 2 more before dividing. The total is      *
         *  subtracting 4 plus the power of two. This power of two is         *
         *  the macro TMPL_LDOUBLE_MANTISSA_ULENGTH, but evaluates to 112, so *
         *  in total we need to add 116. Finally, shift by the bias.          */
        exponent =
            TMPL_LDOUBLE_UBIAS-((TMPL_LDOUBLE_UBIAS-w.bits.expo)+116U)/3U;
    }

    /*  NaN or infinity. Return the input.                                    */
    else if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
        return x;

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else if (w.bits.expo < TMPL_LDOUBLE_UBIAS)
        exponent = TMPL_LDOUBLE_UBIAS - (TMPL_LDOUBLE_UBIAS-w.bits.expo+2U)/3U;
    else
        exponent = TMPL_LDOUBLE_UBIAS + (w.bits.expo-TMPL_LDOUBLE_UBIAS)/3U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    parity = w.bits.expo % 3U;
    w.bits.expo = TMPL_LDOUBLE_UBIAS;

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
     *  array. man0 is 16 bits wide, so shift down by 9 bits.                 */
    ind = w.bits.man0 >> 9U;

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    w.r = w.r*tmpl_ldouble_rcpr_table[ind];

    /*  Compute the Taylor series to the first few terms.                     */
    w.r = tmpl_LDouble_Cbrt_Taylor(w.r);

    /*  Get the correctly rounded down integer exponent/3.                    */
    w.bits.expo = exponent & 0x7FFFU;
    w.r *= tmpl_ldouble_cbrt_data[parity]*tmpl_ldouble_cbrt_table[ind];

    /*  tmp still has the original sign of x. Copy this to the output.        */
    w.bits.sign = tmp.bits.sign;

    /*  Apply 1 iteration of Halley's method and return.                      */
    w3 = w.r*w.r*w.r;
    return w.r*(2.0L*x + w3) / (x + 2.0L*w3);
}
/*  End of tmpl_LDouble_Cbrt.                                                 */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef CBRT_2
#undef CBRT_2_SQ

/*  Double-double uses 64-bit double method combined with Halley's method.    */
#else

/******************************************************************************
 *                       128-Bit Double-Double Version                        *
 ******************************************************************************/

#define CBRT_2    (1.259921049894873164767210607278228350570E+00)
#define CBRT_2_SQ (1.587401051968199474751705639272308260391E+00)

/*  Coefficients for the Taylor series at x = 1.                              */
#define A0 (1.0000000000000000000000000000000000000000E+00)
#define A1 (3.3333333333333333333333333333333333333333E-01)
#define A2 (-1.111111111111111111111111111111111111111E-01)
#define A3 (6.1728395061728395061728395061728395061728E-02)
#define A4 (-4.115226337448559670781893004115226337448E-02)

static const double tmpl_ldouble_cbrt_data[3] = {1.0, CBRT_2, CBRT_2_SQ};

/*  Function for computing square roots at long double precision.             */
long double tmpl_LDouble_Cbrt(long double x)
{
    /*  Union of a double and the bits representing a long double.            */
    tmpl_IEEE754_LDouble w;

    /*  Integer for indexing the arrays defined above.                        */
    unsigned int ind;

    /*  The exponent part of the input x.                                     */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 3.                              */
    unsigned int parity;

    /*  Variable used in Halley's method at the end.                          */
    long double w3;

    /*  The bits of the high part.                                            */
    tmpl_IEEE754_Double whi;

    /*  Set the long double part of the union to the input.                   */
    w.r = x;

    /*  Get the high part from the long double.                               */
    whi.r = w.d[0];

    /*  Disregard the low part. Halley's method will recover this later.      */
    w.d[1] = 0.0;

    /*  cbrt is an odd function. If x is negative, compute -cbrt(-x).         */
    whi.bits.sign = 0x00U;

    /*  Subnormal number or zero.                                             */
    if (whi.bits.expo == 0x00U)
    {
        /*  cbrt(0) = 0.0.                                                    */
        if (whi.r == 0.0)
            return x;

        /*  Non-zero subnormal number. Normalize the input.                   */
        whi.r *= TMPL_DOUBLE_NORMALIZE;

        /*  The parity is computed by expo mod 3. We have added 52 to the     *
         *  exponent to normalize the input, but 52 mod 3 is 1, not 0. Add 2  *
         *  to expo, and subtract 2 from exponent (in a few lines) to ensure  *
         *  the parity variable is correctly computed.                        */
        whi.bits.expo += 2U;

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. We also added 2 to expo, so *
         *  subtract 2 more. To compute the correctly rounded exponent after  *
         *  division by 3, subtract 2 more before dividing. The total is      *
         *  subtracting 4 plus the power of two. This power of two is         *
         *  the macro TMPL_LDOUBLE_MANTISSA_ULENGTH, but evaluates to 112, so *
         *  in total we need to add 116. Finally, shift by the bias.          */
        exponent = TMPL_DOUBLE_UBIAS-((TMPL_DOUBLE_UBIAS-whi.bits.expo)+56U)/3U;
    }

    /*  NaN or infinity. Return the input.                                    */
    else if (TMPL_DOUBLE_IS_NAN_OR_INF(whi))
        return x;

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else if (whi.bits.expo < TMPL_DOUBLE_UBIAS)
        exponent = TMPL_DOUBLE_UBIAS - (TMPL_DOUBLE_UBIAS-whi.bits.expo+2U)/3U;
    else
        exponent = TMPL_DOUBLE_UBIAS + (whi.bits.expo-TMPL_LDOUBLE_UBIAS)/3U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    parity = whi.bits.expo % 3U;
    whi.bits.expo = TMPL_DOUBLE_UBIAS;

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
    ind = whi.bits.man0;

    /*  Obtain the last 3 bits of man1 by shifting down 13 bits. man1 is 16   *
     *  bits wide.                                                            */
    ind = (ind << 3U) + (whi.bits.man1 >> 13U);

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    whi.r = whi.r*tmpl_double_rcpr_table[ind];

    /*  Compute the Taylor series to the first few terms.                     */
    whi.r = whi.r - 1.0;
    whi.r = A0 + whi.r*(A1 + whi.r*(A2 + whi.r*(A3 + whi.r*A4)));

    /*  Get the correctly rounded down integer exponent/3.                    */
    whi.bits.expo = exponent & 0x7FFU;
    whi.r *= tmpl_ldouble_cbrt_data[parity]*tmpl_double_cbrt_table[ind];

    /*  Cbrt is an odd function. Negate if needed.                            */
    whi.bits.sign = w.bits.signa;

    /*  The double part has cbrt(x) to about 10 decimals. The low part of the *
     *  word was zeroed out. We can triple this to 32 decimals using          *
     *  Halley's method. Store the double into the high part of w.            */
    w.d[0] = whi.r; /* w.d[1] is still zero. */

    /*  Apply 1 iteration of Halley's method and return.                      */
    w3 = w.r*w.r*w.r;
    return w.r*(2.0L*x + w3) / (x + 2.0L*w3);
}
/*  End of tmpl_LDouble_Cbrt.                                                 */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef CBRT_2
#undef CBRT_2_SQ
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4

#endif
/*  End of double-double version.                                             */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

#define CBRT_2    (1.259921049894873164767210607278228350570E+00L)
#define CBRT_2_SQ (1.587401051968199474751705639272308260391E+00L)
#define ONE_THIRD (3.333333333333333333333333333333333333333E-01L)

static const long double tmpl_ldouble_cbrt_data[3] = {1.0L, CBRT_2, CBRT_2_SQ};

/*  Function for computing square roots at double precision.                  */
long double tmpl_LDouble_Cbrt(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    signed int expo, parity;
    long double mant, out;

    /*  Special case, NaN or inf, simply return the input.                    */
    if (tmpl_LDouble_Is_NaN_Or_Inf(x))
        return x;

    /*  Get x into scientific form, |x| = mant * 2^expo.                      */
    tmpl_LDouble_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  Negative exponent, computation the parity which must be positive.     */
    if (expo < 0)
    {
        parity = expo % 3;

        /*  It's possible for parity to be -1 or -2. The correct parity is    *
         *  then 3 plus this value.                                           */
        if (parity < 0)
            parity += 3;

        /*  Get the correctly rounded down value of expo/3.                   */
        expo = (expo - 2)/3;
    }

    /*  Exponent positive, parity and division by 3 can be performed normally.*/
    else
    {
        parity = expo % 3;
        expo = expo/3;
    }

    /*  Since 1 <= mant < 2, the Pade approximant to accurately compute cbrt. */
    out = tmpl_LDouble_Cbrt_Pade(mant);

    /*  Since cbrt(m * 2^b) = cbrt(m) * 2^{b/3}, multiply by 2^{b/3}.         */
    out = out*tmpl_LDouble_Pow2(expo);
    out = out*tmpl_ldouble_cbrt_data[parity];

    /*  cbrt is an odd function. If the input was negative, negate the output.*/
    if (x < 0.0L)
        out = -out;

    /*  Apply 1 iteration of Newton's method and return.                      */
    return ONE_THIRD*(2.0L*out + x/(out*out));
}
/*  End of tmpl_LDouble_Cbrt.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef ONE_THIRD

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
