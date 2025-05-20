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
 *                              tmpl_sqrt_ldouble                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at long double precision.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Sqrt                                                     *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique number y such that x = y^2.          *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (long double):                                                 *
 *          The square root of x at long double precision.                    *
 *  64-Bit Double / 80-Bit Extended Versions:                                 *
 *      Called Functions:                                                     *
 *          src/math/auxiliary/                                               *
 *              tmpl_LDouble_Sqrt_Remez:                                      *
 *                  Computes a Remez minimax approximation of sqrt near x = 1.*
 *      Method:                                                               *
 *          Use a combination of square root rules, Remez polynomials, and    *
 *          Newton's method. That is, sqrt(x) is computed as follows:         *
 *                                                                            *
 *              If x = +/- NaN, +/- Inf, or +/- 0, return x.                  *
 *              If x is subnormal (denormal), normalize by 2^52 or 2^63.      *
 *              Compute sqrt(x) via:                                          *
 *                                                                            *
 *              sqrt(x) = sqrt(1.m * 2^b)                                     *
 *                      = sqrt(1.m) * sqrt(2^b)                               *
 *                      = sqrt(1.m) * 2^{b/2}                                 *
 *                      = sqrt(u) * 2^{b/2}    with u = 1.m                   *
 *                      = sqrt(ut/t) * 2^{b/2} with t = 1 + k/128 for some k. *
 *                      = sqrt(u/t) * sqrt(t) * 2^{b/2}                       *
 *                                                                            *
 *          Choose t = 1 + k/128 by choosing k to be the largest integer such *
 *          that 1 + k/128 <= u. Precompute sqrt(t) and 1/t in a table. The   *
 *          value u/t is now between 1 and 1 + 1/128. Compute sqrt(u/t) by:   *
 *                                                                            *
 *              y = sqrt(u/t)                                                 *
 *                = sqrt(1 + s)             with s = u/t - 1.                 *
 *                = 1 + s * P(s)                                              *
 *                                                                            *
 *          Where P is the Remez minimax polynomial for (sqrt(1 + s) - 1) / s *
 *          on the interval [0, 1 / 128]. We use a degree 2 for 64-bit double *
 *          and degree 3 for 80-bit extended. The Remez polynomial requires   *
 *          one degree less than the Taylor polynomial, giving a slight boost *
 *          in performance. y is now accurate to several decimals. We double  *
 *          this to the desired precision by applying Newton's method:        *
 *                                                                            *
 *                    y ~ sqrt(x)                                             *
 *              y^3 - x ~ 0                                                   *
 *                 f(y) = y^2 - x                                             *
 *                f'(y) = 2y                                                  *
 *                                                                            *
 *          Apply Newton's method for 1 iteration:                            *
 *                                                                            *
 *                  out = y - f(y) / f'(y)                                    *
 *                      = y - (y^2 - x) / (2y)                                *
 *                      = (2y^2 - y^2 + x) / (2y)                             *
 *                      = (y^2 + x) / (2y)                                    *
 *                      = (y + x / y) / 2                                     *
 *                                                                            *
 *          Lastly, since 2^{b/2} is not an integer for odd values of b,      *
 *          write b = 2k + r, with r = 0, 1. Then 2^{b/2} is 2^{k}2^{r/2}.    *
 *          If r = 0 we are done. If r = 1, multiply by sqrt(2). Precompute   *
 *          this value and multiply if needed.                                *
 *  128-Bit Quadruple / 128-Bit Double-Double Version:                        *
 *      Called Functions:                                                     *
 *          src/math/auxiliary/                                               *
 *              tmpl_LDouble_Sqrt_Remez:                                      *
 *                  Computes a Remez minimax approximation of sqrt near x = 1.*
 *      Method:                                                               *
 *          Similar to 64-bit double / 80-bit extended, but use Halley's      *
 *          method to improve the precision instead of Newton's. We have:     *
 *                                                                            *
 *                    y ~ sqrt(x)                                             *
 *              y^2 - x ~ 0                                                   *
 *                 f(y) = y^2 - x                                             *
 *                f'(y) = 2y                                                  *
 *               f''(y) = 2                                                   *
 *                                                                            *
 *          Apply Halley's method for 1 iteration:                            *
 *                                                                            *
 *                  out = y - 2f'(y)f(y)/(2f'(y)^2 - f(y)f''(y))              *
 *                      = y (y^2 + 3x) / (x + 3y^2)                           *
 *                                                                            *
 *          The intermediate computation of y^2 causes issues when the input  *
 *          is very small (underflow) or very large (overflow). To avoid this *
 *          we use Newton's method for two iterations, instead of Halley's    *
 *          method for one, for such extreme inputs.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 19, 2025                                                  *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  128-bit double-double stores the data table with doubles.                 */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  The values 2^{0} and 2^{1/2}, used for scaling the end result.            */
static const double tmpl_ldouble_sqrt_data[2] = {
    1.0, 1.4142135623730950488016887242097
};

#else
/*  All other versions use long doubles in the data table.                    */

/*  The values 2^{0/2} and 2^{1/2}.                                           */
static const long double tmpl_ldouble_sqrt_data[2] = {
    1.0L, 1.414213562373095048801688724209698078569671875376948073L
};

#endif
/*  End of double-double vs. 64-bit / 80-bit / 128-bit / portable.            */

/*  Check for IEEE-754 support. This is significantly faster.                 */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  Remez approximation provided here.                                        */
#include "auxiliary/tmpl_sqrt_remez_ldouble.h"

/*  Table of pre-computed values for the sqrt function.                       */
#include "auxiliary/tmpl_sqrt_table_ldouble.h"

/*  64-bit long double uses the same idea as 64-bit double.                   */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Function for computing square roots at long double precision.             */
long double tmpl_LDouble_Sqrt(long double x)
{
    /*  Union of a long double and the bits representing a long double.       */
    tmpl_IEEE754_LDouble w;

    /*  Integer for indexing the pre-computed square root array.              */
    unsigned int ind;

    /*  The exponent part of the output.                                      */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 2.                              */
    unsigned int parity;

    /*  Set the long double part of the union to the input.                   */
    w.r = x;

    /*  Special cases. sqrt(negative) is undefined. sqrt(0) = 0,              *
     *  sqrt(inf) = inf, and sqrt(Not-a-Number) = Not-a-Number.               */
    if (TMPL_LDOUBLE_IS_NEGATIVE(w))
    {
        /*  Minus zero (-0) should be treated the same as zero. In this case, *
         *  return sqrt(-0) = -0. To preserve the sign, return the input.     */
        if (x == 0.0L)
            return x;

        /*  For all x < 0, return Not-a-Number.                               */
        return TMPL_NANL;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
        return x;

    /*  Subnormal number or zero.                                             */
    if (TMPL_LDOUBLE_EXPO_BITS(w) == 0x00U)
    {
        /*  sqrt(0) = 0.0.                                                    */
        if (w.r == 0.0L)
            return x;

        /*  Non-zero subnormal number, normalize to a normal number.          */
        w.r *= TMPL_LDOUBLE_NORMALIZE;

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. To compute the correctly    *
         *  rounded exponent after division by 2, subtract 1 more before      *
         *  dividing, so subtract by 52 + 1 = 53. Finally, shift by the bias. *
         *  In total, we have:                                                *
         *                                                                    *
         *      exponent = 1023 - ((1023 - expo) + 53) / 2                    *
         *               = 485 + (n + 1) / 2                                  *
         *                                                                    *
         *  Where division, "/", means integer division. Using bit-wise shift *
         *  this is equivalent to:                                            *
         *                                                                    *
         *      exponent = 0x1E5 + ((n + 1) >> 1)                             *
         *                                                                    *
         *  where 0x1E5 is 485 in hexidecimal. Compute this.                  */
        exponent = 0x1E5U + ((w.bits.expo + 0x01U) >> 1U);
    }

    /*  Normal number. Compute the exponent. This is the exponent of the      *
     *  original number divided by 2 since we are taking the square root. A   *
     *  little care is needed to account for the bias. The exponent is:       *
     *                                                                        *
     *      e = E - B                                                         *
     *                                                                        *
     *  where B is the bias and E is the number stored in w.bits.expo. We     *
     *  want to solve for the exponent of the new number. We want:            *
     *                                                                        *
     *      e / 2 = E' - B = (E - B) / 2                                      *
     *                                                                        *
     *  where E' is the resulting number stored in the expo bits of the       *
     *  output. We compute:                                                   *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *                                                                        *
     *  The bias for 64-bit double is 1023, which is not even. However, 1024  *
     *  is, so we write:                                                      *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *         = ((E - 1) + (B + 1)) / 2                                      *
     *         = ((E - 1) + 1024) / 2                                         *
     *         = (E - 1) / 2 + 512                                            *
     *                                                                        *
     *  Note that we've already checked that E != 0, so E - 1 will not        *
     *  wrap around. That is, E - 1 >= 0. The number 512 is 0x200 in hex.     */
    else
        exponent = ((TMPL_LDOUBLE_EXPO_BITS(w) - 1U) >> 1U) + 0x200U;

    /*  The parity determines if we scale the final result by sqrt(2) or not. *
     *  This can be determined by the whether or not the exponent is odd.     *
     *  Note that the bias is odd, so exponent - bias changes the parity of   *
     *  the true exponent. That is, if the exponent is 1, which is odd, then  *
     *  the number stored in w.bits.expo is 1024 since 1024 - 1023 = 1. To    *
     *  determine if the exponent is odd, we check if 1 + w.bits.expo is odd. */
    parity = (TMPL_LDOUBLE_EXPO_BITS(w) + 1U) & 1U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_LDOUBLE_BIAS;

    /*  We compute sqrt(x) via:                                               *
     *                                                                        *
     *      sqrt(x) = sqrt(1.m * 2^b)                                         *
     *              = sqrt(1.m) * sqrt(2^b)                                   *
     *              = sqrt(1.m) * 2^(b/2)                                     *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/128 such that t <= u. Precompute sqrt(t) in a table   *
     *  and then have:                                                        *
     *                                                                        *
     *      sqrt(x) = sqrt(u) * 2^(b/2)                                       *
     *              = sqrt(ut/t) * 2^(b/2)                                    *
     *              = sqrt(u/t) * sqrt(t) * 2^(b/2)                           *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/128. We compute sqrt(u/t) via a  *
     *  Remez polynomial in the variable 1 + (u/t - 1).                       *
     *                                                                        *
     *  We compute the value t = 1 + k/128 by computing k. The value k can be *
     *  obtained from the mantissa of the input. We have:                     *
     *                                                                        *
     *           0.5 0.25 0.125 0.0625 0.03125 0.015625 0.0078125             *
     *            |   |    |     |      |       |        |                    *
     *            V   V    V     V      V       V        V                    *
     *      u = 1.a   b    c     d      e       f        g        ....        *
     *                                                                        *
     *  If we treat abcdefg as an integer in binary, this is the number k     *
     *  such that t = 1 + k/128. So we simply need to read off this value     *
     *  from the mantissa. The value 1 / (1 + k/128) is stored in the rcpr    *
     *  array. man0 is 4 bits wide, so we need this and the first 3 bits of   *
     *  man1, the next part of the mantissa.                                  */
    ind = w.bits.man0;

    /*  Obtain the last 3 bits of man1 by shifting down 13 bits. man1 is 16   *
     *  bits wide.                                                            */
    ind = (ind << 3U) + (w.bits.man1 >> 13U);

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    w.r *= tmpl_ldouble_rcpr_table[ind];

    /*  Compute the Remez minimax approximation for sqrt. Peak error 10^-9.   */
    w.r = tmpl_LDouble_Sqrt_Remez(w.r);

    /*  Get the correctly rounded down integer exponent/2.                    */
    w.bits.expo = exponent & 0x7FFU;

    /*  If the exponent is odd, expo/2 is not an integer. Writing expo = 2k+1 *
     *  we have expo/2 = k + 1/2, so 2^{expo/2} = 2^{k+1/2} = 2^{k} * 2^{1/2} *
     *  which is equal to sqrt(2) * 2^{k}. We need to multiply the result by  *
     *  sqrt(2) in the case that exponent is odd. Also, multiply the result   *
     *  sqrt(u/t) by sqrt(t) using the table, giving us sqrt(u).              */
    w.r *= tmpl_ldouble_sqrt_data[parity] * tmpl_ldouble_sqrt_table[ind];

    /*  Apply 1 iteration of Newton's method and return.                      */
    return 0.5L * (w.r + x / w.r);
}
/*  End of tmpl_LDouble_Sqrt.                                                 */

/*  80-bit extended is similar, but extracts the index differently.           */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT

/******************************************************************************
 *                          80-Bit Extended Version                           *
 ******************************************************************************/

/*  Function for computing square roots at long double precision.             */
long double tmpl_LDouble_Sqrt(long double x)
{
    /*  Union of a long double and the bits representing a long double.       */
    tmpl_IEEE754_LDouble w;

    /*  Integer for indexing the pre-computed square root array.              */
    unsigned int ind;

    /*  The exponent part of the output.                                      */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 2.                              */
    unsigned int parity;

    /*  Set the long double part of the union to the input.                   */
    w.r = x;

    /*  Special cases. sqrt(negative) is undefined. sqrt(0) = 0,              *
     *  sqrt(inf) = inf, and sqrt(Not-A-Number) = Not-A-Number.               */
    if (TMPL_LDOUBLE_IS_NEGATIVE(w))
    {
        /*  Minus zero (-0) should be treated the same as zero. In this case, *
         *  return sqrt(-0) = -0. To preserve the sign, return the input.     */
        if (x == 0.0L)
            return x;

        /*  For all x < 0, return Not-A-Number.                               */
        return TMPL_NANL;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
        return x;

    /*  Subnormal number or zero.                                             */
    if (TMPL_LDOUBLE_EXPO_BITS(w) == 0x00U)
    {
        /*  sqrt(0) = 0.0.                                                    */
        if (w.r == 0.0L)
            return x;

        /*  Non-zero subnormal number. Normalize the input.                   */
        w.r *= TMPL_LDOUBLE_NORMALIZE;

        /*  The parity is computed by expo mod 2. We have added 63 to the     *
         *  exponent to normalize the input, but 63 mod 2 is 1, not 0. Add 1  *
         *  to expo, and subtract 1 from exponent (in a few lines) to ensure  *
         *  the parity variable is correctly computed.                        */
        w.bits.expo += 1U;

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. To compute the correctly    *
         *  rounded exponent after division by 2, subtract 1 more before      *
         *  dividing. Lastly, we incremented expo by 1 above to make the      *
         *  offset an even number, so subtract one more. In total we are      *
         *  subtracting 63 + 1 + 1 = 65. Finally, shift by the bias. We have: *
         *                                                                    *
         *      exponent = 16383 - ((16383 - expo) + 65) / 2                  *
         *               = 8159 + (n + 1) / 2                                 *
         *                                                                    *
         *  Where division, "/", means integer division. Using bit-wise shift *
         *  this is equivalent to:                                            *
         *                                                                    *
         *      exponent = 0x1FDF + ((n + 1) >> 1)                            *
         *                                                                    *
         *  where 0x1FDF is 8159 in hexidecimal. Compute this.                */
        exponent = 0x1FDFU + ((w.bits.expo + 0x01U) >> 1U);
    }

    /*  Normal number. Compute the exponent. This is the exponent of the      *
     *  original number divided by 2 since we are taking the square root. A   *
     *  little care is needed to account for the bias. The exponent is:       *
     *                                                                        *
     *      e = E - B                                                         *
     *                                                                        *
     *  where B is the bias and E is the number stored in w.bits.expo. We     *
     *  want to solve for the exponent of the new number. We want:            *
     *                                                                        *
     *      e / 2 = E' - B = (E - B) / 2                                      *
     *                                                                        *
     *  where E' is the resulting number stored in the expo bits of the       *
     *  output. We compute:                                                   *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *                                                                        *
     *  The bias for 80-bit extended is 16383, which is not even. However,    *
     *  16384 is, so we write:                                                *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *         = ((E - 1) + (B + 1)) / 2                                      *
     *         = ((E - 1) + 16384) / 2                                        *
     *         = (E - 1) / 2 + 8192                                           *
     *                                                                        *
     *  Note that we've already checked that E != 0, so E - 1 will not        *
     *  wrap around. That is, E - 1 >= 0. The number 8192 is 0x2000 in hex.   */
    else
        exponent = ((TMPL_LDOUBLE_EXPO_BITS(w) - 1U) >> 1U) + 0x2000U;

    /*  The parity determines if we scale the final result by sqrt(2) or not. *
     *  This can be determined by the whether or not the exponent is odd.     *
     *  Note that the bias is odd, so exponent - bias changes the parity of   *
     *  the true exponent. That is, if the exponent is 1, which is odd, then  *
     *  the number stored in w.bits.expo is 1024 since 1024 - 1023 = 1. To    *
     *  determine if the exponent is odd, we check if 1 + w.bits.expo is odd. */
    parity = (TMPL_LDOUBLE_EXPO_BITS(w) + 1U) & 1U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_LDOUBLE_BIAS;

    /*  We compute sqrt(x) via:                                               *
     *                                                                        *
     *      sqrt(x) = sqrt(1.m * 2^b)                                         *
     *              = sqrt(1.m) * sqrt(2^b)                                   *
     *              = sqrt(1.m) * 2^(b/2)                                     *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/128 such that t <= u. Precompute sqrt(t) in a table   *
     *  and then have:                                                        *
     *                                                                        *
     *      sqrt(x) = sqrt(u) * 2^(b/2)                                       *
     *              = sqrt(ut/t) * 2^(b/2)                                    *
     *              = sqrt(u/t) * sqrt(t) * 2^(b/2)                           *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/128. We compute sqrt(u/t) via a  *
     *  Remez polynomial in the variable 1 + (u/t - 1).                       *
     *                                                                        *
     *  We compute the value t = 1 + k/128 by computing k. The value k can be *
     *  obtained from the mantissa of the input. We have:                     *
     *                                                                        *
     *           0.5 0.25 0.125 0.0625 0.03125 0.015625 0.0078125             *
     *            |   |    |     |      |       |        |                    *
     *            V   V    V     V      V       V        V                    *
     *      u = 1.a   b    c     d      e       f        g        ....        *
     *                                                                        *
     *  If we treat abcdefg as an integer in binary, this is the number k     *
     *  such that t = 1 + k/128. So we simply need to read off this value     *
     *  from the mantissa. The value 1 / (1 + k/128) is stored in the rcpr    *
     *  array. man0 is 15 bits wide, so we need the first 7 bits of it. Shift *
     *  down by 8 to obtain this.                                             */
    ind = w.bits.man0 >> 8U;

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    w.r *= tmpl_ldouble_rcpr_table[ind];

    /*  Compute the Remez minimax approximation for sqrt. Peak error 10^-12.  */
    w.r = tmpl_LDouble_Sqrt_Remez(w.r);

    /*  Get the correctly rounded down integer exponent/2.                    */
    w.bits.expo = exponent & 0x7FFFU;

    /*  If the exponent is odd, expo/2 is not an integer. Writing expo = 2k+1 *
     *  we have expo/2 = k + 1/2, so 2^{expo/2} = 2^{k+1/2} = 2^{k} * 2^{1/2} *
     *  which is equal to sqrt(2) * 2^{k}. We need to multiply the result by  *
     *  sqrt(2) in the case that exponent is odd. Also, multiply the result   *
     *  sqrt(u/t) by sqrt(t) using the table, giving us sqrt(u).              */
    w.r *= tmpl_ldouble_sqrt_data[parity] * tmpl_ldouble_sqrt_table[ind];

    /*  Apply 1 iteration of Newton's method and return.                      */
    return 0.5L * (w.r + x / w.r);
}
/*  End of tmpl_LDouble_Sqrt.                                                 */

/*  128-bit quadruple precision uses Halley's method instead of Newton's.     */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                         128-Bit Quadruple Version                          *
 ******************************************************************************/

/*  Function for computing square roots at long double precision.             */
long double tmpl_LDouble_Sqrt(long double x)
{
    /*  Union of a long double and the bits representing a long double.       */
    tmpl_IEEE754_LDouble w;

    /*  Integer for indexing the pre-computed square root array.              */
    unsigned int ind;

    /*  The exponent part of the output.                                      */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 2.                              */
    unsigned int parity;

    /*  Variable used in Halley's method at the end.                          */
    long double w2;

    /*  Set the long double part of the union to the input.                   */
    w.r = x;

    /*  Special cases. sqrt(negative) is undefined. sqrt(0) = 0,              *
     *  sqrt(inf) = inf, and sqrt(Not-A-Number) = Not-A-Number.               */
    if (TMPL_LDOUBLE_IS_NEGATIVE(w))
    {
        /*  Minus zero (-0) should be treated the same as zero. In this case, *
         *  return sqrt(-0) = -0. To preserve the sign, return the input.     */
        if (x == 0.0L)
            return x;

        /*  For all x < 0, return Not-A-Number.                               */
        return TMPL_NANL;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
        return x;

    /*  Subnormal number or zero.                                             */
    if (TMPL_LDOUBLE_EXPO_BITS(w) == 0x00U)
    {
        /*  sqrt(0) = 0.0.                                                    */
        if (w.r == 0.0L)
            return x;

        /*  Non-zero subnormal number. Normalize the input.                   */
        w.r *= TMPL_LDOUBLE_NORMALIZE;

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. To compute the correctly    *
         *  rounded exponent after division by 2, subtract 1 more before      *
         *  dividing, so subtract by 112 + 1 = 13. Finally, shift by the bias.*
         *  In total, we have:                                                *
         *                                                                    *
         *      exponent = 16383 - ((16383 - expo) + 113) / 2                 *
         *               = 8135 + (n + 1) / 2                                 *
         *                                                                    *
         *  Where division, "/", means integer division. Using bit-wise shift *
         *  this is equivalent to:                                            *
         *                                                                    *
         *      exponent = 0x1FC7 + ((n + 1) >> 1)                            *
         *                                                                    *
         *  where 0x1FC7 is 8135 in hexidecimal. Compute this.                */
        exponent = 0x1FC7U + ((w.bits.expo + 0x01U) >> 1U);
    }

    /*  Normal number. Compute the exponent. This is the exponent of the      *
     *  original number divided by 2 since we are taking the square root. A   *
     *  little care is needed to account for the bias. The exponent is:       *
     *                                                                        *
     *      e = E - B                                                         *
     *                                                                        *
     *  where B is the bias and E is the number stored in w.bits.expo. We     *
     *  want to solve for the exponent of the new number. We want:            *
     *                                                                        *
     *      e / 2 = E' - B = (E - B) / 2                                      *
     *                                                                        *
     *  where E' is the resulting number stored in the expo bits of the       *
     *  output. We compute:                                                   *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *                                                                        *
     *  The bias for 128-bit quadruple is 16383, which is not even. However,  *
     *  16384 is, so we write:                                                *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *         = ((E - 1) + (B + 1)) / 2                                      *
     *         = ((E - 1) + 16384) / 2                                        *
     *         = (E - 1) / 2 + 8192                                           *
     *                                                                        *
     *  Note that we've already checked that E != 0, so E - 1 will not        *
     *  wrap around. That is, E - 1 >= 0. The number 8192 is 0x2000 in hex.   */
    else
        exponent = ((TMPL_LDOUBLE_EXPO_BITS(w) - 1U) >> 1U) + 0x2000U;

    /*  The parity determines if we scale the final result by sqrt(2) or not. *
     *  This can be determined by the whether or not the exponent is odd.     *
     *  Note that the bias is odd, so exponent - bias changes the parity of   *
     *  the true exponent. That is, if the exponent is 1, which is odd, then  *
     *  the number stored in w.bits.expo is 1024 since 1024 - 1023 = 1. To    *
     *  determine if the exponent is odd, we check if 1 + w.bits.expo is odd. */
    parity = (TMPL_LDOUBLE_EXPO_BITS(w) + 1U) & 1U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_LDOUBLE_BIAS;

    /*  We compute sqrt(x) via:                                               *
     *                                                                        *
     *      sqrt(x) = sqrt(1.m * 2^b)                                         *
     *              = sqrt(1.m) * sqrt(2^b)                                   *
     *              = sqrt(1.m) * 2^(b/2)                                     *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/128 such that t <= u. Precompute sqrt(t) in a table   *
     *  and then have:                                                        *
     *                                                                        *
     *      sqrt(x) = sqrt(u) * 2^(b/2)                                       *
     *              = sqrt(ut/t) * 2^(b/2)                                    *
     *              = sqrt(u/t) * sqrt(t) * 2^(b/2)                           *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/128. We compute sqrt(u/t) via a  *
     *  Remez polynomial in the variable 1 + (u/t - 1).                       *
     *                                                                        *
     *  We compute the value t = 1 + k/128 by computing k. The value k can be *
     *  obtained from the mantissa of the input. We have:                     *
     *                                                                        *
     *           0.5 0.25 0.125 0.0625 0.03125 0.015625 0.0078125             *
     *            |   |    |     |      |       |        |                    *
     *            V   V    V     V      V       V        V                    *
     *      u = 1.a   b    c     d      e       f        g        ....        *
     *                                                                        *
     *  If we treat abcdefg as an integer in binary, this is the number k     *
     *  such that t = 1 + k/128. So we simply need to read off this value     *
     *  from the mantissa. The value 1 / (1 + k/128) is stored in the rcpr    *
     *  array. man0 is 16 bits wide, so we need the first 7 bits of it. Shift *
     *  down by 9 to obtain this.                                             */
    ind = w.bits.man0 >> 9U;

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    w.r *= tmpl_ldouble_rcpr_table[ind];

    /*  Compute the Remez minimax approximation for sqrt. Peak error 10^-12.  */
    w.r = tmpl_LDouble_Sqrt_Remez(w.r);

    /*  Get the correctly rounded down integer exponent/2.                    */
    w.bits.expo = exponent & 0x7FFFU;

    /*  If the exponent is odd, expo/2 is not an integer. Writing expo = 2k+1 *
     *  we have expo/2 = k + 1/2, so 2^{expo/2} = 2^{k+1/2} = 2^{k} * 2^{1/2} *
     *  which is equal to sqrt(2) * 2^{k}. We need to multiply the result by  *
     *  sqrt(2) in the case that exponent is odd. Also, multiply the result   *
     *  sqrt(u/t) by sqrt(t) using the table, giving us sqrt(u).              */
    w.r *= tmpl_ldouble_sqrt_data[parity] * tmpl_ldouble_sqrt_table[ind];

    /*  The quicker Halley's method used for normal numbers has the fault of  *
     *  causing underflow for very small inputs and overflow for very large   *
     *  ones. We need to be able to compute w^2 as an intermediate step,      *
     *  which may cause problems. Newton's method only requires w in the      *
     *  intermediate steps, but the convergence is slower, quadratic instead  *
     *  of cubic. For very small and very large numbers use Newton's method.  */
    if (TMPL_LDOUBLE_EXPO_BITS(w) <= TMPL_LDOUBLE_UBIAS - 0x2000U ||
        TMPL_LDOUBLE_EXPO_BITS(w) >= TMPL_LDOUBLE_UBIAS + 0x1FFFU)
    {
        /*  As mentioned, the convergence is slower for Newton's method. We   *
         *  need two iterations to achieve quadruple precision, whereas       *
         *  Halley's method only needs one. Nevertheless, we avoid overflow   *
         *  and underflow.                                                    */
        w.r = 0.5L * (w.r + x / w.r);
        return 0.5L * (w.r + x / w.r);
    }

    /*  Apply 1 iteration of Halley's method and return.                      */
    w2 = w.r * w.r;
    return w.r * (w2 + 3.0L * x) / (x + 3.0L * w2);
}
/*  End of tmpl_LDouble_Sqrt.                                                 */

/*  Double-double uses 64-bit double method combined with Halley's method.    */
#else

/******************************************************************************
 *                       128-Bit Double-Double Version                        *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (+4.9999999942481026927692750049708879562340746546217E-01)
#define A02 (-1.2499867190909895062418178436426601160231476013599E-01)
#define A03 (+6.2045392121239172989223618371410282893180578034924E-02)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*A03))

/*  Function for computing square roots at long double precision.             */
long double tmpl_LDouble_Sqrt(long double x)
{
    /*  Union of a long double and the bits representing a long double.       */
    tmpl_IEEE754_LDouble w;

    /*  Integer for indexing the pre-computed square root array.              */
    unsigned int ind;

    /*  The exponent part of the output.                                      */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 2.                              */
    unsigned int parity;

    /*  Variable used in Halley's method at the end.                          */
    long double w2;

    /*  The bits of the high part.                                            */
    tmpl_IEEE754_Double whi;

    /*  Set the long double part of the union to the input.                   */
    w.r = x;

    /*  Get the high part from the long double.                               */
    whi.r = w.d[0];

    /*  Special cases. sqrt(negative) is undefined. sqrt(0) = 0,              *
     *  sqrt(inf) = inf, and sqrt(Not-A-Number) = Not-A-Number.               */
    if (TMPL_DOUBLE_IS_NEGATIVE(whi))
    {
        /*  Minus zero (-0) should be treated the same as zero. In this case, *
         *  return sqrt(-0) = -0. To preserve the sign, return the input.     */
        if (whi.r == 0.0)
            return x;

        /*  For all x < 0, return Not-A-Number.                               */
        return TMPL_NANL;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(whi))
        return x;

    /*  Subnormal number or zero.                                             */
    if (TMPL_DOUBLE_EXPO_BITS(whi) == 0x00U)
    {
        /*  sqrt(0) = 0.0.                                                    */
        if (whi.r == 0.0L)
            return x;

        /*  Non-zero subnormal number, normalize to a normal number.          */
        whi.r *= TMPL_LDOUBLE_NORMALIZE;

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. To compute the correctly    *
         *  rounded exponent after division by 2, subtract 1 more before      *
         *  dividing, so subtract by 52 + 1 = 53. Finally, shift by the bias. *
         *  In total, we have:                                                *
         *                                                                    *
         *      exponent = 1023 - ((1023 - expo) + 53) / 2                    *
         *               = 485 + (n + 1) / 2                                  *
         *                                                                    *
         *  Where division, "/", means integer division. Using bit-wise shift *
         *  this is equivalent to:                                            *
         *                                                                    *
         *      exponent = 0x1E5 + ((n + 1) >> 1)                             *
         *                                                                    *
         *  where 0x1E5 is 485 in hexidecimal. Compute this.                  */
        exponent = 0x1E5U + ((whi.bits.expo + 1) >> 1);
    }

    /*  Normal number. Compute the exponent. This is the exponent of the      *
     *  original number divided by 2 since we are taking the square root. A   *
     *  little care is needed to account for the bias. The exponent is        *
     *                                                                        *
     *      e = E - B                                                         *
     *                                                                        *
     *  where B is the bias and E is the number stored in whi.bits.expo. We   *
     *  want to solve for the exponent of the new number. We want:            *
     *                                                                        *
     *      e / 2 = E' - B = (E - B) / 2                                      *
     *                                                                        *
     *  where E' is the resulting number stored in the expo bits of the       *
     *  output. We compute:                                                   *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *                                                                        *
     *  The bias for 64-bit double is 1023, which is not even. However, 1024  *
     *  is, so we write:                                                      *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *         = ((E - 1) + (B + 1)) / 2                                      *
     *         = ((E - 1) + 1024) / 2                                         *
     *         = (E - 1) / 2 + 512                                            *
     *                                                                        *
     *  Note that we've already checked that E != 0, so E - 1 will not        *
     *  wrap around. That is, E - 1 >= 0. The number 512 is 0x200 in hex.     */
    else
        exponent = ((TMPL_DOUBLE_EXPO_BITS(whi) - 1U) >> 1U) + 0x200U;

    /*  The parity determines if we scale the final result by sqrt(2) or not. *
     *  This can be determined by the whether or not the exponent is odd.     *
     *  Note that the bias is odd, so exponent - bias changes the parity of   *
     *  the true exponent. That is, if the exponent is 1, which is odd, then  *
     *  the number stored in whi.bits.expo is 1024 since 1024 - 1023 = 1. To  *
     *  determine if the exponent is odd, we check if 1+whi.bits.expo is odd. */
    parity = (TMPL_DOUBLE_EXPO_BITS(whi) + 1U) & 1U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    whi.bits.expo = TMPL_DOUBLE_BIAS;

    /*  Disregard the low part. Halley's method will recover this later.      */
    w.d[1] = 0.0;

    /*  We compute sqrt(x) via:                                               *
     *                                                                        *
     *      sqrt(x) = sqrt(1.m * 2^b)                                         *
     *              = sqrt(1.m) * sqrt(2^b)                                   *
     *              = sqrt(1.m) * 2^(b/2)                                     *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/128 such that t <= u. Precompute sqrt(t) in a table   *
     *  and then have:                                                        *
     *                                                                        *
     *      sqrt(x) = sqrt(u) * 2^(b/2)                                       *
     *              = sqrt(ut/t) * 2^(b/2)                                    *
     *              = sqrt(u/t) * sqrt(t) * 2^(b/2)                           *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/128. We compute sqrt(u/t) via a  *
     *  Remez polynomial in the variable 1 + (u/t - 1).                       *
     *                                                                        *
     *  We compute the value t = 1 + k/128 by computing k. The value k can be *
     *  obtained from the mantissa of the input. We have:                     *
     *                                                                        *
     *           0.5 0.25 0.125 0.0625 0.03125 0.015625 0.0078125             *
     *            |   |    |     |      |       |        |                    *
     *            V   V    V     V      V       V        V                    *
     *      u = 1.a   b    c     d      e       f        g        ....        *
     *                                                                        *
     *  If we treat abcdefg as an integer in binary, this is the number k     *
     *  such that t = 1 + k/128. So we simply need to read off this value     *
     *  from the mantissa. The value 1 / (1 + k/128) is stored in the rcpr    *
     *  array. man0 is 4 bits wide, so we need this and the first 3 bits of   *
     *  man1, the next part of the mantissa.                                  */
    ind = whi.bits.man0;

    /*  Obtain the last 3 bits of man1 by shifting down 13 bits. man1 is 16   *
     *  bits wide.                                                            */
    ind = (ind << 3U) + (whi.bits.man1 >> 13U);

    /*  Compute s = u/t - 1 via s = u * (1/t) - 1 using the array rcpr.       */
    whi.r = whi.r * tmpl_double_rcpr_table[ind] - 1.0;

    /*  Compute the Remez minimax approximation for sqrt. Peak error 10^-12.  */
    whi.r = TMPL_POLY_EVAL(whi.r);

    /*  Get the correctly rounded down integer exponent/2.                    */
    whi.bits.expo = exponent & 0x7FFU;

    /*  Compute 2^{b/2} * sqrt(t) using the two tables.                       */
    whi.r *= tmpl_ldouble_sqrt_data[parity] * tmpl_ldouble_sqrt_table[ind];

    /*  The double part has sqrt(x) to about 12 decimals. The low part of the *
     *  word was zeroed out. We can triple this to 32 decimals using          *
     *  Halley's method. Store the double into the high part of w.            */
    w.d[0] = whi.r; /* w.d[1] is still zero. */

    /*  The quicker Halley's method used for normal numbers has the fault of  *
     *  causing underflow for very small inputs and overflow for very large   *
     *  ones. We need to be able to compute w^2 as an intermediate step,      *
     *  which may cause problems. Newton's method only requires w in the      *
     *  intermediate steps, but the convergence is slower, quadratic instead  *
     *  of cubic. For very small and very large numbers use Newton's method.  */
    if (TMPL_LDOUBLE_EXPO_BITS(w) <= TMPL_LDOUBLE_UBIAS - 0x200U ||
        TMPL_LDOUBLE_EXPO_BITS(w) >= TMPL_LDOUBLE_UBIAS + 0x1FFU)
    {
        /*  As mentioned, the convergence is slower for Newton's method. We   *
         *  need two iterations to achieve quadruple precision, whereas       *
         *  Halley's method only needs one. Nevertheless, we avoid overflow   *
         *  and underflow.                                                    */
        w.r = 0.5L * (w.r + x / w.r);
        return 0.5L * (w.r + x / w.r);
    }

    /*  Apply 1 iteration of Halley's method and return.                      */
    w2 = w.r * w.r;
    return w.r * (w2 + 3.0L * x) / (x + 3.0L * w2);
}
/*  End of tmpl_LDouble_Sqrt.                                                 */

#endif
/*  End of double-double version.                                             */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Rational Remez approximation for sqrt(x) for 1 <= x <= 2.                 */
#include "auxiliary/tmpl_sqrt_rat_remez_ldouble.h"

/*  Function for computing square roots at long double precision.             */
long double tmpl_LDouble_Sqrt(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    signed int expo, parity;
    long double mant, out;

    /*  For negatives the output is complex. Return NaN.                      */
    if (x < 0.0L)
        return TMPL_NANL;

    /*  Special case, NaN, inf, or zero. Simply return the input.             */
    if (tmpl_LDouble_Is_NaN_Or_Inf(x) || (x == 0.0L))
        return x;

    /*  Get x into scientific form, x = mant * 2^expo.                        */
    tmpl_LDouble_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  Negative exponent, compute the parity which must be positive.         */
    if (expo < 0)
    {
        parity = expo % 2;

        /*  It's possible for parity to be -1. The correct parity is then 2   *
         *  plus this value.                                                  */
        if (parity < 0)
            parity += 2;

        /*  Get the correctly rounded down value of expo / 2.                 */
        expo = (expo - 1) / 2;
    }

    /*  Exponent positive, parity and division by 2 can be performed normally.*/
    else
    {
        parity = expo % 2;
        expo = expo / 2;
    }

    /*  Since 1 <= mant < 2, the Remez approximation can compute sqrt(mant).  */
    out = tmpl_LDouble_Sqrt_Rat_Remez(mant);

    /*  Since sqrt(m * 2^b) = sqrt(m) * 2^{b/2}, multiply by 2^{b/2}.         */
    out *= tmpl_LDouble_Pow2(expo) * tmpl_ldouble_sqrt_data[parity];

    /*  Apply 1 iteration of Newton's method and return.                      */
    return 0.5L * (out + x / out);
}
/*  End of tmpl_LDouble_Sqrt.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "auxiliary/tmpl_math_undef.h"

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
