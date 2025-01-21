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
 *                              tmpl_ceil_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the ceiling of x. This is the smallest integer that is       *
 *      greater than or equal to the input x.                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Ceil                                                       *
 *  Purpose:                                                                  *
 *      Computes the ceiling function. The smallest integer that is greater   *
 *      than or equal to the input.                                           *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the argument for ceil(x).                          *
 *  Output:                                                                   *
 *      ceil_x (float):                                                       *
 *          The ceiling of x.                                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, use bit-twiddling. A float is       *
 *      represented as follows:                                               *
 *                                                                            *
 *              s eeeeeeee xxxxxxxxxxxxxxxxxxxxxxx                            *
 *              - -------- -----------------------                            *
 *           sign exponent        mantissa                                    *
 *                                                                            *
 *      If exponent >= 23, the number is an integer. If exponent < 0, the     *
 *      number is such that |x| < 1, so ceil(x) = 1 if x is positive,         *
 *      and 0 if x is negative. Otherwise, shift the bit point "exponent" to  *
 *      the right and zero out all mantissa bits that are to the right of the *
 *      new bit point. This computes the floor of x. If x = floor(x), we are  *
 *      done, otherwise return floor(x) + 1.                                  *
 *                                                                            *
 *      The portable method uses a similar idea, but is very slow.            *
 *  Notes:                                                                    *
 *      1.) On several architectures (amd64 / x86_64, aarch64 / arm64)        *
 *          libtmpl implements the ceil function in assembly code. This is    *
 *          decently faster than any of the provided C routines below.        *
 *      2.) Two different type-punning methods are provided. The fastest      *
 *          assumes 32-bit integers are available and can be used for type    *
 *          punning. The slower one does not assume 32-bit fixed width        *
 *          integers are available. Instead it messes with the bits in the    *
 *          tmpl_IEEE754_Floar union. Both methods assume IEEE-754 support.   *
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
 *  3.) tmpl_ieee754_float.h:                                                 *
 *          Contains the tmpl_IEEE754_Float union used for type punning.      *
 *  4.) tmpl_floatint_float.h:                                                *
 *          Contains the tmpl_IEEE754_FloatInt32 union for type punning.      *
 *  5.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 14, 2024                                             *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS is found here.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This function is only implemented if tmpl's libm was requested.           */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support. This makes the function much faster.          */
#if TMPL_HAS_IEEE754_FLOAT == 1

/*  Check for 32-bit integer support.                                         */
#if TMPL_HAS_FLOATINT32 == 1

/******************************************************************************
 *                   IEEE-754 Version with 32-Bit Integers                    *
 ******************************************************************************/

/*  Fixed-width integers are found here.                                      */
#include <libtmpl/include/tmpl_inttype.h>

/*  tmpl_IEEE754_FloatInt32 data type provided here.                          */
#include <libtmpl/include/types/tmpl_floatint_float.h>

