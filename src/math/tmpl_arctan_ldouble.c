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
 *                            tmpl_arctan_ldouble                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-tangent function at long double precision.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arctan                                                   *
 *  Purpose:                                                                  *
 *      Computes atan(x), the inverse tangent function.                       *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (long double):                                                 *
 *          The arc-tangent of x.                                             *
 *  64-Bit Double / 80-Bit Extended Version:                                  *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Abs (tmpl_math.h):                                   *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_LDouble_Arctan_Asymptotic (tmpl_math.h):                     *
 *              Computes the asymptotic expansion of arctan for large         *
 *              positive real numbers. Very accurate for x > 16.              *
 *          tmpl_LDouble_Arctan_Maclaurin (tmpl_math.h):                      *
 *              Computes the Maclaurin series of arctan. More terms are used  *
 *              in this function than tmpl_Double_Arctan_Very_Small.          *
 *          tmpl_LDouble_Arctan_Very_Small (tmpl_math.h):                     *
 *              Computes the inverse tangent of small numbers using a         *
 *              Maclaurin series. Accurate for values smaller than 1/32.      *
 *      Method:                                                               *
 *          Check if the input is is NaN or infinity. Return NaN if it is     *
 *          NaN, and sign(x) * pi / 2 if it is +/- infinity.                  *
 *                                                                            *
 *          Next, use the fact that atan(x) is odd to reduce to the case      *
 *          x >= 0. For small values, use the MacLaurin series. For values in *
 *          certain ranges, use formula 4.4.34 from Abramowitz and Stegun to  *
 *          reduce the argument to a smaller value. This formula states that: *
 *                                                                            *
 *                                         u - v                              *
 *              atan(u) - atan(v) = atan( -------- )                          *
 *                                         1 + uv                             *
 *                                                                            *
 *          Extract the exponent of the input x. That is, given:              *
 *                                                                            *
 *              x = s * 1.m * 2^e                                             *
 *                                                                            *
 *          where s is the sign, m the mantissa, and e the exponent, extract  *
 *          the value e. Precompute 8 values of atan(v) and use the value e   *
 *          to index this list (e varies from -4 to 3, corresponding to 1/16  *
 *          to 8). For e < -4 we have |x| < 1/16, so use the MacLaurin        *
 *          series. For e > 3 we have |x| >= 16, so use the asymptotic        *
 *          expansion). Values of |x| lying between 2^e and 2^{e+1} will use  *
 *          these precomputed values in the formula above from Abramowitz and *
 *          Stegun. Because of this we can skip most of the if-then           *
 *          statements used in the portable method.                           *
 *                                                                            *
 *          The following values were obtained via guess-and-check to reduce  *
 *          the relative error to below 2 * 10^-16 ~= 2^-52 = double epsilon. *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *          x in [0.0, 1/16) u = x, v = 0.05, reduce and use polynomial.      *
 *          x in [1/16, 1/8) u = x, v = 0.18, reduce and use polynomial.      *
 *          x in [1/8, 1/4)  u = x, v = 0.35, reduce and use polynomial.      *
 *          x in [1/4, 1/2)  u = x, v = 0.72, reduce and use polynomial.      *
 *          x in [1/2, 1)    u = x, v = 1.35, reduce and use polynomial.      *
 *          x in [1, 2)      u = x, v = 2.50, reduce and use polynomial.      *
 *          x in [2, 4)      u = x, v = 4.00, reduce and use polynomial.      *
 *          x in [4, 8)      u = x, v = 8.00, reduce and use polynomial.      *
 *          x >= 8           atan(x) ~= pi/2 + atan(-1/x).                    *
 *      Error (64-Bit Double):                                                *
 *          Based on 2,248,163,737 random samples with -10^6 < x < 10^6.      *
 *              max relative error: 2.3223344540012894e-16                    *
 *              rms relative error: 7.4233764024303319e-17                    *
 *              max absolute error: 2.2204460492503131e-16                    *
 *              rms absolute error: 1.1660491924987274e-16                    *
 *          Values assume 100% accuracy of glibc. Actually error in glibc is  *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *      Error (64-Bit Double):                                                *
 *          Based on 1,124,081,868 random samples with -10^6 < x < 10^6.       *
 *              max relative error: 1.0760955259629269e-19                    *
 *              rms relative error: 3.4510708882926869e-20                    *
 *              max absolute error: 1.0842021724855044e-19                    *
 *              rms absolute error: 5.4208785603818807e-20                    *
 *          Values assume 100% accuracy of glibc. Actually error in glibc is  *
 *          less than 1 ULP (~1 x 10^-19).                                    *
 *  128-Bit Quadruple / 128-Bit Double-Double:                                *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Abs (tmpl_math.h):                                   *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_LDouble_Arctan_Pade (tmpl_math.h):                           *
 *              Compute the Pade approximant for atan. Very accurate for      *
 *              small values. Used to get relative error to ~10^-34.          *
 *      Method:                                                               *
 *          Similar to double / extended method, but with a large lookup      *
 *          table and using the Pade approximant instead of Maclaurin series. *
 *      Error (128-Bit Quadruple):                                            *
 *          Based on 25,000,000 random samples with -10^6 < x < 10^6.         *
 *              max relative error: 1.7473101468321921e-34                    *
 *              rms relative error: 5.2509800591011004e-35                    *
 *              max absolute error: 3.8518598887744717e-34                    *
 *              rms absolute error: 1.0894746550053625e-34                    *
 *          Values assume 100% accuracy of glibc. Actually error in glibc is  *
 *          less than 1 ULP (~2 x 10^-34).                                    *
 *      Error (128-Bit Double-Double):                                        *
 *          Based on 25,000,000 random samples with -10^6 < x < 10^6.         *
 *              max relative error: 1.5693901271014608e-32                    *
 *              rms relative error: 4.0465499798622827e-33                    *
 *              max absolute error: 2.4651903288156619e-32                    *
 *              rms absolute error: 6.3562982935323872e-33                    *
 *          Values assume 100% accuracy of glibc. Comments for their          *
 *          double-double implementation claim the peak error is 1.7 x 10^-34.*
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Abs (tmpl_math.h):                                   *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_LDouble_Arctan_Asymptotic (tmpl_math.h):                     *
 *              Computes the asymptotic expansion of arctan for large         *
 *              positive real numbers. Very accurate for x > 16.              *
 *          tmpl_LDouble_Arctan_Maclaurin (tmpl_math.h):                      *
 *              Computes the Maclaurin series of arctan. More terms are used  *
 *              in this function than tmpl_Double_Arctan_Very_Small.          *
 *          tmpl_LDouble_Arctan_Very_Small (tmpl_math.h):                     *
 *              Computes the inverse tangent of small numbers using a         *
 *              Maclaurin series. Accurate for values smaller than 1/32.      *
 *          tmpl_LDouble_Is_NaN (tmpl_math.h):                                *
 *              Determines if a double is Not-a-Number.                       *
 *          tmpl_LDouble_Is_Inf (tmpl_math.h):                                *
 *              Determines if a double is infinity.                           *
 *      Method:                                                               *
 *          Same double / extended but use if-then statements to narrow       *
 *          the range of x and use the appropriate values in the table.       *
 *      Error:                                                                *
 *          Based on 788,968,857 random samples with -10^6 < x < 10^6.        *
 *              max relative error: 2.3223344540012894e-16                    *
 *              rms relative error: 7.4233764024303319e-17                    *
 *              max absolute error: 2.2204460492503131e-16                    *
 *              rms absolute error: 1.1660491924987274e-16                    *
 *          Values assume 100% accuracy of glibc. Actually error in glibc is  *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *  Notes:                                                                    *
 *      There are three special cases. If the input is NaN, the output will   *
 *      also be NaN. If the input is positive infinity, the limit is used and *
 *      pi/2 is returned. If the input is negative infinity, the limit is     *
 *      used and -pi/2 is returned.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 *  3.) tmpl_math_arctan_double_tables.h:                                     *
 *          Header file containing pre-computed values of arctan(x).          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 19, 2022                                              *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototypes found here.                                           */
