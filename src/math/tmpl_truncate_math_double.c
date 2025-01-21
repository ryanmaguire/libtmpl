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
 *                            tmpl_truncate_double                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the truncation of x. This is the input minus the fractional  *
 *      part, which is equivalent to rounding-to-zero.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Truncation                                                *
 *  Purpose:                                                                  *
 *      Computes the integer part of the input (round-to-zero).               *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      trunc_x (double):                                                     *
 *          The truncation of x.                                              *
 *  IEEE-754 Version with 64-Bit Integers:                                    *
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
 *          First, special cases.                                             *
 *              If x is NaN or infinity, return x.                            *
 *              If |x| < 1 (meaning exponent < 0), return 0.                  *
 *          For the general case, compute the exponent, and then zero out     *
 *          the last "exponent" bits of the mantissa. This is equivalent to   *
 *          setting the fractional part of the input to zero, meaning it is   *
 *          now an integer value. We could do this by creating a bit-mask of  *
 *          64 1's, and then "bit-shift" up by "exponent" number of bits.     *
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
 *      Error:                                                                *
 *          Based on 788,968,857 samples with -10^6 < x < 10^6.               *
 *              max relative error: 0.0000000000000000e+00                    *
 *              rms relative error: 0.0000000000000000e+00                    *
 *              max absolute error: 0.0000000000000000e+00                    *
 *              rms absolute error: 0.0000000000000000e+00                    *
 *          Values are based on unit tests using glibc and libtmpl.           *
 *  IEEE-754 Version without 64-Bit Integers:                                 *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          This method is mostly for experimentation, as it is highly        *
 *          unlikely that one would have 64-bit IEEE-754 compliant doubles,   *
 *          but not have 64-bit integers available. One can force this in the *
 *          build process via -noint when using make.sh, or NO_INT=1 with the *
 *          Makefile.                                                         *
 *                                                                            *
 *          The algorithm is nearly identical to the version using 64-bit     *
 *          integers for type punning, but since we only have the IEEE-754    *
 *          struct to work with, we move through the mantissa 16 bits at a    *
 *          time. The previous method does the entire computation in one step *
 *          since the entire mantissa fits in a single 64-bit integer.        *
 *                                                                            *
 *          This version is a fair amount slower than the previous one, about *
 *          1.3 to 1.7 times slower.                                          *
 *      Error:                                                                *
 *          Based on 788,968,857 samples with -10^6 < x < 10^6.               *
 *              max relative error: 0.0000000000000000e+00                    *
 *              rms relative error: 0.0000000000000000e+00                    *
 *              max absolute error: 0.0000000000000000e+00                    *
 *              rms absolute error: 0.0000000000000000e+00                    *
 *          Values are based on unit tests using glibc and libtmpl.           *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Base2_Mant_and_Exp:                               *
 *                  Gets the base-2 scientific representation of the input.   *
 *                  That is, writes x = r * 2^n with 1 <= r < 2.              *
 *              tmpl_Double_Is_NaN_Or_Inf:                                    *
 *                  Determines if a number is NaN or infinity.                *
 *              tmpl_Double_Abs:                                              *
 *                  Computes the absolute value of a double.                  *
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
 *          libtmpl implements the truncation function in assembly code. This *
 *          is decently faster than any of the provided C routines below.     *
 *      2.) Two different type-punning methods are provided. The fastest      *
 *          assumes 64-bit integers are available and can be used for type    *
 *          punning. The slower one does not assume 64-bit fixed width        *
 *          integers are available. Instead it messes with the bits in the    *
 *          tmpl_IEEE754_Double union. Both methods assume IEEE-754 support.  *
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
 *  3.) tmpl_ieee754_double.h:                                                *
 *          Contains the tmpl_IEEE754_Double union used for type punning.     *
 *  4.) tmpl_floatint_double.h:                                               *
 *          Contains the tmpl_IEEE754_FloatInt64 union for type punning.      *
 *  5.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 26, 2022                                            *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS is found here.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This function is only implemented if tmpl's libm was requested.           */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support. This makes the function much faster.          */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Check for 64-bit integer support.                                         */
#if TMPL_HAS_FLOATINT64 == 1

/******************************************************************************
 *                   IEEE-754 Version with 64-Bit Integers                    *
 ******************************************************************************/

/*  Fixed-width integers are found here.                                      */
#include <libtmpl/include/tmpl_inttype.h>

/*  tmpl_IEEE754_FloatInt64 data type provided here.                          */
#include <libtmpl/include/types/tmpl_floatint_double.h>

/*  Function for computing the truncation of a double (trunc equivalent).     */
double tmpl_Double_Truncate(double x)
{
    /*  Union of a 64-bit int and a double.                                   */
    tmpl_IEEE754_FloatInt64 word64;

    /*  The lower fractional bits (non-integral) will be stored here.         */
    tmpl_UInt64 fractional_bits;

    /*  Variable for the exponent, not offset by the bias.                    */
    unsigned int exponent;

    /*  Initialize the word to the input.                                     */
    word64.f = x;

    /*  If |x| < 1, we have trunc(x) = 0.                                     */
    if (word64.w.bits.expo < TMPL_DOUBLE_UBIAS)
        return 0.0;

    /*  If the input is really big, there are no fractional bits. That is,    *
     *  the input is already an integer. Return the input.                    */
    if (word64.w.bits.expo > TMPL_DOUBLE_UBIAS + 51U)
        return x;

    /*  We now have |x| >= 1, so the exponent in the word is greater than the *
     *  bias. The difference is hence a positive number, so we do not need to *
     *  cast to signed ints. Compute the exponent of the input.               */
    exponent = word64.w.bits.expo - TMPL_DOUBLE_UBIAS;

    /*  There are 52-bits in the mantissa. The bit-mask 0x000FFFFFFFFFFFFF    *
     *  represents 52 1's in binary. By shifting down by the exponent, we     *
     *  get a bit-mask for the fractional bits of the input.                  */
    fractional_bits = 0x000FFFFFFFFFFFFFU >> exponent;

    /*  If none of the fractional bits of the input are 1, then the input was *
     *  already an integer. Return the input.                                 */
    if ((word64.n & fractional_bits) == 0)
        return x;

    /*  The truncation function can be computed by zeroing out all of the     *
     *  fractional bits. This is achieved by using bit-wise-and with the      *
     *  complement of the fractional bits.                                    */
    word64.n &= ~fractional_bits;

    /*  word64 now has the truncation of the input. Output the double part.   */
    return word64.f;
}
/*  End of tmpl_Double_Truncate.                                              */

#else
/*  Else for #if TMPL_HAS_FLOATINT64 == 1.                                    */

/******************************************************************************
 *                  IEEE-754 Version without 64-Bit Integers                  *
 ******************************************************************************/

/*  This method does not require 64 bit integer types be available. It does   *
 *  require that IEEE-754 support for double is available. It is a little     *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  tmpl_IEEE754_Double data type provided here.                              */
#include <libtmpl/include/tmpl_ieee754_double.h>

/*  Function for computing the truncation of a double (trunc equivalent).     */
double tmpl_Double_Truncate(double x)
{
    /*  Union of a double and the bits that represent it.                     */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  For arguments |x| < 1, we have trunc(x) = 0.                          */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS)
        return 0.0;

    /*  For very large arguments, |x| >= 2^52, x is already an integer.       */
    if (w.bits.expo > TMPL_DOUBLE_UBIAS + 51U)
        return x;

    /*  For |x| < 2^36, the trunc function will zero out the last part of the *
     *  mantissa. man3 stores 16 bits, similar to man1 and man2.              */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS + 0x24U)
        w.bits.man3 = 0x00U;

    /*  For 2^36 <= |x| < 2^52, only the last part of the mantissa needs to   *
     *  modified. The other bits represent the integer part of x.             */
    else
    {
        /*  We create a bit-mask that zeros out the lowest bits, which        *
         *  represent the fractional part of the number. After this, w is     *
         *  an integer value. The mask is created as follows. 0xFFFF is the   *
         *  hexidecimal representation of 16 1's in binary. We want the lower *
         *  bits to be zero so that bit-wise-and will kill these off. The     *
         *  exact bits we want to be zero is given by the exponent of the     *
         *  input. There are 52 (0x34 in hex) bits total, so we want the last *
         *  52 - expo bits to be zero. The exponent is offset by a bias, so   *
         *  expo = w.bits.expo - TMPL_DOUBLE_UBIAS. In total, shifting up by  *
         *  0x34 - (w.bits.expo - TMPL_DOUBLE_UBIAS) will zero out the lower  *
         *  bits, creating the appropriate bit-mask.                          */
        w.bits.man3 &= (0xFFFFU << (0x34U - (w.bits.expo - TMPL_DOUBLE_UBIAS)));
        goto TMPL_DOUBLE_TRUNCATE_FINISH;
    }

    /*  If |x| < 2^20, the second part of the mantissa is zeroed out as well. */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS + 0x14U)
        w.bits.man2 = 0x00U;

    /*  Otherwise, if 2^20 <= |x| < 2^36, the highest part of the mantissa    *
     *  needs to be zeroed out, and the second high part must be modified.    */
    else
    {
        /*  Similar to before, create a bit-mask to zero out the fractional   *
         *  parts of the input. Since the upper 16 bits have already been     *
         *  zeroed out, we shift by 52 - 16 = 36, which is 0x24 in hex.       */
        w.bits.man2 &= (0xFFFFU << (0x24U - (w.bits.expo - TMPL_DOUBLE_UBIAS)));
        goto TMPL_DOUBLE_TRUNCATE_FINISH;
    }

    /*  If |x| < 2^4, the higher three parts of the mantissa all need to be   *
     *  zeroed out.                                                           */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS + 0x04U)
        w.bits.man1 = 0x00U;

    /*  Otherwise, for 2^4 <= |x| < 2^20, zero out the upper two parts and    *
     *  modify the second lowest part.                                        */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 32 bits *
         *  have been zeroed out, so we shift by 52 - 32 = 20 (0x14 in hex).  */
        w.bits.man1 &= (0xFFFFU << (0x14U - (w.bits.expo - TMPL_DOUBLE_UBIAS)));
        goto TMPL_DOUBLE_TRUNCATE_FINISH;
    }

    /*  The lowest part of the mantissa is 4 bits, unlike the other 3 parts   *
     *  which are 16 bits each. Use a bit-mask to zero out the fractional     *
     *  part of the mantissa.                                                 */
    w.bits.man0 &= (0x000FU << (0x04U - (w.bits.expo - TMPL_DOUBLE_UBIAS)));

    /*  w is now correctly set to the truncation of the input.                */
