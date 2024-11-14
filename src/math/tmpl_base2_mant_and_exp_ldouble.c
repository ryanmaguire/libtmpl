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
 *                       tmpl_base2_mant_and_exp_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the scientific form of the input. Given x, computes the      *
 *      values m and e such that |x| = m * 2^e with e an integer and          *
 *      1 <= m < 2.                                                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Base2_Mant_and_Exp                                       *
 *  Purpose:                                                                  *
 *      Computes the scientific form of the absolute value of the input.      *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *      mant (long double *):                                                 *
 *          A pointer to the mantissa. The value m in the expression          *
 *          |x| = m * 2^e will be stored here.                                *
 *      expo (signed int *):                                                  *
 *          A pointer to the exponent. The value e in the expression          *
 *          |x| = m * 2^e will be stored here.                                *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Abs (tmpl_math.h):                                   *
 *              Computes the absolute value of a long double.                 *
 *      Method:                                                               *
 *          Extract the exponent by subtracting the bias. Set the exponent    *
 *          part of the input to the bias and return.                         *
 *                                                                            *
 *          Special Cases:                                                    *
 *              NaN or Inf:                                                   *
 *                  Set expo to zero, and mant to +NaN or +Inf, respectively. *
 *              Zero:                                                         *
 *                  Set expo to zero, and mant to +zero.                      *
 *      Error (64-bit double / 80-bit long double / 128-bit quadruple):       *
 *          Based on 631,175,086 random samples.                              *
 *              max mant relative error: 0.000000e+00                         *
 *              rms mant relative error: 0.000000e+00                         *
 *              max mant absolute error: 0.000000e+00                         *
 *              rms mant absolute error: 0.000000e+00                         *
 *              max expo relative error: 0.000000e+00                         *
 *              rms expo relative error: 0.000000e+00                         *
 *              max expo absolute error: 0.000000e+00                         *
 *              rms expo absolute error: 0.000000e+00                         *
 *      Error 128-bit double-double:                                          *
 *          Based on 20,000,000 random samples with 0 < x-1 < 10^-309         *
 *              max mant relative error: 4.940656e-324                        *
 *              rms mant relative error: 0.000000e+00                         *
 *              max mant absolute error: 4.940656e-324                        *
 *              rms mant absolute error: 0.000000e+00                         *
 *              max expo relative error: 0.000000e+00                         *
 *              rms expo relative error: 0.000000e+00                         *
 *              max expo absolute error: 0.000000e+00                         *
 *              rms expo absolute error: 0.000000e+00                         *
 *          Based on 20,000,000 random samples with 10^-200 < x < 10^200      *
 *              max mant relative error: 0.000000e+00                         *
 *              rms mant relative error: 0.000000e+00                         *
 *              max mant absolute error: 0.000000e+00                         *
 *              rms mant absolute error: 0.000000e+00                         *
 *              max expo relative error: 0.000000e+00                         *
 *              rms expo relative error: 0.000000e+00                         *
 *              max expo absolute error: 0.000000e+00                         *
 *              rms expo absolute error: 0.000000e+00                         *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Abs (tmpl_math.h):                                   *
 *              Computes the absolute value of a long double.                 *
 *          tmpl_LDouble_Is_NaN_Or_Inf (tmpl_math.h):                         *
 *              Determines if a long double is NaN or infinity.               *
 *      Method:                                                               *
 *          If |x| < 1, compute with 1/|x|. Otherwise compute with |x|.       *
 *          Iteratively divide the input by certain powers of 2 until we      *
 *          obtain a value between 1 and 2. If the input was original less    *
 *          1, negate the exponent, otherwise we have the correct values.     *
 *                                                                            *
 *          Special Cases:                                                    *
 *              NaN or Inf:                                                   *
 *                  Set expo to zero, and mant to +NaN or +Inf, respectively. *
 *              Zero:                                                         *
 *                  Set expo to zero, and mant to +zero.                      *
 *      Error:                                                                *
 *          Based on 631,175,086 random samples.                              *
 *              max mant relative error: 7.082118e-20                         *
 *              rms mant relative error: 1.583610e-23                         *
 *              max mant absolute error: 1.084202e-19                         *
 *              rms mant absolute error: 2.424350e-23                         *
 *              max expo relative error: 0.000000e+00                         *
 *              rms expo relative error: 0.000000e+00                         *
 *              max expo absolute error: 0.000000e+00                         *
 *              rms expo absolute error: 0.000000e+00                         *
 *  Notes:                                                                    *
 *      The portable method is O(log(log(x))), the IEEE-754 method is O(1).   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 *  2.) float.h:                                                              *
 *          Standard C header file containing limits for long double.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 10, 2022                                              *
 ******************************************************************************/

