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
 *                             tmpl_mod_2_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the remainder after division by two.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Mod_2                                                      *
 *  Purpose:                                                                  *
 *      Computes the remainder after division of the input by two.            *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the argument for x mod 2.                          *
 *  Output:                                                                   *
 *      x_mod_2 (float):                                                      *
 *          The remainder after division of x by two.                         *
 *  Called Functions:                                                         *
 *      tmpl_Int32_Leading_Zeros    (tmpl_integer.h):                         *
 *          Counts leading zeros in an integer. Used if IEEE-754 support and  *
 *          32-bit integers are available.                                    *
 *      tmpl_Float_Floor   (tmpl_math.h):                                     *
 *          Computes the floor of a float. Only used in the portable method.  *
 *  Method:                                                                   *
 *      For all methods, reduce the input to non-negative since mod 2 is odd. *
 *                                                                            *
 *      If IEEE-754 support and 32-bit integers are available:                *
 *          The number is represented as 1.xxx * 2^e. By shifting the decimal *
 *          e to the right and zero out all integer terms greater than one we *
 *          have two possibilities: 1.yyy, and 0.yyy. If the result is 1.yyy, *
 *          that's the answer. If the answer is 0.yyy we need to shift the    *
 *          decimal to the right by the number of leading zeros until it is   *
 *          of the form 1.zzz. If this never occurs, the input was an integer *
 *          greater than one, so the result mod 2 is zero.                    *
 *                                                                            *
 *      If IEEE-754 support is available, but 32-bit integers are not:        *
 *          Use bit twiddling to compute the floor of x/2. Use the formula:   *
 *              x mod 2 = x - 2*floor(x/2)                                    *
 *          to complete the computation.                                      *
 *                                                                            *
 *      Portable method:                                                      *
 *          Call tmpl_Float_Floor directly and returns x - 2*floor(x/2).      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_inttype.h:                                                       *
 *          Header file containing TMPL_HAS_32_BIT_INT macro.                 *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 30, 2022                                             *
 ******************************************************************************/

/*  TMPL_HAS_IEEE754_FLOAT macro and function prototype found here.           */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support. Significant speed boost if available.         */
#if TMPL_HAS_IEEE754_FLOAT == 1

/*  TMPL_HAS_32_BIT_INT macro found here. tmpl_UInt32 is here if available.   */
#include <libtmpl/include/tmpl_inttype.h>

/*  We can get a speed boost if 32-bit int is available.                      */
#if TMPL_HAS_32_BIT_INT == 1

/*  Functions for counting the number of leading zeros in an integer are here.*/
#include <libtmpl/include/tmpl_integer.h>

