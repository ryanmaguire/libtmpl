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
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_cbrt_remez_double.h                                          *
 *              tmpl_Double_Cbrt_Remez:                                       *
 *                  Computes a Remez minimax approximation of cbrt near x = 1.*
 *      Method:                                                               *
 *          Use a combination of cube root rules, polynomials, and Newton's   *
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
 *          We can chop off the cubic term if we use a Remez approximation,   *
 *          instead of the Taylor expansion, and still attain the same        *
 *          precision. The Remez coefficients differ slightly from the Taylor *
 *          coefficients.                                                     *
 *                                                                            *
 *          y is now accurate to at least 8 decimals. We can double this to   *
 *          16 decimals using 1 iteration of Newton's method. We have:        *
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
 *      Error:                                                                *
 *          Based on 1,051,958,476 samples with -10^6 < x < 10^6.             *
 *              max rel error: 7.0469763017409916e-16                         *
 *              rms rel error: 1.5775644974028550e-16                         *
 *              max abs error: 1.4210854715202004e-14                         *
 *              rms abs error: 2.6790772954468324e-15                         *
 *          Error values assume 100% accuracy in glibc. Actual accuracy is    *
 *          around 1-2 ULP.                                                   *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_cbrt_pade_double.h:                                          *
 *              tmpl_Double_Cbrt_Pade:                                        *
 *                  Computes a Pade approximant of cbrt near x = 1.           *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Is_NaN_Or_Inf:                                    *
 *                  Determines if a double is NaN or infinity.                *
 *              tmpl_Double_Base2_Mant_and_Exp:                               *
 *                  Gets the input into scientific form, |x| = m * 2^b with   *
 *                  1 <= m < 2 and b an integer.                              *
 *              tmpl_Double_Pow2:                                             *
 *                  Quickly computes an integer power of 2 as a double.       *
 *      Method:                                                               *
 *          Reduce to x >= 0 since cbrt is an odd function. Convert x to      *
 *          scientific notation x = m * 2^b with 1 <= m < 2 and b an integer. *
 *          Use the Pade approximant on m and multiply by 2^{b/3}. Finish by  *
 *          performing one iteration of Newton's method.                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 *  2.) tmpl_cbrt_remez_double.h:                                             *
 *          Used in the IEEE-754 version. Remez approximation for cbrt.       *
 *  3.) tmpl_cbrt_pade_double.h:                                              *
 *          Used in the portable version. Pade approximant for cbrt.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 22, 2022                                             *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Newton's method has a divide-by-three in the expression.                  */
#define ONE_THIRD (3.3333333333333333333333333333333E-01)

/*  The values 2^{0/3}, 2^{1/3}, and 2^{2/3}.                                 */
static const double tmpl_double_cbrt_data[3] = {
    1.0000000000000000000000000000000E+00,
    1.2599210498948731647672106072782E+00,
    1.5874010519681994747517056392722E+00
};

/*  Check for IEEE-754 support. This is significantly faster.                 */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Remez approximation provided here.                                        */
#include <libtmpl/include/math/tmpl_cbrt_remez_double.h>

/*  Table of pre-computed values for the cbrt function.                       */
#include <libtmpl/include/math/tmpl_cbrt_table_double.h>