/*  TMPL_HAS_IEEE754_LDOUBLE macro and function prototype found here.         */
#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we can make this very fast and precise.             */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  64-bit double, 80-bit extended, and 128-bit quadruple implementations     *
 *  of long double use the same idea. Double-double is quite different.       */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *        64-Bit Double / 80-Bit Extended / 128-bit Quadruple Versions        *
 ******************************************************************************/

/*  Function for computing the scientific form of the input. Given x, return  *
 *  the values m and e such that |x| = m * 2^e with 1 <= m < 2.               */
void tmpl_LDouble_Base2_Mant_and_Exp(long double x,
                                     long double *mant,
                                     signed int *expo)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;

    /*  If either of the input pointers are NULL, there's nothing to be done. */
    if (!mant || !expo)
        return;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  Compute the absolute value by setting the sign bit to zero.           */
    w.bits.sign = 0x00U;

    /*  NaN or Inf. Set exponent to zero and mant to the input.               */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
    {
        *mant = w.r;
        *expo = 0;
        return;
    }

    /*  Subnormal or zero.                                                    */
    else if (w.bits.expo == 0x00U)
    {
        /*  x = 0. Set mant to the input and expo to zero.                    */
        if (w.r == 0.0L)
        {
            *mant = w.r;
            *expo = 0;
            return;
        }

        /*  Non-zero subnormal number. Normalize.                             */
        w.r *= TMPL_LDOUBLE_NORMALIZE;

        /*  Compute the exponent by subtracting of the bias.                  */
        *expo = (signed int)(w.bits.expo) - TMPL_LDOUBLE_BIAS;

        /*  Since we normalized, subtract off the appropriate power of two.   */
        *expo = *expo - TMPL_LDOUBLE_MANTISSA_LENGTH;

        /*  Set the exponent bits to the bias, meaning 1 <= w.r < 2.          */
        w.bits.expo = TMPL_LDOUBLE_BIAS;
        *mant = w.r;
        return;
    }

    /*  Normal number that is not NaN or Inf. Compute the exponent by         *
     *  subtracting off the bias.                                             */
    *expo = (signed int)w.bits.expo - TMPL_LDOUBLE_BIAS;

    /*  Set the exponent to zero. Since the exponent is offset by a bias, set *
     *  the expo part of bits to the bias.                                    */
    w.bits.expo = TMPL_LDOUBLE_UBIAS;

    /*  Since the exponent is zero and the sign is zero, we have 1 <= w.r < 2.*
     *  Set the mant value to this and return.                                */
    *mant = w.r;
}
/*  End of tmpl_LDouble_Base2_Mant_and_Exp.                                   */

#else
/*  Else for 64-bit / 80-bit / 128-bit version.                               */

/******************************************************************************
 *                       128-bit Double-Double Version                        *
 ******************************************************************************/

/*  Function for computing the scientific form of the input. Given x, return  *
 *  the values m and e such that |x| = m * 2^e with 1 <= m < 2.               */