/*  Function for computing the remainder after division by 2.                 */
float tmpl_Float_Mod_2(float x)
{
    /*  32-bit integer available, we can get a speed boost using this. Create *
     *  a union with an unsigned 32-bit integer and an IEEE-754 float.        */
    union {
        tmpl_IEEE754_Float w;
        tmpl_UInt32 n;
    } word32;

    /*  This variable is for preserving the sign of x at the end. mod 2 is an *
     *  odd function, so we'll compute the absolute value of the input.       */
    tmpl_IEEE754_Float tmp;

    /*  Two variables for the exponent of the input and the number of leading *
     *  zeroes in the mantissa after shifting.                                */
    unsigned int expo, leading;

    /*  Set the float part of the IEEE-754 union to the input.                */
    word32.w.r = x;

    /*  We'll be altering this variable. Preserve the sign by copying it.     */
    tmp = word32.w;

    /*  If the exponent is negative, or zero, then |x| < 2. Return x.         */
    if (word32.w.bits.expo <= TMPL_FLOAT_BIAS)
        return x;

    /*  If the exponent is greater than or equal to 23 all bits of the        *
     *  mantissa represent the integer part of x. That is, x is an integer    *
     *  to single precision. The answer is either -1, 0, or 1 depending on    *
     *  the sign of x and whether the last bit of the mantissa is 0 or 1.     */
    else if (word32.w.bits.expo > TMPL_FLOAT_BIAS + 22U)
    {
        /*  Special case, infinity or NaN. Return NaN.                        */
        if (word32.w.bits.expo == TMPL_FLOAT_NANINF_EXP)
            return TMPL_NANF;

        /*  Large number. One's place is not included in mantissa. Return 0.  */
        else if (word32.w.bits.expo > TMPL_FLOAT_BIAS + 23U)
        {
            word32.w.r = 0.0F;

            /*  Return a signed zero with the same sign as the input.         */
            word32.w.bits.sign = tmp.bits.sign;
            return word32.w.r;
        }

        /*  For all other cases, the one's case is included in the mantissa.  *
         *  We just need to check the very last bit.                          */

        /*  If the last bit of the mantissa is 1, the number is odd.          */
        if (word32.w.bits.man1 & 0x01U)
        {
            /*  Odd integer, mod 2 is +/- 1.                                  */
            word32.w.r = 1.0F;

            /*  tmp still has the sign of x, copy this to the output.         */
            word32.w.bits.sign = tmp.bits.sign;
            return word32.w.r;
        }

        /*  Otherwise we have an even integer, return 0.                      */
        else
        {
            /*  Even integer, mod 2 is 0.                                     */
            word32.w.r = 0.0F;

            /*  Preserve the sign of the input (i.e. if x is "negative" 0).   *
             *  tmp still has the sign of the input, copy this to the output. */
            word32.w.bits.sign = tmp.bits.sign;
            return word32.w.r;
        }
    }

    /*  Compute the exponent of the float. This is the expo bits minus the    *
     *  offset. We've checked that expo is not negative, so we can safely     *
     *  subtract off the bias and the result is a positive integer.           */
    expo = word32.w.bits.expo - TMPL_FLOAT_BIAS;

    /*  The first "expo" bits of the mantissa are for the integer part of x.  *
     *  mod 2 kills all of these, so shift the decimal point expo to the left.*/
    word32.n = word32.n << expo;

    /*  If the 24th bit is 1, the number is now in the form 1.xxx. We just    *
     *  need to reset the exponent to 1 and we have the answer.               */
    if (word32.n & 0x00800000)
        word32.w.bits.expo = TMPL_FLOAT_BIAS;

    /*  Otherwise the number is of the form 0.xxx. We need to get this into   *
     *  scientific notation. To do this we count how many leading zeros there *
     *  are in the mantissa.                                                  */
    else
    {
        /*  Zero out the exponent and sign part of the word. We only want to  *
         *  count leading zeros in the mantissa.                              */
        word32.n = 0x007FFFFF & word32.n;

        /*  There are 9 bits for the sign and exponent, and these are all     *
         *  zero. These do not contribute to the leading zeros in the         *
         *  mantissa so subtract off 9. We also want the answer in the form   *
         *  1.xxx, not 0.1xxx, so shift one more to the left. The result is   *
         *  shifting by the number of leading zeros minus 9 plus 1, so shift  *
         *  by the number of leading zeros minus 8.                           */
        leading = (unsigned int)tmpl_UInt32_Leading_Zeros(word32.n) - 8U;
        word32.n = word32.n << leading;

        /*  If the 24th bit is 1, we have 1.xxx as desired. The exponent is   *
         *  now -leading, so set this. We need to add the bias back, so the   *
         *  final exponent is TMPL_FLOAT_BIAS - leading.                      */
        if (word32.n & 0x00800000)
            word32.w.bits.expo = (TMPL_FLOAT_BIAS - leading) & 0xFF;

        /*  In this case the number was an even integer to begin with.        *
         *  The result is zero.                                               */
        else
            word32.w.r = 0.0;
    }

    /*  mod 2 is an odd function and we've computed |x| mod 2. The variable   *
     *  tmp still has the original sign of x. Copy this into the answer.      */
    word32.w.bits.sign = tmp.bits.sign;
    return word32.w.r;
}
/*  End of tmpl_Float_Mod_2.                                                  */

