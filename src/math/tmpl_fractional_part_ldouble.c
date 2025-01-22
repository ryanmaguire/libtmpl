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
 *                        tmpl_fractional_part_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the truncation of x. This is the input minus the fractional  *
 *      part, which is equivalent to rounding-to-zero.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Fractional_Part                                          *
 *  Purpose:                                                                  *
 *      Rounds a long double towards zero, removing the fractional part.      *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      trunc_x (long double):                                                *
 *          The truncation of x.                                              *
 *  Double / Extended / Quadruple with 64-Bit Integers:                       *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          If we can use 64-bit integers for type punning, we do the         *
 *          following. A 64-bit IEEE-754 double is represented as follows:    *
 *                                                                            *
 *                s eeeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxx ...             *
 *                - ----------- ---------------------------------             *
 *              sign exponent                mantissa                         *
 *                                                                            *
 *          Where there is 1 s, 11 e's, and 52 x's. The true exponent is the  *
 *          exponent component (written in binary) minus the bias, which is   *
 *          1023. That is:                                                    *
 *                                                                            *
 *              exponent = eeeeeeeeeee_2 - 1023                               *
 *                                                                            *
 *          Extended (80-bits) and quadruple (128-bits) are handled similarly,*
 *          albeit with a different number of exponent bits and mantissa bits,*
 *          and also a different bias. We have:                               *
 *                                                                            *
 *              Type      | Exponent | Mantissa |  Bias                       *
 *              ---------------------------------------                       *
 *              double    |       11 |       52 |  1023                       *
 *              extended  |       15 |       63 | 16383                       *
 *              quadruple |       15 |      112 | 16383                       *
 *                                                                            *
 *          The algorithm goes as follows. First, special cases.              *
 *              If x is NaN or infinity, return x.                            *
 *              If |x| < 1 (meaning exponent < 0), return 0.                  *
 *          For the general case, compute the exponent, and then zero out     *
 *          the last "exponent" bits of the mantissa. This is equivalent to   *
 *          setting the fractional part of the input to zero, meaning it is   *
 *          now an integer value. We could do this by creating a bit-mask of  *
 *          1's, and then "bit-shift" up by "exponent" number of bits.        *
 *          This makes the bottom "exponent" bits equal to zero. We could     *
 *          then perform bit-wise-and with the input to zero out the          *
 *          fractional bits of the number.                                    *
 *                                                                            *
 *          It makes the computation a little easier to actually create a     *
 *          bit-mask of all 1's for the fractional bits, and 0's for every    *
 *          other bit. We then flip this (0's for the fractional bits and 1's *
 *          for the other bits) using bit-wise-complement. In doing so we can *
 *          easily check if the input is already an integer, potentially      *
 *          skipping some redundant computations.                             *
 *                                                                            *
 *          For 128-bit quadruple we need to use two 64-bit integers since    *
 *          the 112-bit mantissa will not fit into a single 64-bit word. This *
 *          is the only difference between the other two representations.     *
 *      Error:                                                                *
 *          Based on 394,484,428 samples with -10^6 < x < 10^6.               *
 *              max relative error: 0.0000000000000000e+00                    *
 *              rms relative error: 0.0000000000000000e+00                    *
 *              max absolute error: 0.0000000000000000e+00                    *
 *              rms absolute error: 0.0000000000000000e+00                    *
 *          Values are based on unit tests using glibc and libtmpl.           *
 *  Double / Extended / Quadruple without 64-Bit Integers:                    *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          This method is mostly for experimentation, as it is unlikely that *
 *          one would have 64-bit IEEE-754 compliant long double but not have *
 *          64-bit integers available. One can force this in the build        *
 *          process via -noint when using make.sh or NO_INT=1 in the Makefile.*
 *                                                                            *
 *          The algorithm is nearly identical to the version using 64-bit     *
 *          integers for type punning, but since we only have the IEEE-754    *
 *          struct to work with, we move through the mantissa 16 bits at a    *
 *          time. The previous method does the entire computation in one step *
 *          since the entire mantissa fits in a single 64-bit integer, or two *
 *          steps if long double is represented by 128-bit quadruples.        *
 *                                                                            *
 *          This version is a fair amount slower than the previous one, about *
 *          1.3 to 2.0 times slower.                                          *
 *      Error:                                                                *
 *          Based on 394,484,428 samples with -10^6 < x < 10^6.               *
 *              max relative error: 0.0000000000000000e+00                    *
 *              rms relative error: 0.0000000000000000e+00                    *
 *              max absolute error: 0.0000000000000000e+00                    *
 *              rms absolute error: 0.0000000000000000e+00                    *
 *          Values are based on unit tests using glibc and libtmpl.           *
 *  128-Bit Double-Double Version:                                            *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Truncate:                                         *
 *                  Computes the truncation of a double.                      *
 *      Method:                                                               *
 *          A double-double is represented by two doubles. We have:           *
 *                                                                            *
 *              x = xhi + xlo                                                 *
 *                                                                            *
 *          If xlo is very small, we can compute via:                         *
 *                                                                            *
 *              trunc(x) = trunc(xhi)                                         *
 *                                                                            *
 *          If xlo has integral parts, then xhi is an integer and we can      *
 *          compute via:                                                      *
 *                                                                            *
 *              trunc(x) = trunc(xhi + xlo)                                   *
 *                       = xhi + trunc(xlo)                                   *
 *                                                                            *
 *          In either case, we simply need to compute using double-precision  *
 *          functions.                                                        *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_LDouble_Base2_Mant_and_Exp:                              *
 *                  Gets the base-2 scientific representation of the input.   *
 *                  That is, writes x = r * 2^n with 1 <= r < 2.              *
 *              tmpl_LDouble_Is_NaN_Or_Inf:                                   *
 *                  Determines if a number is NaN or infinity.                *
 *              tmpl_LDouble_Abs:                                             *
 *                  Computes the absolute value of a long double.             *
 *      Method:                                                               *
 *          This version is extremely slow, but does not assume IEEE-754      *
 *          numbers, and it does not use type-punning. It is mostly for       *
 *          experimentation, and is about 10 to 20 times slower. The          *
 *          complexity is O(log(|x|)) where x is the input.                   *
 *                                                                            *
 *          First, special cases:                                             *
 *              If x is zero, return 0.                                       *
 *              If x is NaN or infinity, return x.                            *
 *          For the general case, since x is neither zero nor a NaN or        *
 *          infinity, we can put x in scientific notation:                    *
 *                                                                            *
 *              |x| = r * 2^n   with 1 <= r < 2, n is an integer              *
 *                                                                            *
 *          We then loop through each integer k = n, n-1, ..., 1, 0 and       *
 *          subtract 2^k from |x| if |x| >= 2^k, and continuing to the next   *
 *          integer if |x| < 2^k. We keep track of which powers of k were     *
 *          subtracted off from |x| and add these to "out". At the end, we    *
 *          have computed out = trunc(|x|) in binary. We conclude by          *
 *          returning "out" if x is positive, and -out otherwise.             *
 *      Error:                                                                *
 *          Based on 788,968,857 samples with -10^6 < x < 10^6.               *
 *              max relative error: 0.0000000000000000e+00                    *
 *              rms relative error: 0.0000000000000000e+00                    *
 *              max absolute error: 0.0000000000000000e+00                    *
 *              rms absolute error: 0.0000000000000000e+00                    *
 *          Values are based on unit tests using glibc and libtmpl.           *
 *  Notes:                                                                    *
 *      1.) On several architectures (amd64 / x86_64, aarch64 / arm64)        *
 *          libtmpl implements the trunc function in assembly code. This is   *
 *          decently faster than any of the provided C routines below.        *
 *      2.) Two different type-punning methods are provided. The fastest      *
 *          assumes 64-bit integers are available and can be used for type    *
 *          punning. The slower one does not assume 64-bit fixed width        *
 *          integers are available. Instead it messes with the bits in the    *
 *          tmpl_IEEE754_LDouble union. Both methods assume IEEE-754 support. *
 *          libtmpl determines if this is available upon building.            *
 *      3.) The "portable" method is dreadfully slow, about 10x worse. It is  *
 *          primarily here for experimentation. Only use it if you have no    *
 *          other options.                                                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_inttype.h:                                                       *
 *          Provides fixed-width integer data types.                          *
 *  3.) tmpl_ieee754_ldouble.h:                                               *
 *          Contains the tmpl_IEEE754_LDouble union used for type punning.    *
 *  4.) tmpl_floatint_ldouble.h:                                              *
 *          Contains tmpl_IEEE754_FloatIntLongDouble for type punning.        *
 *  5.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 19, 2023                                             *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS is found here.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This function is only implemented if tmpl's libm was requested.           */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support. This makes the function much faster.          */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  64-bit long double, exact same as 64-bit double.                          */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  Check for 64-bit integer support.                                         */