/*  Function for computing the ceiling of a float (ceilf equivalent).         */
float tmpl_Float_Ceil(float x)
{
    /*  Union of a 32-bit int and a float.                                    */
    tmpl_IEEE754_FloatInt32 word32;

    /*  The lower fractional bits (non-integral) will be stored here.         */
    tmpl_UInt32 fractional_bits;

    /*  Variable for the exponent, not offset by the bias.                    */
    unsigned int exponent;

    /*  Initialize the word to the input.                                     */
    word32.f = x;

    /*  If |x| < 1, we have ceil(x) = 1 or 0, depending on the sign.          */
    if (word32.w.bits.expo < TMPL_FLOAT_UBIAS)
    {
        /*  Regardless of the sign of x, zero should map to zero.             */
        if (x == 0.0F)
            return x;

        /*  For negative, ceil(x) = 0.                                        */
        if (word32.w.bits.sign)
            return 0.0F;

        /*  And for 0 < x < 1, ceil(x) = 1.                                   */
        return 1.0F;
    }

    /*  If the input is really big, there are no fractional bits. That is,    *
     *  the input is already an integer. Return the input.                    */
    if (word32.w.bits.expo > TMPL_FLOAT_UBIAS + 22U)
        return x;

    /*  We now have |x| >= 1, so the exponent in the word is greater than the *
     *  bias. The difference is hence a positive number, so we do not need to *
     *  cast to signed ints. Compute the exponent of the input.               */
    exponent = word32.w.bits.expo - TMPL_FLOAT_UBIAS;

    /*  There are 52-bits in the mantissa. The bit-mask 0x000FFFFFFFFFFFFF    *
     *  represents 52 1's in binary. By shifting down by the exponent, we     *
     *  get a bit-mask for the fractional bits of the input.                  */
    fractional_bits = 0x007FFFFFU >> exponent;

    /*  If none of the fractional bits of the input are 1, then the input was *
     *  already an integer. Return the input.                                 */
    if ((word32.n & fractional_bits) == 0)
        return x;

    /*  For positive non-integer values, ceil(x) = floor(x+1). We can         *
     *  compute the +1 term by adding to the 1's bit in the word. Note that   *
     *  if this results in a carry, the sum will bleed over into the exponent *
     *  part. This is perfectly fine since a carry means the exponent must    *
     *  increase by 1, which is what the sum does.                            */
    if (!word32.w.bits.sign)
        word32.n += 0x00800000U >> exponent;

    /*  For negative non-integer values, we have ceil(x) = -floor(-x), and    *
     *  for positive numbers we have ceil(x) = floor(x+1). In either case we  *
     *  just compute the floor function. This is done by zeroing out all of   *
     *  the fractional bits.                                                  */
    word32.n &= ~fractional_bits;

    /*  word32 now has the ceil of the input. Output the float part.          */
    return word32.f;
}
/*  End of tmpl_Float_Ceil.                                                   */

#else
/*  Else for #if TMPL_HAS_FLOATINT32 == 1.                                    */

/******************************************************************************
 *                  IEEE-754 Version without 32-Bit Integers                  *
 ******************************************************************************/

/*  This method does not require 32 bit integer types be available. It does   *
 *  require that IEEE-754 support for float is available. It is a little      *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  tmpl_IEEE754_Float data type provided here.                               */
#include <libtmpl/include/types/tmpl_ieee754_float.h>

/*  Function for computing the ceiling of a float (ceilf equivalent).         */
float tmpl_Float_Ceil(float x)
{
    /*  Union of a float and the bits that represent it.                      */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the word to the input.                          */
    w.r = x;

    /*  For arguments |x| < 1, either ceil(x) = 0 or ceil(x) = 1.             */
    if (w.bits.expo < TMPL_FLOAT_UBIAS)
    {
        /*  Regardless of the sign of x, zero should map to zero.             */
        if (x == 0.0F)
            return x;

        /*  For -1 < x < 0, we have ceil(x) = 0.                              */
        if (TMPL_FLOAT_IS_NEGATIVE(w))
            return 0.0F;

        /*  And for 0 < x < 1, we get ceil(x) = 1.                            */
        return 1.0F;
    }

    /*  For very large arguments, |x| >= 2^23, x is already an integer.       */
    if (w.bits.expo > TMPL_FLOAT_UBIAS + 22U)
        return x;

    /*  For |x| < 2^8, the floor function will zero out the last part of the  *
     *  mantissa. man1 stores 16 bits, total.                                 */
    if (w.bits.expo < TMPL_FLOAT_UBIAS + 0x08U)
    {
        w.bits.man1 = 0x00U;

        /*  We create a bit-mask that zeros out the lowest bits, which        *
         *  represent the fractional part of the number. After this, w is     *
         *  an integer value. The mask is created as follows. There are 23    *
         *  bits total in the mantissa, 7 in man0 and 16 in man1. We've       *
         *  already zeroed out the lower 16 bits in man1, so we need to zero  *
         *  out the lower expo - 16 bits of man0, where expo is the exponent  *
         *  of the input. Taking into account the bias, this is:              *
         *      expo = w.bits.expo - TMPL_FLOAT_UBIAS                         *
         *  To lower out the lower expo bits, we take the bit-mask 0x7F,      *
         *  which is the hexidecimal representation of 7 1's in binary, and   *
         *  shift this up 7 - expo bits. We then perform bit-wise and.        */
        w.bits.man0 &= (0x7FU << (0x07U - (w.bits.expo - TMPL_FLOAT_UBIAS)));
    }

    /*  Same idea as before, but this time we use a bit-mask starting with    *
     *  0xFFFF, which is 16 1's in binary. This is because man1 contains 16   *
     *  bits. We shift up 23 - expo = 0x17 - expo bits and do bit-wise and.   */
    else
        w.bits.man1 &= (0xFFFFU << (0x17U - (w.bits.expo - TMPL_FLOAT_UBIAS)));

    /*  For positive inputs, use ceil(x) = floor(x) + 1. This is true         *
     *  unless the input was already an integer. Check for this.              */
    if (!TMPL_FLOAT_IS_NEGATIVE(w) && w.r != x)
        return w.r + 1.0F;

    /*  Otherwise w is now correctly set to the ceil of the input.            */
    return w.r;
}
/*  End of tmpl_Float_Ceil.                                                   */