#else
/*  Else for #if TMPL_HAS_32_BIT_INT == 1.                                    */

/*  This method does not require 32 bit integer types be available. It does   *
 *  require that IEEE-754 support for float is available. It is a little      *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  The mantissa is split into 2 components. The highest component has 7 bits *
 *  and the lowest component has 16 bits, 23 bits total.                      */
#define TMPL_EXPO_SHIFT (0x07U + TMPL_FLOAT_UBIAS)

/*  Function for computing the remainder after division by 2.                 */
float tmpl_Float_Mod_2(float x)
{
    tmpl_IEEE754_Float w, tmp;
    w.r = x;
    tmp = w;

    /*  If the exponent is negative, or zero, then |x| < 2. Return x.         */
    if (w.bits.expo <= TMPL_FLOAT_BIAS)
        return x;

    /*  If the exponent is greater than or equal to 23 all bits of the        *
     *  mantissa represent the integer part of x. That is, x is an integer    *
     *  to single precision. The answer is either -1, 0, or 1 depending on    *
     *  the sign of x and whether the last bit of the mantissa is 0 or 1.     */
    else if (w.bits.expo > TMPL_FLOAT_BIAS + 22U)
    {
        /*  Special case, infinity or NaN. Return NaN.                        */
        if (w.bits.expo == TMPL_FLOAT_BIAS)
            return TMPL_NANF;

        /*  Large number. One's place is not included in mantissa. Return 0.  */
        else if (w.bits.expo > TMPL_FLOAT_BIAS + 23U)
        {
            w.r = 0.0F;

            /*  Return a signed zero with the same sign as the input.         */
            w.bits.sign = tmp.bits.sign;
            return w.r;
        }

        /*  If the last bit of the mantissa is 1, the number is odd.          */
        if (w.bits.man1 & 0x01U)
        {
            /*  Odd integer, mod 2 is +/- 1.                                  */
            w.r = 1.0F;

            /*  tmp still has the sign of x, copy this to the output.         */
            w.bits.sign = tmp.bits.sign;
            return w.r;
        }

        /*  Otherwise we have an even integer, return 0.                      */
        else
        {
            /*  Even integer, mod 2 is 0.                                     */
            w.r = 0.0F;

            /*  Preserve the sign of the input (i.e. if x is "negative" 0).   *
             *  tmp still has the sign of the input, copy this to the output. */
            w.bits.sign = tmp.bits.sign;
            return tmp.r;
        }
    }

    /*  For x > 0, x mod 2 = x - 2*floor(x/2). Compute x/2 by subtracting     *
     *  one from the exponent.                                                */
    w.bits.expo--;

    /*  Compute the floor of x/2 by bit-twiddling, checking each part of the  *
     *  mantissa.                                                             */
    if (w.bits.expo < TMPL_EXPO_SHIFT)
    {
        w.bits.man1 = 0x00U;
        w.bits.man0 &= 0x7F << (0x07U - (w.bits.expo - TMPL_FLOAT_UBIAS));
    }
    else
        w.bits.man1 &= 0xFFFFU << (0x10U - (w.bits.expo - TMPL_EXPO_SHIFT));

    /*  We want to compute 2 * floor(x/2). So far we have floor(x/2).         *
     *  Multiply by 2 by adjusting the exponent by 1.                         */
    w.bits.expo++;
    return x - w.r;
}
/*  End of tmpl_Float_Floor.                                                  */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef TMPL_EXPO_SHIFT

#endif
/*  End of #if TMPL_HAS_32_BIT_INT == 1.                                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/*  Portable algorithm for mod 2 based on the floor function.                 */
float tmpl_Float_Mod_2(float x)
{
    return x - 2.0F * tmpl_Float_Truncate(0.5F * x);
}
/*  End of tmpl_Float_Mod_2.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */
