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
 *                              tmpl_sqrt_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at single precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Sqrt                                                       *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (float):                                                       *
 *          The square root of x at single precision.                         *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          src/math/auxiliary/                                               *
 *              tmpl_Float_Sqrt_Remez:                                        *
 *                  Computes sqrt(x) near x = 1 using a Remez polynomial.     *
 *      Method:                                                               *
 *          Use a combination of square root rules, Remez polynomials, and    *
 *          Newton's method. That is, sqrt(x) is computed as follows:         *
 *                                                                            *
 *              If x < 0:                                                     *
 *                  return Not-a-Number.                                      *
 *              If x = +/- NaN, +Inf, or 0:                                   *
 *                  return x.                                                 *
 *              If x is subnormal (denormal):                                 *
 *                  normalize by 2^52 and proceed to the next part.           *
 *                                                                            *
 *          Put x into (binary) scientific form, x = 1.m * 2^b. We then do:   *
 *                                                                            *
 *              sqrt(x) = sqrt(1.m * 2^b)                                     *
 *                      = sqrt(1.m) * sqrt(2^b)                               *
 *                      = sqrt(1.m) * 2^{b/2}                                 *
 *                      = sqrt(u) * 2^{b/2}     with u = 1.m                  *
 *                      = sqrt(ut/t) * 2^{b/2}  with t = 1 + k/128 for some k.*
 *                      = sqrt(u/t) * sqrt(t) * 2^{b/2}                       *
 *                                                                            *
 *          Choose t = 1 + k/128 by choosing k to be the largest integer such *
 *          that 1 + k/128 <= u. Precompute sqrt(t) and 1/t in a table. The   *
 *          value u/t is now between 1 and 1 + 1/128. Compute sqrt(u/t) by:   *
 *                                                                            *
 *              y = sqrt(u/t)                                                 *
 *                = sqrt(1 + s)             with s = u/t - 1.                 *
 *                ~ 1 + 0.5x - 0.125x^2                                       *
 *                                                                            *
 *          y is now accurate to at least 8 decimals. Accuracy can be         *
 *          improved to 9 decimals by using a Remez polynomial instead:       *
 *                                                                            *
 *              y = a + bs + cs^2                                             *
 *                                                                            *
 *          Where a, b, and c are the coefficients from the Remez exchange    *
 *          algorithm for sqrt(1+s) on the interval [0, 1/128].               *
 *                                                                            *
 *          Lastly, since 2^{b/2} is not an integer for odd valued b, use the *
 *          fact that for odd b we have b = 2k+1, so b/2 = k+1/2, and thus:   *
 *                                                                            *
 *              2^{b/2} = 2^{k + 1/2}                                         *
 *                      = 2^{k} * 2^{1/2}                                     *
 *                      = sqrt(2) * 2^{k}                                     *
 *                                                                            *
 *          Precompute sqrt(2) and multiply the result by this if b is odd.   *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Float_Sqrt_Rat_Remez:                                    *
 *                  Computes sqrt(x) via a Pade approximant.                  *
 *              tmpl_Float_Is_NaN_Or_Inf:                                     *
 *                  Determines if a float is NaN or infinity.                 *
 *              tmpl_Float_Pow2:                                              *
 *                  Computes 2^n as a float for integer n.                    *
 *              tmpl_Float_Base2_Mant_and_Exp:                                *
 *                  Gets an input into scientific form x = m * 2^b.           *
 *      Method:                                                               *
 *          Similar to the IEEE-754 method but without the lookup table. Put  *
 *          x into scientific form x = m * 2^b with 1 <= m < 2. Compute       *
 *          sqrt(m) using a rational Remez approximation.                     *
 *  Notes:                                                                    *
 *      libtmpl implements sqrt using assembly code for architectures that    *
 *      support built-in sqrt. This includes x86, x86_64, and arm64 devices.  *
 *      This is much faster than the C code provided, so it is advised        *
 *      that you not use this code unless you need to. This file will not be  *
 *      compiled unless NO_ASM=1 is passed to the Makefile, or if your        *
 *      machine uses an architecture that lacks built-in sqrt.                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 20, 2025                                                  *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  The values 2^{0} and 2^{1/2}, used for scaling the end result.            */
static const float tmpl_float_sqrt_data[2] = {
    1.0F, 1.4142135623730950488016887242097F
};

/*  Check for IEEE-754 support. This is significantly faster.                 */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Lookup table of pre-computed values for sqrt(x).                          */
#include "auxiliary/tmpl_sqrt_table_float.h"

/*  Remez minimax polynomial for sqrt(x) near x = 1.                          */
#include "auxiliary/tmpl_sqrt_remez_float.h"