#include <libtmpl/include/tmpl_math.h>

/*  Lookup tables are found here.                                             */
#include <libtmpl/include/math/tmpl_math_arctan_ldouble_tables.h>

/*  Check for IEEE-754 long double support.                                   */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  64-bit / 80-bit long double uses the same idea as 64-bit double.          */
#if \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN            || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN               || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN   || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN      || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN  || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN

/******************************************************************************
 *                          64 BIT DOUBLE PRECISION                           *
 *                                    and                                     *
 *                         80 BIT EXTENDED PRECISION                          *
 ******************************************************************************/

/*  Long double precision inverse tangent (atanl equivalent).                 */
long double tmpl_LDouble_Arctan(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;
    long double arg, out, v, atan_v;
    unsigned int ind;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if (TMPL_LDOUBLE_IS_NAN(w))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (TMPL_LDOUBLE_IS_NEGATIVE(w))
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Small values, |x| < 1/32. Use the MacLaurin series to a few terms.    */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 4U)
    {
        /*  For very small values avoid underflow and return the first term   *
         *  of the Maclaurin series, which is just the input.                 */
        if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 52U)
            return x;
        else
            return tmpl_LDouble_Arctan_Very_Small(x);
    }

    /*  The arctan function is odd. Compute |x| and work with that.           */
    w.r = tmpl_LDouble_Abs(w.r);

    /*  For |x| > 16, use the asymptotic expansion.                           */
    if (TMPL_LDOUBLE_EXPO_BITS(w) > TMPL_LDOUBLE_BIAS + 3U)
    {
        out = tmpl_LDouble_Arctan_Asymptotic(w.r);

        /*  Use the fact that atan is odd to complete the computation.        */
        if (x < 0.0L)
            return -out;
        else
            return out;
    }

    /*  The exponent tells us the index for the tables tmpl_atan_ldouble_v and*
     *  tmpl_atan_ldouble_atan_of_v that correspond to x. The index is simply *
     *  the exponent plus four (since the lowest value is 1/16 = 2^-4, we     *
     *  need to shift up by 4). The exponent has a bias, per the IEEE-754     *
     *  format, so we must subtract this off to get the correct index.        */
    ind = (TMPL_LDOUBLE_EXPO_BITS(w) + 4U) - TMPL_LDOUBLE_UBIAS;
    v = tmpl_atan_ldouble_v[ind];
    atan_v = tmpl_atan_ldouble_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (w.r - v) / (1.0L + w.r*v);
    out = atan_v + tmpl_LDouble_Arctan_Maclaurin(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    if (x < 0.0L)
        return -out;
    else
        return out;
}
/*  End of tmpl_LDouble_Arctan.                                               */

