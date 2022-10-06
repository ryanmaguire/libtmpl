/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototypes found here.                                           */
#include <libtmpl/include/tmpl_math.h>

/*  Lookup tables are found here.                                             */
#include <libtmpl/include/math/tmpl_math_arctan_tables.h>

/*  Check for IEEE-754 long double support.                                   */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/******************************************************************************
 *                          64 BIT DOUBLE PRECISION                           *
 *                                    and                                     *
 *                         80 BIT EXTENDED PRECISION                          *
 ******************************************************************************/

#if \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN            || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN               || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN   || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN      || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN  || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN

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
    if (w.bits.expo == TMPL_LDOUBLE_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if (w.bits.man0 || w.bits.man1 || w.bits.man2 || w.bits.man3)
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Small values, |x| < 1/32. Use the MacLaurin series to a few terms.    */
    else if (w.bits.expo < TMPL_LDOUBLE_BIAS - 4U)
    {
        /*  For very small values avoid underflow and return the first term   *
         *  of the Maclaurin series, which is just the input.                 */
        if (w.bits.expo < TMPL_LDOUBLE_BIAS - 52U)
            return x;
        else
            return tmpl_LDouble_Arctan_Very_Small(x);
    }

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.sign = 0x00U;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    if (w.bits.expo > TMPL_LDOUBLE_BIAS + 3U)
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
    ind = (w.bits.expo + 4U) - TMPL_LDOUBLE_BIAS;
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

/******************************************************************************
 *                        128 BIT QUADRUPLE PRECISION                         *
 *                                    and                                     *
 *                      128 BIT DOUBLE-DOUBLE PRECISION                       *
 ******************************************************************************/

#else

/*  The only difference in the code for quadruple and double-double precision *
 *  is how the bits of a long double are extracted.                           */
#if \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

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
    if (w.bits.expo == TMPL_LDOUBLE_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if ((w.bits.man0 != 0x0U || w.bits.man1 != 0x0U))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Avoid underflow. If |x| < 2^-52, atan(x) = x to quadruple precision.  */
    else if (w.bits.expo < TMPL_LDOUBLE_BIAS - 52U)
        return x;

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.sign = 0x00U;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    if (w.bits.expo > TMPL_LDOUBLE_BIAS + 3U)
    {
        out = tmpl_Pi_By_Two_L - tmpl_LDouble_Arctan_Pade(1.0L/w.r);
        return (x < 0.0L ? -out : out);
    }

    n = (unsigned int)(8.0L*w.r + 0.25L);
    t = 0.125L * (long double)n;
    t = (w.r - t) / (1.0L + w.r*t);
    out = tmpl_ldouble_atan_n_by_8[n] + tmpl_LDouble_Arctan_Pade(t);
    return (x < 0.0L ? -out : out);
}
/*  End of tmpl_LDouble_Arctan.                                               */

#else
/*  This part is for double-double precision.                                 */

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
    if (w.bits.expoa == TMPL_LDOUBLE_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if ((w.bits.man0a != 0x0U || w.bits.man1a != 0x0U))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.signa)
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Avoid underflow. If |x| < 2^-52, atan(x) = x to quadruple precision.  */
    else if (w.bits.expoa < TMPL_LDOUBLE_BIAS - 52U)
        return x;

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.signb = w.bits.signa ^ w.bits.signb;
    w.bits.signa = 0x0U;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    if (w.bits.expoa > TMPL_LDOUBLE_BIAS + 3U)
    {
        out = tmpl_Pi_By_Two_L - tmpl_LDouble_Arctan_Pade(1.0L/w.r);
        return (x < 0.0L ? -out : out);
    }

    n = (unsigned int)(8.0L*w.r + 0.25L);
    t = 0.125L * (long double)n;
    t = (w.r - t) / (1.0L + w.r*t);
    out = tmpl_ldouble_atan_n_by_8[n] + tmpl_LDouble_Arctan_Pade(t);
    return (x < 0.0L ? -out : out);
}
/*  End of tmpl_LDouble_Arctan.                                               */

#endif
/*  End of difference between double-double and quadruple precisions.         */

#endif
/*  End of double/extended precision vs quadruple/double-double precision.    */

#else
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

/*  Portable algorithm that does not use IEEE-754 tricks.                     */

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