/*  Function for computing square roots at single precision.                  */
float tmpl_Float_Sqrt(float x)
{
    /*  Union of a float and the bits representing a float.                   */
    tmpl_IEEE754_Float w;

    /*  Integer for indexing the arrays defined above.                        */
    unsigned int ind;

    /*  The exponent part of the output.                                      */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 2.                              */
    unsigned int parity;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  Special cases. sqrt(negative) is undefined. sqrt(0) = 0,              *
     *  sqrt(inf) = inf, and sqrt(Not-A-Number) = Not-A-Number.               */
    if (TMPL_FLOAT_IS_NEGATIVE(w))
    {
        /*  Minus zero (-0) should be treated the same as zero. In this case, *
         *  return sqrt(-0) = -0. To preserve the sign, return the input.     */
        if (x == 0.0F)
            return x;

        /*  For all x < 0, return Not-A-Number.                               */
        return TMPL_NANF;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
        return x;

    /*  Subnormal number or zero.                                             */
    if (TMPL_FLOAT_EXPO_BITS(w) == 0x00U)
    {
        /*  sqrt(0) = 0.0.                                                    */
        if (w.r == 0.0F)
            return x;

        /*  Non-zero subnormal number, normalize it.                          */
        w.r *= TMPL_FLOAT_NORMALIZE;

        /*  The parity is computed by expo mod 2. We have added 23 to the     *
         *  exponent to normalize the input, but 23 mod 2 is 1, not 0. Add 1  *
         *  to expo, and subtract 1 from exponent (in a few lines) to ensure  *
         *  the parity variable is correctly computed.                        */
        w.bits.expo += 1U;

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. To compute the correctly    *
         *  rounded exponent after division by 2, subtract 1 more before      *
         *  dividing. We also added 1 to the exponent above to ensure the     *
         *  parity is correctly computed, so subtract 1 more. In total we     *
         *  subtract 23 + 1 + 1 = 25. Finally, shift by the bias. We have:    *
         *                                                                    *
         *      exponent = 127 - ((127 - expo) + 25) / 2                      *
         *               = 51 + (n + 1) / 2                                   *
         *                                                                    *
         *  Where division, "/", means integer division. Using bit-wise shift *
         *  this is equivalent to:                                            *
         *                                                                    *
         *      exponent = 0x33 + ((n + 1) >> 1)                              *
         *                                                                    *
         *  where 0x33 is 51 in hexidecimal. Compute this.                    */
        exponent = 0x33U + ((w.bits.expo + 0x01U) >> 1U);
    }

    /*  Normal number. Compute the exponent. This is the exponent of the      *
     *  original number divided by 2 since we are taking the square root. A   *
     *  little care is needed to account for the bias. The exponent is        *
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
     *  The bias for 32-bit float is 127, which is not even. However, 128     *
     *  is, so we write:                                                      *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *         = ((E - 1) + (B + 1)) / 2                                      *
     *         = ((E - 1) + 128) / 2                                          *
     *         = (E - 1) / 2 + 64                                             *
     *                                                                        *
     *  Note that we've already checked that E != 0, so E - 1 will not        *
     *  wrap around. That is, E - 1 >= 0. The number 512 is 0x200 in hex.     */
    else
        exponent = ((TMPL_FLOAT_EXPO_BITS(w) - 1U) >> 1U) + 0x40U;

    /*  The parity determines if we scale the final result by sqrt(2) or not. *
     *  This can be determined by the whether or not the exponent is odd.     *
     *  Note that the bias is odd, so exponent - bias changes the parity of   *
     *  the true exponent. That is, if the exponent is 1, which is odd, then  *
     *  the number stored in w.bits.expo is 128 since 128 - 127 = 1. To       *
     *  determine if the exponent is odd, we check if 1 + w.bits.expo is odd. */
    parity = (TMPL_FLOAT_EXPO_BITS(w) + 1U) & 1U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_FLOAT_BIAS;

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
     *  array. man0 is 7 bits wide, we only need this value.                  */
    ind = w.bits.man0;

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    w.r *= tmpl_float_rcpr_table[ind];

    /*  Compute the Remez minimax approximation for sqrt. Peak error 10^-8.   */
    w.r = tmpl_Float_Sqrt_Remez(w.r);

    /*  Get the correctly rounded down integer exponent/2.                    */
    w.bits.expo = exponent & 0xFFU;

    /*  If the exponent is odd, expo/2 is not an integer. Writing expo = 2k+1 *
     *  we have expo/2 = k + 1/2, so 2^{expo/2} = 2^{k+1/2} = 2^{k} * 2^{1/2} *
     *  which is equal to sqrt(2) * 2^{k}. We need to multiply the result by  *
     *  sqrt(2) in the case that exponent is odd. Also, multiply the result   *
     *  sqrt(u/t) by sqrt(t) using the table, giving us sqrt(u).              */
    w.r *= tmpl_float_sqrt_data[parity] * tmpl_float_sqrt_table[ind];

    /*  The Remez polynomial for single precision sqrt is nearly accurate to  *
     *  full single precision, the error is only a few ULP. To get down to    *
     *  1 ULP or less, apply an iteration of Newton's method.                 */
    return 0.5F * (w.r + x / w.r);
}
/*  End of tmpl_Float_Sqrt.                                                   */

#else
/*  Else for TMPL_HAS_IEEE754_FLOAT.                                          */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Pade approximant for sqrt(x) for x near 1.                                */
#include "auxiliary/tmpl_sqrt_rat_remez_float.h"

/*  Function for computing square roots at single precision.                  */
float tmpl_Float_Sqrt(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    signed int expo, parity;
    float mant, out;

    /*  For negatives the output is complex. Return NaN.                      */
    if (x < 0.0F)
        return TMPL_NANF;

    /*  Special case, NaN or inf, simply return the input.                    */
    if (tmpl_Float_Is_NaN_Or_Inf(x) || (x == 0.0F))
        return x;

    /*  Get x into scientific form, x = mant * 2^expo.                        */
    tmpl_Float_Base2_Mant_and_Exp(x, &mant, &expo);

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

    /*  Since 1 <= mant < 2, the Pade approximant can accurately compute sqrt.*/
    out = tmpl_Float_Sqrt_Rat_Remez(mant);

    /*  Since sqrt(m * 2^b) = sqrt(m) * 2^{b/3}, multiply by 2^{b/3}.         */
    return out * tmpl_Float_Pow2(expo) * tmpl_float_sqrt_data[parity];
}
/*  End of tmpl_Float_Sqrt.                                                   */

#endif
/*  End of #if for TMPL_HAS_IEEE754_FLOAT.                                    */

#endif
/*  End of #if for TMPL_USE_MATH_ALGORITHMS.                                  */