void tmpl_LDouble_Base2_Mant_and_Exp(long double x,
                                     long double *mant,
                                     signed int *expo)
{
    /*  Words for the high and low part of the long double.                   */
    tmpl_IEEE754_Double whi, wlo;

    /*  And a word for the long double itself.                                */
    tmpl_IEEE754_LDouble w;

    /*  If either of the input pointers are NULL, there's nothing to be done. */
    if (!mant || !expo)
        return;

    /*  This function computes |x| = m * 2^e, so compute |x|.                 */
    w.r = tmpl_LDouble_Abs(x);

    /*  Extract the hi and low parts of the input.                            */
    whi.r = w.d[0];
    wlo.r = w.d[1];

    /*  Special case, NaN or infinity.                                        */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(whi))
    {
        *expo = 0;
        *mant = w.r;
        return;
    }

    /*  If the high word is subnormal / denormal, the low word must be zero.  */
    else if (whi.bits.expo == 0x00U)
    {
        /*  Special case, the input is zero.                                  */
        if (whi.r == 0.0)
        {
            *mant = w.r;
            *expo = 0;
            return;
        }

        /*  Otherwise, normalize the high word.                               */
        whi.r *= TMPL_DOUBLE_NORMALIZE;

        /*  Compute the exponent by subtracting off the bias.                 */
        *expo = (signed int)(whi.bits.expo) - TMPL_DOUBLE_BIAS;

        /*  Since we normalized the value, subtract off this power of two.    */
        *expo = *expo - TMPL_DOUBLE_MANTISSA_LENGTH;

        /*  Set the exponent bits to the bias. Now 1 <= whi.r < 2.            */
        whi.bits.expo = TMPL_DOUBLE_UBIAS;

        /*  Load the doubles into the long double.                            */
        w.d[0] = whi.r;
        w.d[1] = wlo.r;
        *mant = w.r;
        return;
    }

    /*  If whi expo is much larger than wlo, set low to zero. Maximum         *
     *  relative error this can cause is 10^-308, well below quad precision.  */
    if (whi.bits.expo > wlo.bits.expo + TMPL_DOUBLE_UBIAS)
        wlo.r = 0.0;

    /*  Otherwise, subtract whi's exponent from wlo since we will be setting  *
     *  whi's exponent to the bias later.                                     */
    else
        wlo.bits.expo = (TMPL_DOUBLE_UBIAS + wlo.bits.expo) - whi.bits.expo;

    /*  The exponent can be computed from whi double by subtracting the bias. */
    *expo = (signed int)whi.bits.expo - TMPL_DOUBLE_BIAS;

    /*  Set the exponent bits to the bias. Now 1 <= whi.r < 2.                */
    whi.bits.expo = TMPL_DOUBLE_UBIAS;

    /*  Load the two doubles into the long double and return.                 */
    w.d[0] = whi.r;
    w.d[1] = wlo.r;
    *mant = w.r;
    return;
}
/*  End of tmpl_LDouble_Base2_Mant_and_Exp.                                   */

#endif
/*  End of double-double version.                                             */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/*  Portable method needs the largest power of 10 possible. Found in float.h. */
#include <float.h>

/*  This method does not assume IEEE-754 support, but instead of running in   *
 *  O(1) time, it runs in O(ln(m)), where m is the exponent of the input. So  *
 *  it roughly runs like O(ln(ln(max(|x|, |1/x|)))).                          */
