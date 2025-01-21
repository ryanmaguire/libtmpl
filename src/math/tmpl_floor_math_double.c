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
 *                             tmpl_floor_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = |_x_|, the floor of x. This is the largest integer    *
 *      that is less than or equal to the input x.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Floor                                                     *
 *  Purpose:                                                                  *
 *      Computes the floor function. The largest integer less than or equal   *
 *      to the input.                                                         *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for |_x_|.                            *
 *  Output:                                                                   *
 *      floor_x (double):                                                     *
 *          The floor of x.                                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, use bit-twiddling. A double is      *
 *      represented as follows:                                               *
 *                                                                            *
 *        s eeeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  *
 *        - ----------- ----------------------------------------------------  *
 *      sign exponent                mantissa                                 *
 *                                                                            *
 *      If exponent >= 52, the number is an integer. If exponent < 0, the     *
 *      number is such that |x| < 1, so floor(x) = 0 if x is non-negative,    *
 *      and -1 if x is negative. Otherwise, shift the bit point "exponent" to *
 *      the right and zero out all mantissa bits that are to the right of the *
 *      new bit point.                                                        *
 *                                                                            *
 *      The portable method uses a similar idea, but is very slow.            *
 *  Notes:                                                                    *
 *      1.) On several architectures (amd64 / x86_64, aarch64 / arm64)        *
 *          libtmpl implements the floor function in assembly code. This is   *
 *          decently faster than any of the provided C routines below.        *
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

/*  Function for computing the floor of a double (floor equivalent).          */
double tmpl_Double_Floor(double x)
{
    /*  Union of a 64-bit int and a double.                                   */
    tmpl_IEEE754_FloatInt64 word64;

    /*  The lower fractional bits (non-integral) will be stored here.         */
    tmpl_UInt64 fractional_bits;

    /*  Variable for the exponent, not offset by the bias.                    */
    unsigned int exponent;

    /*  Initialize the word to the input.                                     */
    word64.f = x;

    /*  If |x| < 1, we have floor(x) = 0 or -1, depending on the sign.        */
    if (word64.w.bits.expo < TMPL_DOUBLE_UBIAS)
    {
        /*  Regardless of the sign of x, zero should map to zero.             */
        if (x == 0.0)
            return x;

        /*  For negative, floor(x) = -1.                                      */
        if (word64.w.bits.sign)
            return -1.0;

        /*  And for 0 < x < 1, floor(x) = 0.                                  */
        return 0.0;
    }

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

    /*  For negative non-integer values, floor(x) = -floor(|x|+1). We can     *
     *  compute the +1 term by adding to the 1's bit in the word. Note that   *
     *  if this results in a carry, the sum will bleed over into the exponent *
     *  part. This is perfectly fine since a carry means the exponent must    *
     *  increase by 1, which is what the sum does.                            */
    if (word64.w.bits.sign)
        word64.n += 0x0010000000000000 >> exponent;

    /*  The floor function can be computed by zeroing out all of the          *
     *  fractional bits. This is achieved by using bit-wise and with the      *
     *  complement of the fractional bits.                                    */
    word64.n &= ~fractional_bits;

    /*  word64 now has the floor of the input. Output the double part.        */
    return word64.f;
}
/*  End of tmpl_Double_Floor.                                                 */

#else
/*  Else for #if TMPL_HAS_FLOATINT64 == 1.                                    */

/******************************************************************************
 *                  IEEE-754 Version without 64-Bit Integers                  *
 ******************************************************************************/

/*  This method does not require 64 bit integer types be available. It does   *
 *  require that IEEE-754 support for double is available. It is a little     *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  tmpl_IEEE754_Double data type provided here.                              */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  Function for computing the floor of a double (floor equivalent).          */