#else
/*  Else for 64-bit double and 80-bit extended precision methods.             */

/******************************************************************************
 *                        128 BIT QUADRUPLE PRECISION                         *
 *                                    and                                     *
 *                      128 BIT DOUBLE-DOUBLE PRECISION                       *
 ******************************************************************************/

/*  To get quadruple or double-double precision, the Taylor series is too     *
 *  slow. Instead, the Pade approximant is used after reducing the argument.  */

/*  Long double precision inverse tangent (atanl equivalent).                 */
long double tmpl_LDouble_Arctan(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;
    long double out, t;
    unsigned int n;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if (TMPL_LDOUBLE_IS_NAN(w))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (TMPL_LDOUBLE_IS_NEGATIVE(w))
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Avoid underflow. If |x| < 2^-56, atan(x) = x to quadruple precision.  */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 56U)
        return x;

    /*  The arctan function is odd. Compute |x| and work with that.           */
    w.r = tmpl_LDouble_Abs(w.r);

    /*  For |x| > 16, use the asymptotic expansion.                           */
    if (TMPL_LDOUBLE_EXPO_BITS(w) > TMPL_LDOUBLE_UBIAS + 3U)
        out = tmpl_Pi_By_Two_L - tmpl_LDouble_Arctan_Pade(1.0L/w.r);
    else
    {
        n = (unsigned int)(8.0L*w.r + 0.25L);
        t = 0.125L * (long double)n;
        t = (w.r - t) / (1.0L + w.r*t);
        out = tmpl_ldouble_atan_n_by_8[n] + tmpl_LDouble_Arctan_Pade(t);
    }

    if (x < 0.0L)
        return -out;
    else
        return out;
}
/*  End of tmpl_LDouble_Arctan.                                               */

#endif
/*  End of double/extended precision vs quadruple/double-double precision.    */

#else
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Long double precision inverse tangent (atanl equivalent).                 */
long double tmpl_LDouble_Arctan(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double abs_x, arg, out, v, atan_v;
    unsigned int ind;

    /*  Special cases, NaN and INF.                                           */
    if (tmpl_LDouble_Is_NaN(x))
        return x;
    else if (tmpl_LDouble_Is_Inf(x))
        return (x < 0.0L ? -tmpl_Pi_By_Two_L : tmpl_Pi_By_Two_L);

    abs_x = tmpl_LDouble_Abs(x);

    /*  Small values, |x| < 1/16. Use the MacLaurin series to a few terms.    */
    if (abs_x < 0.0625L)
        return tmpl_LDouble_Arctan_Very_Small(x);
    else if (abs_x < 0.125L)
        ind = 0U;
    else if (abs_x < 0.25L)
        ind = 1U;
    else if (abs_x < 0.5L)
        ind = 2U;
    else if (abs_x < 1.0L)
        ind = 3U;
    else if (abs_x < 2.0L)
        ind = 4U;
    else if (abs_x < 4.0L)
        ind = 5U;
    else if (abs_x < 8.0L)
        ind = 6U;
    else if (abs_x < 16.0L)
        ind = 7U;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    else
    {
        out = tmpl_LDouble_Arctan_Asymptotic(abs_x);
        return (x < 0.0L ? -out : out);
    }

    v = tmpl_atan_ldouble_v[ind];
    atan_v = tmpl_atan_ldouble_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (abs_x - v) / (1.0L + abs_x*v);
    out = atan_v + tmpl_LDouble_Arctan_Maclaurin(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    return (x < 0.0L ? -out : out);
}
#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