/*  Function for computing cube roots at double precision.                    */
double tmpl_Double_Cbrt(double x)
{
    /*  Union of a double and the bits representing a double.                 */
    tmpl_IEEE754_Double w, tmp;

    /*  Integer for indexing the pre-computed cube root array.                */
    unsigned int ind;

    /*  The exponent part of the output.                                      */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 3.                              */
    unsigned int parity;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Save the sign of x by copying w into tmp.                             */
    tmp.bits.sign = w.bits.sign;

    /*  cbrt is an odd function. If x is negative, compute -cbrt(-x).         */
    w.bits.sign = 0x00U;

    /*  Subnormal number or zero.                                             */
    if (w.bits.expo == 0x00U)
    {
        /*  cbrt(0) = 0.0.                                                    */
        if (w.r == 0.0)
            return x;

        /*  Non-zero subnormal number. Normalize the input.                   */
        w.r *= TMPL_DOUBLE_NORMALIZE;

        /*  The parity is computed by expo mod 3. We have added 52 to the     *
         *  exponent to normalize the input, but 52 mod 2 is 1, not 0. Add 2  *
         *  to expo, and subtract 2 from exponent (in a few lines) to ensure  *
         *  the parity variable is correctly computed.                        */
        w.bits.expo += 2U;

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. We also added 2 to expo, so *
         *  subtract 2 more. To compute the correctly rounded exponent after  *
         *  division by 3, subtract 2 more before dividing. The total is      *
         *  subtracting 4 and the power of two. This power of two is          *
         *  the macro TMPL_DOUBLE_MANTISSA_ULENGTH, which evaluates to 52, so *
         *  in total we need to subtract 56. Finally, shift by the bias.      */
        exponent = TMPL_DOUBLE_UBIAS - ((TMPL_DOUBLE_UBIAS-w.bits.expo)+56U)/3U;
    }

    /*  NaN or infinity. Return the input.                                    */
    else if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
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
     *  The bias for 64-bit double is 1023, so 2*1023 / 3 = 682. This is      *
     *  0x2AA in hexidecimal. We compute the exponent using this.             */
    else
        exponent = 0x2AAU + w.bits.expo / 3U;

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
     *  array. man0 is 4 bits wide, so we need this and the first 3 bits of   *
     *  man1, the next part of the mantissa.                                  */
    ind = w.bits.man0;

    /*  Obtain the last 3 bits of man1 by shifting down 13 bits. man1 is 16   *
     *  bits wide.                                                            */
    ind = (ind << 3U) + (w.bits.man1 >> 13U);

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    w.r = w.r*tmpl_double_rcpr_table[ind];

    /*  Compute the Remez minimax approximation for cbrt. Peak error 10^-9.   */
    w.r = tmpl_Double_Cbrt_Remez(w.r);

    /*  Get the correctly rounded down integer exponent/3.                    */
    w.bits.expo = exponent & 0x7FFU;

    /*  Compute 2^{b/3} * cbrt(t) using the two tables.                       */
    w.r *= tmpl_double_cbrt_data[parity]*tmpl_double_cbrt_table[ind];

    /*  tmp still has the original sign of x. Copy this to the output.        */
    w.bits.sign = tmp.bits.sign;

    /*  Apply 1 iteration of Newton's method and return.                      */
    return ONE_THIRD*(2.0*w.r + x/(w.r*w.r));
}
/*  End of tmpl_Double_Cbrt.                                                  */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Pade approximant provided here.                                           */
#include <libtmpl/include/math/tmpl_cbrt_pade_double.h>

/*  Function for computing cube roots at double precision.                    */
double tmpl_Double_Cbrt(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    signed int expo, parity;
    double mant, out;

    /*  Special case, NaN or inf, simply return the input.                    */
    if (tmpl_Double_Is_NaN_Or_Inf(x))
        return x;

    /*  Get x into scientific form, |x| = mant * 2^expo.                      */
    tmpl_Double_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  Negative exponent, compute the parity which must be positive.         */
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
        expo = expo / 3;
    }

    /*  Since 1 <= mant < 2, the Pade approximant can accurately compute cbrt.*/
    out = tmpl_Double_Cbrt_Pade(mant);

    /*  Since cbrt(m * 2^b) = cbrt(m) * 2^{b/3}, multiply by 2^{b/3}.         */
    out = out*tmpl_Double_Pow2(expo)*tmpl_double_cbrt_data[parity];

    /*  cbrt is an odd function. If the input was negative, negate the output.*/
    if (x < 0.0)
        out = -out;

    /*  Apply 1 iteration of Newton's method and return.                      */
    return ONE_THIRD*(2.0*out + x/(out*out));
}
/*  End of tmpl_Double_Cbrt.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef ONE_THIRD

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