double tmpl_Double_Floor(double x)
{
    /*  Union of a double and the bits that represent it.                     */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  For arguments |x| < 1, either floor(x) = 0 or floor(x) = -1.          */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS)
    {
        /*  Regardless of the sign of x, zero should map to zero.             */
        if (x == 0.0)
            return x;

        /*  For -1 < x < 0, we have floor(x) = -1.                            */
        if (w.bits.sign)
            return -1.0;

        /*  And for 0 < x < 1, we get floor(x) = 0.                           */
        return 0.0;
    }

    /*  For very large arguments, |x| >= 2^52, x is already an integer.       */
    if (w.bits.expo > TMPL_DOUBLE_UBIAS + 51U)
        return x;

    /*  For |x| < 2^36, the floor function will zero out the last part of the *
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
         *  bits to be zero so that bit-wise and will kill these off. The     *
         *  exact bits we want to be zero is given by the exponent of the     *
         *  input. There are 52 (0x34 in hex) bits total, so we want the last *
         *  52 - expo bits to be zero. The exponent is offset by a bias, so   *
         *  expo = w.bits.expo - TMPL_DOUBLE_UBIAS. In total, shifting up by  *
         *  0x34 - (w.bits.expo - TMPL_DOUBLE_UBIAS) will zero out the lower  *
         *  bits, creating the appropriate bit-mask.                          */
        w.bits.man3 &= (0xFFFFU << (0x34U - (w.bits.expo - TMPL_DOUBLE_UBIAS)));
        goto TMPL_DOUBLE_FLOOR_FINISH;
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
        goto TMPL_DOUBLE_FLOOR_FINISH;
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
        goto TMPL_DOUBLE_FLOOR_FINISH;
    }

    /*  The lowest part of the mantissa is 4 bits, unlike the other 3 parts   *
     *  which are 16 bits each. Use a bit-mask to zero out the fractional     *
     *  part of the mantissa.                                                 */
    w.bits.man0 &= (0x000FU << (0x04U - (w.bits.expo - TMPL_DOUBLE_UBIAS)));

    /*  We need to handle positive and negative inputs carefully.             */
TMPL_DOUBLE_FLOOR_FINISH:

    /*  For negative inputs, use floor(x) = -floor(-x) - 1. This is true      *
     *  unless the input was already an integer. Check for this.              */
    if (TMPL_DOUBLE_IS_NEGATIVE(w) && w.r != x)
        return w.r - 1.0;

    /*  Otherwise w is now correctly set to the floor of the input.           */
    return w.r;
}
/*  End of tmpl_Double_Floor.                                                 */

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
 *      On x86_64 machines, the assembly code and both versions of the floor  *
 *      function above that take advantage of the IEEE-754 format have        *
 *      computational time comparable to other libm implementations. This     *
 *      version is about 10x slower.                                          *
 ******************************************************************************/

/*  Function for computing the floor of a double (floor equivalent).          */
double tmpl_Double_Floor(double x)
{
    /*  Declare necessary variables. C89 requires declarations are the top.   */
    double abs_x, mant, y, out;
    signed int expo;

    /*  Special case, floor(0) = 0.                                           */
    if (x == 0.0)
        return x;

    /*  Next special case, NaN or inf. Return the input.                      */
    if (tmpl_Double_Is_NaN_Or_Inf(x))
        return x;

    /*  Get the numbers mant and expo such that x = mant * 2^expo with        *
     *  1 <= |mant| < 2. That is, the base 2 scientific notation of x.        */
    tmpl_Double_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  If expo < 0 we have |x| < 1. floor(x) = 0 if x >= 0 and -1 otherwise. */
    if (expo < 0)
    {
        /*  For negative values, -1 < x < 0, we have floor(x) = -1.           */
        if (x < 0.0)
            return -1.0;

        /*  Otherwise, for 0 < x < 1, we have floor(x) = 0.                   */
        return 0.0;
    }

    /*  This function is only accurate to 64 bits in the mantissa. For most   *
     *  machines the mantissa has 52 bits, so this is probably overkill.      */
    else if (expo > 64)
        return x;

    /*  Use the fact that floor(x) = -1 - floor(-x) for negative non-integer  *
     *  values to reduce the argument.                                        */
    abs_x = tmpl_Double_Abs(x);

    /*  We're going to "zero" the highest bit of the integer part of abs_x    *
     *  by substracting it off. Compute this from the lookup table.           */
    y = tmpl_double_pow_2_table[expo];

    /*  We will iteratively add the non-zero bits of the integer part to out, *
     *  resulting in us computing floor(abs_x).                               */
    out = y;

    /*  Zero out the highest bit of abs_x by subtracting y.                   */
    abs_x = abs_x - y;

    /*  This highest non-zero bit has been zeroed out, move to the next one.  */
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

    /*  If the input was negative we need to use floor(x) = -1 - floor(-x).   */
    if (x < 0.0)
    {
        /*  The formula does not work for integers. If the input was an       *
         *  integer to begin with, return it.                                 */
        if (x == -out)
            return x;

        /*  Otherwise, use the negation formula and return.                   */
        return -1.0 - out;
    }

    /*  For positive values, we are done with the computation.                */
    return out;
}
/*  End of tmpl_Double_Floor.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of TMPL_USE_MATH_ALGORITHMS.                                          */