void tmpl_LDouble_Base2_Mant_and_Exp(long double x,
                                     long double *mant,
                                     signed int *expo)
{
    /*  We'll compute the exponent using |x|, so create a variable for this.  */
    long double abs_x;

    /*  If either of the input pointers are NULL, there's nothing to be done. */
    if (!mant || !expo)
        return;

    /*  Zero is a special value, and is represented as 0.0 * 2^0.             */
    if (x == 0.0L)
    {
        *mant = 0.0L;
        *expo = 0;
        return;
    }

    /*  Infinity/NaN are special cases. The mantissa will be set to the       *
     *  absolute value of the input and the exponent will be set to zero.     */
    else if (tmpl_LDouble_Is_NaN_Or_Inf(x))
    {
        *mant = tmpl_LDouble_Abs(x);
        *expo = 0;
        return;
    }

    /*  If we have a non-exceptional case, compute |x|.                       */
    abs_x = tmpl_LDouble_Abs(x);

    /*  If |x| < 1,0, compute with 1/|x|. We'll then negate the exponent at   *
     *  the end of the computation.                                           */
    if (abs_x < 1.0L)
    {
        *mant = 1.0L / abs_x;

        /*  Check if this division caused an overflow.                        */
        if (tmpl_LDouble_Is_Inf(*mant))
        {
            /*  The input is probably subnormal / denormal. There is no good  *
             *  way to handle this portably without IEEE-754 assumptions.     *
             *  Signal this to the caller, set the exponent to -65535. This   *
             *  is much smaller than any of the common representations of     *
             *  float, double, or long double.                                */
            *mant = 1.0L;
            *expo = -65535;
            return;
        }
    }

    /*  If |x| >= 1.0, the exponent is non-negative. No need to invert.       */
    else
        *mant = abs_x;

    /*  Initialize the exponent to zero. The value will be computed by a sum. */
    *expo = 0;

    /*  The exponent is computed via it's binary representation. We find what *
     *  powers of 2 the value is greater than, and then divide by these,      *
     *  which amounts to zeroing out that particular value in the binary      *
     *  expansion of the exponent. Because of this, for values less than      *
     *  10^4932 (which is probably beyond the bounds of long double for       *
     *  your implementation), we can compute the mantissa and exponent in     *
     *  O(ln(ln(x))) time. To avoid compiler warnings about constants beyond  *
     *  the range of double, use the macro LDBL_MAX_10_EXP to check the       *
     *  largest power of 10 allowed.                                          */
#if LDBL_MAX_10_EXP > 4932

    /*  First two hundred digits of 2^16384.                                  */
#define TWO_TO_THE_16384 \
(1.18973149535723176508575932662800713076344468709651023747267482123326135818\
04836869044885954726120399151154374848393092588976673813086874262745246983415\
650060808716343660048975221432516195314468459523E4932L)

    /*  Keep dividing by this power until the exponent is less than 16384.    */
    while (*mant >= TWO_TO_THE_16384)
    {
        *mant /= TWO_TO_THE_16384;
        *expo += 16384;
    }

    /*  Undefine this macro in case someone wants to #include this file.      */
#undef TWO_TO_THE_16384

#endif
/*  End of #if LDBL_MAX_10_EXP > 4932.                                        */

    /*  Same idea for 2^8192.                                                 */
#if LDBL_MAX_10_EXP > 2466

    /*  First two hundred digits of 2^8192.                                   */
#define TWO_TO_THE_8192 \
(1.09074813561941592946298424473378286244826416199623269243183278618972133184\
91192952162642345252019872239572917961570252731098708201771840636109797650775\
547990789062988421929895386098252280482051596969E2466L)

    /*  Keep dividing by this power until the exponent is less than 8192.     */
    while (*mant >= TWO_TO_THE_8192)
    {
        *mant /= TWO_TO_THE_8192;
        *expo += 8192;
    }

    /*  Undefine this macro in case someone wants to #include this file.      */
#undef TWO_TO_THE_8192

#endif
/*  End of #if LDBL_MAX_10_EXP > 2466.                                        */

    /*  Same idea for 2^4096.                                                 */
#if LDBL_MAX_10_EXP > 1233

    /*  First two hundred digits of 2^4096.                                   */
#define TWO_TO_THE_4096 \
(1.04438888141315250669175271071662438257996424904738378038423348328395390797\
15574568488268119349975583408901067144392628379875734381857936072632360878513\
652779459569765437099983403615901343837183144281E1233L)

    /*  Keep dividing by this power until the exponent is less than 4096.     */
    while (*mant >= TWO_TO_THE_4096)
    {
        *mant /= TWO_TO_THE_4096;
        *expo += 4096;
    }

    /*  Undefine this macro in case someone wants to #include this file.      */
#undef TWO_TO_THE_4096

#endif
/*  End of #if LDBL_MAX_10_EXP > 1233.                                        */

    /*  Same idea for 2^2048.                                                 */
#if LDBL_MAX_10_EXP > 616

    /*  First two hundred digits of 2^2048.                                   */
#define TWO_TO_THE_2048 \
(3.2317006071311007300714876688669951960444102669715484032130345427524655138\
8678908931972014115229134636887179609218980194941195591504909210950881523864\
48283120630877367300996091750197750389652106796058E616L)

    /*  Keep dividing by this power until the exponent is less than 2048.     */
    while (*mant >= TWO_TO_THE_2048)
    {
        *mant /= TWO_TO_THE_2048;
        *expo += 2048;
    }

    /*  Undefine this macro in case someone wants to #include this file.      */
#undef TWO_TO_THE_2048

#endif
/*  End of #if LDBL_MAX_10_EXP > 616.                                         */

    /*  Same idea for 2^1024.                                                 */
#if LDBL_MAX_10_EXP > 308

    /*  First two hundred digits of 2^1024.                                   */
#define TWO_TO_THE_1024 \
(1.7976931348623159077293051907890247336179769789423065727343008115773267580\
5500963132708477322407536021120113879871393357658789768814416622492847430639\
47412437776789342486548527630221960124609411945308E308L)

    /*  Keep dividing by this power until the exponent is less than 1024.     */
    while (*mant >= TWO_TO_THE_1024)
    {
        *mant /= TWO_TO_THE_1024;
        *expo += 1024;
    }

    /*  Undefine this macro in case someone wants to #include this file.      */
#undef TWO_TO_THE_1024

#endif
/*  End of #if LDBL_MAX_10_EXP > 308.                                         */

    /*  Same idea for 2^512.                                                  */
#if LDBL_MAX_10_EXP > 512

    /*  Portable version, we don't know how exactly a double is represented.  *
     *  The following is all digits of 2^512. This is probably overkill.      */
#define TWO_TO_THE_512 \
(1.3407807929942597099574024998205846127479365820592393377723561443\
721764030073546976801874298166903427690031858186486050853753882811\
946569946433649006084096E+154L)

    /*  Keep dividing by this power until the exponent is less than 512.      */
    while (*mant >= TWO_TO_THE_512)
    {
        *mant /= TWO_TO_THE_512;
        *expo += 512;
    }

    /*  Undefine this macro in case someone wants to #include this file.      */
#undef TWO_TO_THE_512

#endif
/*  End of #if LDBL_MAX_10_EXP > 154.                                         */

    /*  Same idea but for 2^256.                                              */
#if LDBL_MAX_10_EXP > 77

    /*  The following macro is all digits of 2^256.                           */
#define \
TWO_TO_THE_256 \
(1.1579208923731619542357098500868\
7907853269984665640564039457584007913129639936E+77L)

    /*  Keep dividing by this power until the exponent is less than 256.      */
    while (*mant >= TWO_TO_THE_256)
    {
        *mant /= TWO_TO_THE_256;
        *expo += 256;
    }

    /*  Undefine this macro in case someone wants to #include this file.      */
#undef TWO_TO_THE_256

#endif
/*  End of #if LDBL_MAX_10_EXP > 77.                                          */

    /*  Same idea for 2^128.                                                  */
#if LDBL_MAX_10_EXP > 38

    /*  The following macro is all digits of 2^128.                           */
#define TWO_TO_THE_128 (3.40282366920938463463374607431768211456E+38L)

    /*  Keep dividing by this power until the exponent is less than 128.      */
    while (*mant >= TWO_TO_THE_128)
    {
        *mant /= TWO_TO_THE_128;
        *expo += 128;
    }

    /*  Undefine this macro in case someone wants to #include this file.      */
#undef TWO_TO_THE_128

#endif
/*  End of #if LDBL_MAX_10_EXP > 38.                                          */

    /*  Same idea for 2^64.                                                   */
#if LDBL_MAX_10_EXP > 19

    /*  THe following is all digits of 2^64.                                  */
#define TWO_TO_THE_64 (1.8446744073709551616E+19L)

    /*  Keep dividing by this power until the exponent is less than 64.       */
    while (*mant >= TWO_TO_THE_64)
    {
        *mant /= TWO_TO_THE_64;
        *expo += 64;
    }

    /*  Undefine this macro in case someone wants to #include this file.      */
#undef TWO_TO_THE_64

#endif
/*  End of #if LDBL_MAX_10_EXP > 19.                                          */

    /*  Same idea for 2^32.                                                   */
#if LDBL_MAX_10_EXP > 9

    /*  The following macro is 2^32 to all digits.                            */
#define TWO_TO_THE_32 (4.294967296E+09L)
    while (*mant >= TWO_TO_THE_32)
    {
        *mant /= TWO_TO_THE_32;
        *expo += 32;
    }

    /*  Undefine this macro in case someone wants to #include this file.      */
#undef TWO_TO_THE_32

#endif
/*  End of #if LDBL_MAX_10_EXP > 9.                                           */

    /*  The following values are small enough that any implementation of      *
     *  double should be able to achieve them.                                */
    while (*mant >= 65536.0L)
    {
        *mant /= 65536.0L;
        *expo += 16;
    }

    if (*mant >= 256.0L)
    {
        *mant /= 256.0L;
        *expo += 8;
    }

    if (*mant >= 16.0L)
    {
        *mant /= 16.0L;
        *expo += 4;
    }

    if (*mant >= 4.0L)
    {
        *mant /= 4.0L;
        *expo += 2;
    }

    if (*mant >= 2.0L)
    {
        *mant /= 2.0L;
        *expo += 1;
    }

    /*  If |x| < 1, we need to negate the exponent since we computed the      *
     *  exponent of 1 / |x|. We also need to set mant to 1 / mant. This will  *
     *  result in mant < 1, so multiply by 2 and subtract 1 from the          *
     *  exponent. This will give us the correct value 1.m * 2^b.              */
    if (abs_x < 1.0L)
    {
        /*  Special case, if mant = 1, no need to subtract 1 or compute       *
         *  the reciprocal of mant. Just negate the exponent.                 */
        if (*mant == 1.0L)
            *expo = -*expo;
        else
        {
            *expo = -*expo - 1;
            *mant = 2.0L / *mant;
        }
    }
}
/*  End of tmpl_LDouble_Base2_Mant_and_Exp.                                   */

#endif
/*  End #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                    */