#if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1

/******************************************************************************
 *                   IEEE-754 Version with 64-Bit Integers                    *
 ******************************************************************************/

/*  Fixed-width integers are found here.                                      */
#include <libtmpl/include/tmpl_inttype.h>

/*  tmpl_IEEE754_FloatIntLongDouble data type provided here.                  */
#include <libtmpl/include/types/tmpl_floatint_ldouble.h>

/*  Function for computing the fractional part of a long double.              */
long double tmpl_LDouble_Fractional_Part(long double x)
{
    /*  Union of a 64-bit int and a long double.                              */
    tmpl_IEEE754_FloatIntLongDouble word;

    /*  The lower fractional bits (non-integral) will be stored here.         */
    tmpl_UInt64 fractional_bits;

    /*  Variable for the exponent, not offset by the bias.                    */
    unsigned int exponent;

    /*  Initialize the word to the input.                                     */
    word.f = x;

    /*  If |x| < 1, we have x mod 1 = x.                                      */
    if (TMPL_LDOUBLE_EXPO_BITS(word.w) < TMPL_LDOUBLE_UBIAS)
        return x;

    /*  If the input is really big, there are no fractional bits. That is,    *
     *  the input is already an integer. Return the input.                    */
    if (TMPL_LDOUBLE_EXPO_BITS(word.w) > TMPL_LDOUBLE_UBIAS + 51U)
    {
        /*  Special case, for NaN or infinity, return NaN.                    */
        if (TMPL_LDOUBLE_IS_NAN_OR_INF(word.w))
            return x - x;

        /*  Otherwise, the output is zero.                                    */
        return 0.0L;
    }

    /*  We now have |x| >= 1, so the exponent in the word is greater than the *
     *  bias. The difference is hence a positive number, so we do not need to *
     *  cast to signed ints. Compute the exponent of the input.               */
    exponent = word.w.bits.expo - TMPL_LDOUBLE_UBIAS;

    /*  There are 52-bits in the mantissa. The bit-mask 0x000FFFFFFFFFFFFF    *
     *  represents 52 1's in binary. By shifting down by the exponent, we     *
     *  get a bit-mask for the fractional bits of the input.                  */
    fractional_bits = 0x000FFFFFFFFFFFFFU >> exponent;

    /*  If none of the fractional bits of the input are 1, then the input was *
     *  already an integer. Return zero.                                      */
    if ((word.n & fractional_bits) == 0)
        return 0.0L;

    /*  The trunc function can be computed by zeroing out all of the          *
     *  fractional bits. This is achieved by using bit-wise-and with the      *
     *  complement of the fractional bits.                                    */
    word.n &= ~fractional_bits;

    /*  word now has the trunc of the input. Output the long double part.     */
    return x - word.f;
}
/*  End of tmpl_LDouble_Fractional_Part.                                      */