#endif
/*  End of #if TMPL_HAS_FLOATINT32 == 1.                                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

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
 *      On x86_64 machines, the assembly code and both versions of the ceil   *
 *      function above that take advantage of the IEEE-754 format have        *
 *      computational time comparable to other libm implementations. This     *
 *      version is about 10x slower.                                          *
 ******************************************************************************/

/*  Function for computing the ceiling of a float (ceil equivalent).          */
float tmpl_Float_Ceil(float x)
{
    /*  Declare necessary variables. C89 requires declarations are the top.   */
    float abs_x, mant, y, out;
    signed int expo;

    /*  Special case, ceil(0) = 0.                                            */
    if (x == 0.0F)
        return x;

    /*  Next special case, NaN or inf. Return the input.                      */
    if (tmpl_Float_Is_NaN_Or_Inf(x))
        return x;

    /*  Get the numbers mant and expo such that x = mant * 2^expo with        *
     *  1 <= |mant| < 2. That is, the base 2 scientific notation of x.        */
    tmpl_Float_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  If expo < 0 we have |x| < 1. ceil(x) = 1 if x >= 0 and 0 otherwise.   */
    if (expo < 0)
    {
        /*  For negative values, -1 < x < 0, we have ceil(x) = 0.             */
        if (x < 0.0F)
            return 0.0F;

        /*  Otherwise, for 0 < x < 1, we have ceil(x) = 1.                    */
        return 1.0F;
    }

    /*  This function is only accurate to 64 bits in the mantissa. For most   *
     *  machines the mantissa has 52 bits, so this is probably overkill.      */
    else if (expo > 64)
        return x;

    /*  Use the fact that ceil(x) = floor(x + 1) for positive non-integer and *
     *  ceil(x) = -floor(-x) for negative inputs to reduce the argument.      */
    abs_x = tmpl_Float_Abs(x);

    /*  We're going to "zero" the highest bit of the integer part of abs_x    *
     *  by substracting it off. Compute this from the lookup table.           */
    y = tmpl_float_pow_2_table[expo];

    /*  We will iteratively add the non-zero bits of the integer part to out, *
     *  resulting in us computing ceil(abs_x).                                */
    out = y;

    /*  Zero out the highest bit of abs_x by subtracting y.                   */
    abs_x = abs_x - y;

    /*  This highest non-zero bit has been zeroed out, move to the next one.  */
    --expo;

    /*  Loop over the remaining bits of the integer part of abs_x and repeat. */
    while (expo >= 0)
    {
        y = tmpl_float_pow_2_table[expo];

        /*  If abs_x < y, this bit is already zero. No need to subtract.      *
         *  Otherwise, zero this bit out and add it to out.                   */
        if (abs_x >= y)
        {
            abs_x -= y;
            out += y;
        }

        /*  If abs_x is zero, we are done. Break out of the loop.             */
        if (abs_x == 0.0F)
            break;

        /*  Get the next power of two and repeat.                             */
        --expo;
    }

    /*  If the input was positive we need to use ceil(x) = floor(x) + 1.      */
    if (x > 0.0F)
    {
        /*  The formula does not work for integers. If the input was an       *
         *  integer to begin with, return it.                                 */
        if (x == out)
            return x;

        /*  Otherwise, use the negation formula and return.                   */
        return out + 1.0F;
    }

    /*  For negative values, use ceil(x) = -floor(x) and return.              */
    return -out;
}
/*  End of tmpl_Float_Ceil.                                                   */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of TMPL_USE_MATH_ALGORITHMS.                                          */