TMPL_DOUBLE_TRUNCATE_FINISH:
    return w.r;
}
/*  End of tmpl_Double_Truncate.                                              */

#endif
/*  End of #if TMPL_HAS_FLOATINT64 == 1.                                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

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
 *      version is about 10x slower.                                          *
 ******************************************************************************/

/*  Function for computing the truncation of a double (trunc equivalent).     */
double tmpl_Double_Truncate(double x)
{
    /*  Declare necessary variables. C89 requires declarations are the top.   */
    double abs_x, mant, y, out;
    signed int expo;

    /*  Special case, trunc(0) = 0.                                           */
    if (x == 0.0)
        return x;

    /*  Next special case, NaN or inf. Return the input.                      */
    if (tmpl_Double_Is_NaN_Or_Inf(x))
        return x;

    /*  Get the numbers mant and expo such that x = mant * 2^expo with        *
     *  1 <= |mant| < 2. That is, the base 2 scientific notation of x.        */
    tmpl_Double_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  If expo < 0 we have |x| < 1. trunc(x) = 0.                            */
    if (expo < 0)
        return 0.0;

    /*  This function is only accurate to 64 bits in the mantissa. For most   *
     *  machines the mantissa has 52 bits, so this is probably overkill.      */
    else if (expo > 64)
        return x;

    /*  Use the fact that trunc(x) = -trunc(-x) to reduce the argument.       */
    abs_x = tmpl_Double_Abs(x);

    /*  We're going to "zero" the highest bit of the integer part of abs_x    *
     *  by substracting it off. Compute this from the lookup table.           */
    y = tmpl_double_pow_2_table[expo];

    /*  We will iteratively add the non-zero bits of the integer part to out, *
     *  resulting in us computing trunc(abs_x).                               */
    out = y;

    /*  Zero out the highest bit of abs_x by subtracting y.                   */
    abs_x = abs_x - y;

    /*  The highest non-zero bit has been zeroed out, move to the next one.   */
    --expo;

    /*  Loop over the remaining bits of the integer part of abs_x and repeat. */
    while (expo >= 0)
    {
        y = tmpl_double_pow_2_table[expo];

        /*  If abs_x < y, this bit is already zero. No need to subtract.      *
         *  Otherwise, zero this bit out and add it to out.                   */
        if (abs_x >= y)
        {
            abs_x -= y;
            out += y;
        }

        /*  If abs_x is zero, we are done. Break out of the loop.             */
        if (abs_x == 0.0)
            break;

        /*  Get the next power of two and repeat.                             */
        --expo;
    }

    /*  If the input was negative we need to use trunc(x) = -trunc(-x).       */
    if (x < 0.0)
        return -out;

    /*  For positive values, we are done with the computation.                */
    return out;
}
/*  End of tmpl_Double_Truncate.                                              */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of TMPL_USE_MATH_ALGORITHMS.                                          */