#else
/*  Else for #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                          */

/******************************************************************************
 *                  IEEE-754 Version without 64-Bit Integers                  *
 ******************************************************************************/

/*  This method does not require 64 bit integer types be available. It does   *
 *  require that IEEE-754 support for long double is available. It is a bit   *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  tmpl_IEEE754_LDouble data type provided here.                             */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  Function for computing the fractional part of a long double.              */
long double tmpl_LDouble_Fractional_Part(long double x)
{
    /*  Union of a long double and the bits that represent it.                */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  For arguments |x| < 1, we have x mod 1 = x.                           */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS)
        return x;

    /*  If the input is really big, there are no fractional bits. That is,    *
     *  the input is already an integer. Return the input.                    */
    if (TMPL_LDOUBLE_EXPO_BITS(w) > TMPL_LDOUBLE_UBIAS + 51U)
    {
        /*  Special case, for NaN or infinity, return NaN.                    */
        if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
            return x - x;

        /*  Otherwise, the output is zero.                                    */
        return 0.0L;
    }

    /*  For |x| < 2^36, the trunc function will zero out the last part of the *
     *  mantissa. man3 stores 16 bits, similar to man1 and man2.              */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS + 0x24U)
        w.bits.man3 = 0x00U;

    /*  For 2^36 <= |x| < 2^52, only the last part of the mantissa needs to   *
     *  modified. The other bits represent the integer part of x.             */
    else
    {
        /*  We create a bit-mask that zeros out the lowest bits, which        *
         *  represent the fractional part of the number. After this, w is     *
         *  an integer value. The mask is created as follows. 0xFFFF is the   *
         *  hexidecimal representation of 16 1's in binary. We want the lower *
         *  bits to be zero so that bit-wise and will kill these off. The     *
         *  exact bits we want to be zero is given by the exponent of the     *
         *  input. There are 52 (0x34 in hex) bits total, so we want the last *
         *  52 - expo bits to be zero. The exponent is offset by a bias, so   *
         *  expo = w.bits.expo - TMPL_LDOUBLE_UBIAS. In total, shifting up by *
         *  0x34 - (w.bits.expo - TMPL_LDOUBLE_UBIAS) will zero out the lower *
         *  bits, creating the appropriate bit-mask.                          */
        w.bits.man3 &= (0xFFFFU << (0x34U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  If |x| < 2^20, the second part of the mantissa is zeroed out as well. */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS + 0x14U)
        w.bits.man2 = 0x00U;

    /*  Otherwise, if 2^20 <= |x| < 2^36, the highest part of the mantissa    *
     *  needs to be zeroed out, and the second high part must be modified.    */
    else
    {
        /*  Similar to before, create a bit-mask to zero out the fractional   *
         *  parts of the input. Since the upper 16 bits have already been     *
         *  zeroed out, we shift by 52 - 16 = 36, which is 0x24 in hex.       */
        w.bits.man2 &= (0xFFFFU << (0x24U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  If |x| < 2^4, the higher three parts of the mantissa all need to be   *
     *  zeroed out.                                                           */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS + 0x04U)
        w.bits.man1 = 0x00U;

    /*  Otherwise, for 2^16 <= |x| < 2^20, zero out the upper two parts and   *
     *  modify the second lowest part.                                        */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 32 bits *
         *  have been zeroed out, so we shift by 52 - 32 = 20 (0x14 in hex).  */
        w.bits.man1 &= (0xFFFFU << (0x14U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  The lowest part of the mantissa is 4 bits, unlike the other 3 parts   *
     *  which are 16 bits each. Use a bit-mask to zero out the fractional     *
     *  part of the mantissa.                                                 */
    w.bits.man0 &= (0x000FU << (0x04U - (w.bits.expo - TMPL_LDOUBLE_UBIAS)));

    /*  Otherwise w is now correctly set to the trunc of the input.           */
TMPL_LDOUBLE_FRACTIONAL_PART_FINISH:

    /*  The fractional part is x - trunc(x). Return this.                     */
    return x - w.r;
}
/*  End of tmpl_LDouble_Fractional_Part.                                      */

#endif
/*  End of #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                            */

/*  Extended precision. Similar to 64-bit double but with different bit-masks.*/
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT

/*  Check for 64-bit integer support.                                         */
#if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1

/******************************************************************************
 *                    80-Bit Extended with 64-Bit Integers                    *
 ******************************************************************************/

/*  Fixed-width integers are found here.                                      */
#include <libtmpl/include/tmpl_inttype.h>

/*  tmpl_IEEE754_FloatIntLongDouble data type provided here.                  */
#include <libtmpl/include/types/tmpl_floatint_ldouble.h>

/*  Function for computing the fractional part of a long double.              */
long double tmpl_LDouble_Fractional_Part(long double x)
{
    /*  Union of a long double with integers for type-punning.                */
    tmpl_IEEE754_FloatIntLongDouble word;

    /*  The lower fractional bits (non-integral) will be stored here.         */
    tmpl_UInt64 fractional_bits;

    /*  Variable for the exponent, not offset by the bias.                    */
    unsigned int exponent;

    /*  Initialize the word to the input.                                     */
    word.f = x;

    /*  If |x| < 1, we have x mod 1 = x.                                      */
    if (TMPL_LDOUBLE_EXPO_BITS(word.w) < TMPL_LDOUBLE_UBIAS)
        return x;

    /*  If the input is really big, there are no fractional bits. That is,    *
     *  the input is already an integer. Return the input.                    */
    if (TMPL_LDOUBLE_EXPO_BITS(word.w) > TMPL_LDOUBLE_UBIAS + 62U)
    {
        /*  Special case, for NaN or infinity, return NaN.                    */
        if (TMPL_LDOUBLE_IS_NAN_OR_INF(word.w))
            return x - x;

        /*  Otherwise, the output is zero.                                    */
        return 0.0L;
    }

    /*  We now have |x| >= 1, so the exponent in the word is greater than the *
     *  bias. The difference is hence a positive number, so we do not need to *
     *  cast to signed ints. Compute the exponent of the input.               */
    exponent = word.w.bits.expo - TMPL_LDOUBLE_UBIAS;

    /*  There are 63-bits in the mantissa. The bit-mask 0x7FFFFFFFFFFFFFFF    *
     *  represents 63 1's in binary. By shifting down by the exponent, we     *
     *  get a bit-mask for the fractional bits of the input.                  */
    fractional_bits = 0x7FFFFFFFFFFFFFFFU >> exponent;

    /*  If none of the fractional bits of the input are 1, then the input was *
     *  already an integer. Return the input.                                 */
    if ((word.words.lo & fractional_bits) == 0)
        return 0.0L;

    /*  The truncation function can be computed by zeroing out all of the     *
     *  fractional bits. This is achieved by using bit-wise and with the      *
     *  complement of the fractional bits.                                    */
    word.words.lo &= ~fractional_bits;

    /*  word now has the trunc of the input. Output the long double part.     */
    return x - word.f;
}
/*  End of tmpl_LDouble_Fractional_Part.                                      */

#else
/*  Else for #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                          */

/******************************************************************************
 *                   80-Bit Extended without 64-Bit Integers                  *
 ******************************************************************************/

/*  This method does not require 64 bit integer types be available. It does   *
 *  require that IEEE-754 support for double is available. It is a little     *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  tmpl_IEEE754_LDouble data type provided here.                             */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  Function for computing the fractional part of a long double.              */
long double tmpl_LDouble_Fractional_Part(long double x)
{
    /*  Union of a long double and the bits that represent it.                */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  For arguments |x| < 1, we have x mod 1 = x.                           */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS)
        return x;

    /*  For very large arguments, |x| >= 2^63, x is already an integer.       */
    if (TMPL_LDOUBLE_EXPO_BITS(w) > TMPL_LDOUBLE_UBIAS + 62U)
    {
        /*  Special case, for NaN or infinity, return NaN.                    */
        if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
            return x - x;

        /*  Otherwise, the output is zero.                                    */
        return 0.0L;
    }

    /*  For |x| < 2^47, the trunc function will zero out the last part of the *
     *  mantissa. man3 stores 16 bits, similar to man1 and man2.              */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS + 0x2FU)
        w.bits.man3 = 0x00U;

    /*  For 2^47 <= |x| < 2^63, only the last part of the mantissa needs to   *
     *  modified. The other bits represent the integer part of x.             */
    else
    {
        /*  We create a bit-mask that zeros out the lowest bits, which        *
         *  represent the fractional part of the number. After this, w is     *
         *  an integer value. The mask is created as follows. 0xFFFF is the   *
         *  hexidecimal representation of 16 1's in binary. We want the lower *
         *  bits to be zero so that bit-wise and will kill these off. The     *
         *  exact bits we want to be zero is given by the exponent of the     *
         *  input. There are 63 (0x3F in hex) bits total, so we want the last *
         *  63 - expo bits to be zero. The exponent is offset by a bias, so   *
         *  expo = w.bits.expo - TMPL_LDOUBLE_UBIAS. In total, shifting up by *
         *  0x3F - (w.bits.expo - TMPL_LDOUBLE_UBIAS) will zero out the lower *
         *  bits, creating the appropriate bit-mask.                          */
        w.bits.man3 &= (0xFFFFU << (0x3FU - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  If |x| < 2^31, the second part of the mantissa is zeroed out as well. */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS + 0x1FU)
        w.bits.man2 = 0x00U;

    /*  Otherwise, if 2^31 <= |x| < 2^47, the highest part of the mantissa    *
     *  needs to be zeroed out, and the second high part must be modified.    */
    else
    {
        /*  Similar to before, create a bit-mask to zero out the fractional   *
         *  parts of the input. Since the upper 16 bits have already been     *
         *  zeroed out, we shift by 63 - 16 = 47, which is 0x2F in hex.       */
        w.bits.man2 &= (0xFFFFU << (0x2FU - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  If |x| < 2^15, the higher three parts of the mantissa all need to be  *
     *  zeroed out.                                                           */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS + 0x0FU)
        w.bits.man1 = 0x00U;

    /*  Otherwise, for 2^16 <= |x| < 2^20, zero out the upper two parts and   *
     *  modify the second lowest part.                                        */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 32 bits *
         *  have been zeroed out, so we shift by 52 - 32 = 20 (0x14 in hex).  */
        w.bits.man1 &= (0xFFFFU << (0x1FU - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  The lowest part of the mantissa is 15 bits, unlike the other 3 parts  *
     *  which are 16 bits each. Use a bit-mask to zero out the fractional     *
     *  part of the mantissa.                                                 */
    w.bits.man0 &= (0x7FFFU << (0x0FU - (w.bits.expo - TMPL_LDOUBLE_UBIAS)));

    /*  Otherwise w is now correctly set to the trunc of the input.           */
TMPL_LDOUBLE_FRACTIONAL_PART_FINISH:
    return x - w.r;
}
/*  End of tmpl_LDouble_Fractional_Part.                                      */

#endif
/*  End of #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                            */

/*  Double double, different from the rest. Uses two calls to double-trunc.   */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                            128-Bit Double-Double                           *
 ******************************************************************************/

/*  tmpl_IEEE754_LDouble data type provided here.                             */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  Function for computing the fractional part of a long double.              */
long double tmpl_LDouble_Fractional_Part(long double x)
{
    /*  Variable for the difference in the exponent of the low and high parts.*/
    unsigned int expo_diff;

    /*  Variable for the trunc of the high part of the input. This is a       *
     *  double. That is, x = xhi + xlo. We will eventually compute trunc(xhi).*/
    double trunc_hi;

    /*  Union of a long double and the bits representing it.                  */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  Special cases: NaN or infinity. Return NaN.                           */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
        return x - x;

    /*  For arguments |x| < 1, we have x mod 1 = x.                           */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS)
        return x;

    /*  With x = xhi + xlo, either trunc(x) = trunc(xhi), if xlo is very      *
     *  small, or trunc(x) = trunc(xhi) + trunc(xlo) = xhi + trunc(xlo), in   *
     *  which case xhi is already an integer. Compute trunc(xhi) first.       */
    trunc_hi = tmpl_Double_Truncate(w.d[0]);

    /*  If xhi != trunc(xhi), then xhi is not an integer, meaning xhi has a   *
     *  non-trivial fractional part. This means xlo consists only of a        *
     *  fractional part, so trunc(x) = trunc(xhi + xlo) = trunc(xhi). Set the *
     *  low part to zero.                                                     */
    if (w.d[0] != trunc_hi)
        w.d[1] = 0.0;

    /*  If trunc(xhi) = xhi, then xhi is an integer, in which case we have    *
     *  trunc(x) = trunc(xhi + xlo) = xhi + trunc(xlo). Compute trunc(xlo).   */
    else
        w.d[1] = tmpl_Double_Truncate(w.d[1]);

    /*  We're done comparing the high part of the input and can replace it    *
     *  with its trunc.                                                       */
    w.d[0] = trunc_hi;

    /*  We need to make sure that the output is in "double-double" form.      *
     *  Check the size difference between xhi and xlo. Compare the exponents. */
    expo_diff = w.bits.expo - w.bits.expol;

    /*  Rare case, the exponents are exactly 53 apart, and the very last bit  *
     *  of the high part of the word is one. Reset xhi and xlo via:           *
     *                                                                        *
     *      xhi = xhi + 2*xlo                                                 *
     *      xlo = -xlo                                                        *
     *                                                                        *
     *  We will still have x = xhi + xlo, but now in "double-double" form.    */
    if ((expo_diff == 53U) && ((w.bits.man3 & 0x01U) != 0))
    {
        w.d[0] += 2.0*w.d[1];
        w.d[1] = -w.d[1];
    }

    /*  Next case, after taking the trunc we have that the exponents are      *
     *  closer than 53 apart. We can then add the low part to the high part,  *
     *  and then zero out the low part.                                       */
    else if (expo_diff < 53U)
    {
        w.d[0] += w.d[1];
        w.d[1] = 0.0;
    }

    /*  w now contains the trunc of the input. Return the long double part.   */
    return x - w.r;
}
/*  End of tmpl_LDouble_Fractional_Part.                                      */

/*  Quadruple, similar to 80-bit extended, but with more parts.               */
#else

/*  Check for 64-bit integer support.                                         */
#if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1

/******************************************************************************
 *                   128-Bit Quadruple with 64-Bit Integers                   *
 ******************************************************************************/

/*  Fixed-width integers are found here.                                      */
#include <libtmpl/include/tmpl_inttype.h>

/*  tmpl_IEEE754_FloatIntLongDouble data type provided here.                  */
#include <libtmpl/include/types/tmpl_floatint_ldouble.h>

/*  Function for computing the fractional part of a long double.              */
long double tmpl_LDouble_Fractional_Part(long double x)
{
    /*  Union of a long double with integers for type-punning.                */
    tmpl_IEEE754_FloatIntLongDouble word;

    /*  The lower fractional bits (non-integral) will be stored here.         */
    tmpl_UInt64 fractional_bits;

    /*  Variable for the exponent, not offset by the bias.                    */
    unsigned int exponent;

    /*  Initialize the word to the input.                                     */
    word.f = x;

    /*  For |x| < 1, we have x mod 1 = x.                                     */
    if (word.w.bits.expo < TMPL_LDOUBLE_BIAS)
        return x;

    /*  For very large inputs, there are no fractional bits. The input is     *
     *  already an integer. Return the input.                                 */
    if (TMPL_LDOUBLE_EXPO_BITS(word.w) > TMPL_LDOUBLE_BIAS + 111U)
    {
        /*  Special case, for NaN or infinity, return NaN.                    */
        if (TMPL_LDOUBLE_IS_NAN_OR_INF(word.w))
            return x - x;

        /*  Otherwise, the output is zero.                                    */
        return 0.0L;
    }

    /*  We now have |x| >= 1, so the exponent in the word is greater than the *
     *  bias. The difference is hence a positive number, so we do not need to *
     *  cast to signed ints. Compute the exponent of the input.               */
    exponent = word.w.bits.expo - TMPL_LDOUBLE_UBIAS;

    /*  There are 112-bits in the mantissa, and it is split between two       *
     *  64-bit integers. The low word hold 64 bits, and the high word has 48. *
     *  If the exponent is less than 48, we can zero out the lower part.      */
    if (exponent < 48U)
    {
        /*  Low word can be zeroed out. The high word has 48 bits. Create a   *
         *  bit-mask by shifting 0xFFFFFFFFFFFF (48 1's in binary) down by    *
         *  exponent.                                                         */
        fractional_bits = 0x0000FFFFFFFFFFFFU >> exponent;

        /*  If none of the fractional bits of the input are 1, then the input *
         *  was already an integer. Return the input.                         */
        if (((word.words.hi & fractional_bits) | word.words.lo) == 0)
            return 0.0L;

        /*  The trunc function can be computed by zeroing out all of the      *
         *  fractional bits. This is achieved by using bit-wise and with the  *
         *  complement of the fractional bits.                                */
        word.words.hi &= ~fractional_bits;

        /*  The low part can be made zero. It is only fractional bits.        */
        word.words.lo = 0;
    }

    /*  For very large inputs, |x| > 2^48, the high part of the mantissa      *
     *  is part of the integral portion of the input. We need to examine the  *
     *  lower bits.                                                           */
    else
    {
        /*  Similar bit-mask as before, but with 64 1's instead of 48.        */
        fractional_bits = 0xFFFFFFFFFFFFFFFFU >> (exponent - 48U);

        /*  If none of the fractional bits of the input are 1, then the input *
         *  was already an integer. Return the input.                         */
        if ((word.words.lo & fractional_bits) == 0)
            return 0.0L;

        /*  Same trick as before, zero out the fractional bits.               */
        word.words.lo &= ~fractional_bits;
    }

    /*  word now has the trunc of the input. Output the long double part.     */
    return x - word.f;
}
/*  End of tmpl_LDouble_Fractional_Part.                                      */

#else
/*  Else for #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                          */

/******************************************************************************
 *                  128-Bit Quadruple without 64-Bit Integers                 *
 ******************************************************************************/

/*  Same idea as the previous code, but examines the mantissa 16 bits at a    *
 *  time. This does not require 64-bit integers.                              */

/*  tmpl_IEEE754_LDouble data type provided here.                             */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  Function for computing the fractional part of a long double.              */
long double tmpl_LDouble_Fractional_Part(long double x)
{
    /*  Union of a long double and the bits that represent it.                */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  For arguments |x| < 1, we have x mod 1 = x.                           */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS)
        return x;

    /*  For very large arguments, |x| >= 2^112, x is already an integer.      */
    if (TMPL_LDOUBLE_EXPO_BITS(w) > TMPL_LDOUBLE_UBIAS + 111U)
    {
        /*  Special case, for NaN or infinity, return NaN.                    */
        if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
            return x - x;

        /*  Otherwise, the output is zero.                                    */
        return 0.0L;
    }

    /*  For |x| < 2^96, the trunc function will zero out the last part of the *
     *  mantissa. man6 stores 16 bits, similar to all other parts.            */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS + 0x60U)
        w.bits.man6 = 0x00U;

    /*  For 2^96 <= |x| < 2^112, only the last part of the mantissa needs to  *
     *  modified. The other bits represent the integer part of x.             */
    else
    {
        /*  We create a bit-mask that zeros out the lowest bits, which        *
         *  represent the fractional part of the number. After this, w is     *
         *  an integer value. The mask is created as follows. 0xFFFF is the   *
         *  hexidecimal representation of 16 1's in binary. We want the lower *
         *  bits to be zero so that bit-wise and will kill these off. The     *
         *  exact bits we want to be zero is given by the exponent of the     *
         *  input. There are 112 (0x70 in hex) bits total so we want the last *
         *  112 - expo bits to be zero. The exponent is offset by a bias, so  *
         *  expo = w.bits.expo - TMPL_LDOUBLE_UBIAS. In total, shifting up by *
         *  0x70 - (w.bits.expo - TMPL_LDOUBLE_UBIAS) will zero out the lower *
         *  bits, creating the appropriate bit-mask.                          */
        w.bits.man3 &= (0xFFFFU << (0x70U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  If |x| < 2^80, the second part of the mantissa is zeroed out as well. */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x50U)
        w.bits.man5 = 0x00U;

    /*  Otherwise, if 2^80 <= |x| < 2^96, the highest part of the mantissa    *
     *  needs to be zeroed out, and the second high part must be modified.    */
    else
    {
        /*  Similar to before, create a bit-mask to zero out the fractional   *
         *  parts of the input. Since the upper 16 bits have already been     *
         *  zeroed out, we shift by 112 - 16 = 96, which is 0x60 in hex.      */
        w.bits.man5 &= (0xFFFFU << (0x60U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  If |x| < 2^64, the higher three parts of the mantissa all need to be  *
     *  zeroed out.                                                           */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x40U)
        w.bits.man4 = 0x00U;

    /*  Otherwise, for 2^64 <= |x| < 2^80, zero out the upper two parts and   *
     *  modify the second lowest part.                                        */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 32 bits *
         *  have been zeroed out, so we shift by 112 - 32 = 80 (0x50 in hex). */
        w.bits.man4 &= (0xFFFFU << (0x50U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  If |x| < 2^48, the higher four parts of the mantissa all need to be   *
     *  zeroed out.                                                           */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x30U)
        w.bits.man3 = 0x00U;

    /*  Otherwise, for 2^48 <= |x| < 2^64, zero out the upper two parts and   *
     *  modify the second lowest part.                                        */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 48 bits *
         *  have been zeroed out, so we shift by 112 - 48 = 64 (0x40 in hex). */
        w.bits.man3 &= (0xFFFFU << (0x40U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  If |x| < 2^32, the higher five parts of the mantissa all need to be   *
     *  zeroed out.                                                           */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x20U)
        w.bits.man2 = 0x00U;

    /*  Otherwise, for 2^32 <= |x| < 2^48, zero out the upper two parts and   *
     *  modify the second lowest part.                                        */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 64 bits *
         *  have been zeroed out, so we shift by 112 - 64 = 48 (0x30 in hex). */
        w.bits.man2 &= (0xFFFFU << (0x30U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  If |x| < 2^16, the higher six parts of the mantissa all need to be    *
     *  zeroed out.                                                           */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x10U)
        w.bits.man1 = 0x00U;

    /*  Otherwise, for 2^16 <= |x| < 2^32, zero out the upper five parts and  *
     *  modify the second highest part.                                       */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 80 bits *
         *  have been zeroed out, so we shift by 112 - 80 = 32 (0x20 in hex). */
        w.bits.man1 &= (0xFFFFU << (0x20U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FRACTIONAL_PART_FINISH;
    }

    /*  Same bit-wise trick for the last part of the mantissa.                */
    w.bits.man0 &= (0xFFFFU << (0x10U - (w.bits.expo - TMPL_LDOUBLE_UBIAS)));

    /*  Otherwise w is now correctly set to the trunc of the input.           */
TMPL_LDOUBLE_FRACTIONAL_PART_FINISH:
    return x - w.r;
}
/*  End of tmpl_LDouble_Fractional_Part.                                      */

#endif
/*  End of #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                            */

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/******************************************************************************
 *  DO NOT USE UNLESS YOU HAVE NO OTHER OPTIONS.                              *
 *      This code is portable but stupidly slow. The default build of libtmpl *
 *      uses assembly code that is very fast. If the user requested no        *
 *      assembly code and IEEE-754 support is available, the above code is    *
 *      used, and is nearly as fast. This portable code is available in case  *
 *      assembly language nor IEEE-754 support can be used, but it is slow.   *
 *                                                                            *
 *      On x86_64 machines, the assembly code and both versions of the trunc  *
 *      function above that take advantage of the IEEE-754 format have        *
 *      computational time comparable to other libm implementations. This     *
 *      version is about 10-20x slower.                                       *
 ******************************************************************************/

/*  Function for truncating a long double (truncl equivalent).                */
long double tmpl_LDouble_Fractional_Part(long double x)
{
    /*  Declare necessary variables. C89 requires declarations are the top.   */
    long double abs_x, mant, y, out;
    signed int expo;

    /*  Special case, trunc(0) = 0.                                           */
    if (x == 0.0L)
        return 0.0L;

    /*  Next special case, NaN or inf. Return NaN.                            */
    if (tmpl_LDouble_Is_NaN_Or_Inf(x))
        return x - x;

    /*  Get the numbers mant and expo such that x = mant * 2^expo with        *
     *  1 <= |mant| < 2. That is, the base 2 scientific notation of x.        */
    tmpl_LDouble_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  If expo < 0 we have |x| < 1. trunc(x) = 0.                            */
    if (expo < 0)
        return x;

    /*  This function is only accurate to 64 bits in the mantissa. For most   *
     *  machines the mantissa has 63 bits, so this is fine.                   */
    else if (expo > 64)
        return 0.0L;

    /*  Use the fact that trunc(x) = -trunc(-x) to reduce the argument.       */
    abs_x = tmpl_LDouble_Abs(x);

    /*  We're going to "zero" the highest bit of the integer part of abs_x    *
     *  by substracting it off. Compute this from the lookup table.           */
    y = tmpl_ldouble_pow_2_table[expo];

    /*  We will iteratively add the non-zero bits of the integer part to out, *
     *  resulting in us computing trunc(abs_x).                               */
    out = y;

    /*  Zero out the highest bit of abs_x by subtracting y.                   */
    abs_x = abs_x - y;

    /*  This highest non-zero bit has been zeroed out, move to the next one.  */
    --expo;

    /*  Loop over the remaining bits of the integer part of abs_x and repeat. */
    while (expo >= 0)
    {
        y = tmpl_ldouble_pow_2_table[expo];

        /*  If abs_x < y, this bit is already zero. No need to subtract.      *
         *  Otherwise, zero this bit out and add it to out.                   */
        if (abs_x >= y)
        {
            abs_x -= y;
            out += y;
        }

        /*  If abs_x is zero, we are done. Break out of the loop.             */
        if (abs_x == 0.0L)
            break;

        /*  Get the next power of two and repeat.                             */
        --expo;
    }

    /*  If the input was negative we need to use trunc(x) = -trunc(-x).       */
    if (x < 0.0L)
        return x + out;

    /*  For positive values, we are done with the computation.                */
    return x - out;
}
/*  End of tmpl_LDouble_Fractional_Part.                                      */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
