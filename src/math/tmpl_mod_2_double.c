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
 *                             tmpl_mod_2_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the remainder after division by two.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Mod_2                                                     *
 *  Purpose:                                                                  *
 *      Computes the remainder after division of the input by two.            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for x mod 2.                          *
 *  Output:                                                                   *
 *      x_mod_2 (double):                                                     *
 *          The remainder after division of x by two.                         *
 *  Called Functions:                                                         *
 *      tmpl_Int64_Leading_Zeros    (tmpl_integer.h):                         *
 *          Counts leading zeros in an integer. Used if IEEE-754 support and  *
 *          64-bit integers are available.                                    *
 *      tmpl_Double_Floor   (tmpl_math.h):                                    *
 *          Computes the floor of a double. Only used in the portable method. *
 *  Method:                                                                   *
 *      For all methods, reduce the input to non-negative since mod 2 is odd. *
 *                                                                            *
 *      If IEEE-754 support and 64-bit integers are available:                *
 *          The number is represented as 1.xxx * 2^e. By shifting the decimal *
 *          e to the right and zero out all integer terms greater than one we *
 *          have two possibilities: 1.yyy, and 0.yyy. If the result is 1.yyy, *
 *          that's the answer. If the answer is 0.yyy we need to shift the    *
 *          decimal to the right by the number of leading zeros until it is   *
 *          of the form 1.zzz. If this never occurs, the input was an integer *
 *          greater than one, so the result mod 2 is zero.                    *
 *                                                                            *
 *      If IEEE-754 support is available, but 64-bit integers are not:        *
 *          Use bit twiddling to compute the floor of x/2. Use the formula:   *
 *              x mod 2 = x - 2*floor(x/2)                                    *
 *          to complete the computation.                                      *
 *                                                                            *
 *      Portable method:                                                      *
 *          Call tmpl_Double_Floor directly and returns x - 2*floor(x/2).     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_inttype.h:                                                       *
 *          Header file containing TMPL_HAS_64_BIT_INT macro.                 *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 30, 2022                                             *
 ******************************************************************************/

/*  TMPL_HAS_IEEE754_DOUBLE macro and function prototype found here.          */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support. Significant speed boost if available.         */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  TMPL_HAS_64_BIT_INT macro found here. tmpl_UInt64 is here if available.   */
#include <libtmpl/include/tmpl_inttype.h>

/*  We can get a speed boost if 64-bit int is available.                      */
#if TMPL_HAS_64_BIT_INT == 1

/*  Function for computing the remainder after division by 2.                 */
double tmpl_Double_Mod_2(double x)
{
    /*  64-bit integer available, we can get a speed boost using this. Create *
     *  a union with an unsigned 64-bit integer and an IEEE-754 double.       */
    union {
        tmpl_IEEE754_Double w;
        tmpl_UInt64 n;
    } word64;

    /*  This variable is for preserving the sign of x at the end. mod 2 is an *
     *  odd function, so we'll compute the absolute value of the input.       */
    tmpl_IEEE754_Double tmp;

    /*  Two variables for the exponent of the input and the number of leading *
     *  zeroes in the mantissa after shifting.                                */
    unsigned int expo, leading;

    /*  Set the double part of the IEEE-754 union to the input.               */
    word64.w.r = x;

    /*  We'll be altering this variable. Preserve the sign by copying it.     */
    tmp = word64.w;

    /*  If the exponent is negative, or zero, then |x| < 2. Return x.         */
    if (word64.w.bits.expo <= TMPL_DOUBLE_BIAS)
        return x;

    /*  If the exponent is greater than or equal to 52 all bits of the        *
     *  mantissa represent the integer part of x. That is, x is an integer    *
     *  to double precision. The answer is either -1, 0, or 1 depending on    *
     *  the sign of x and whether the last bit of the mantissa is 0 or 1.     */
    else if (word64.w.bits.expo > TMPL_DOUBLE_BIAS + 51U)
    {
        /*  Special case, infinity or NaN. Return NaN.                        */
        if (word64.w.bits.expo == TMPL_DOUBLE_NANINF_EXP)
            return TMPL_NAN;

        /*  Large number. One's place is not included in mantissa. Return 0.  */
        else if (word64.w.bits.expo > TMPL_DOUBLE_BIAS + 52U)
        {
            word64.w.r = 0.0;

            /*  Return a signed zero with the same sign as the input.         */
            word64.w.bits.sign = tmp.bits.sign;
            return word64.w.r;
        }

        /*  For all other cases, the one's case is included in the mantissa.  *
         *  We just need to check the very last bit.                          */

        /*  If the last bit of the mantissa is 1, the number is odd.          */
        if (word64.w.bits.man3 & 0x01U)
        {
            /*  Odd integer, mod 2 is +/- 1.                                  */
            word64.w.r = 1.0;

            /*  tmp still has the sign of x, copy this to the output.         */
            word64.w.bits.sign = tmp.bits.sign;
            return word64.w.r;
        }

        /*  Otherwise we have an even integer, return 0.                      */
        else
        {
            /*  Even integer, mod 2 is 0.                                     */
            word64.w.r = 0.0;

            /*  Preserve the sign of the input (i.e. if x is "negative" 0).   *
             *  tmp still has the sign of the input, copy this to the output. */
            word64.w.bits.sign = tmp.bits.sign;
            return word64.w.r;
        }
    }

    /*  Compute the exponent of the double. This is the expo bits minus the   *
     *  offset. We've checked that expo is not negative, so we can safely     *
     *  subtract off the bias and the result is a positive integer.           */
    expo = word64.w.bits.expo - TMPL_DOUBLE_BIAS;

    /*  The first "expo" bits of the mantissa are for the integer part of x.  *
     *  mod 2 kills all of these, so shift the decimal point expo to the left.*/
    word64.n = word64.n << expo;

    /*  If the 52nd bit is 1, the number is now in the form 1.xxx. We just    *
     *  need to reset the exponent to 1 and we have the answer.               */
    if (word64.n & 0x0010000000000000)
        word64.w.bits.expo = TMPL_DOUBLE_BIAS;

    /*  Otherwise the number is of the form 0.xxx. We need to get this into   *
     *  scientific notation. To do this we count how many leading zeros there *
     *  are in the mantissa.                                                  */
    else
    {
        /*  Zero out the exponent and sign part of the word. We only want to  *
         *  count leading zeros in the mantissa.                              */
        word64.n = 0x000FFFFFFFFFFFFF & word64.n;

        /*  There are 12 bits for the sign and exponent, and these are all    *
         *  zero. These do not contribute to the leading zeros in the         *
         *  mantissa so subtract off 12. We also want the answer in the form  *
         *  1.xxx, not 0.1xxx, so shift one more to the left. The result is   *
         *  shifting by the number of leading zeros minus 12 plus 1, so shift *
         *  by the number of leading zeros minus 11.                          */
        leading = (unsigned int)tmpl_UInt64_Leading_Zeros(word64.n) - 11U;
        word64.n = word64.n << leading;

        /*  If the 52nd bit is 1, we have 1.xxx as desired. The exponent is   *
         *  now -leading, so set this. We need to add the bias back, so the   *
         *  final exponent is TMPL_DOUBLE_BIAS - leading.                     */
        if (word64.n & 0x0010000000000000)
            word64.w.bits.expo = (TMPL_DOUBLE_BIAS - leading) & 0x7FF;

        /*  In this case the number was an even integer to begin with.        *
         *  The result is zero.                                               */
        else
            word64.w.r = 0.0;
    }

    /*  mod 2 is an odd function and we've computed |x| mod 2. The variable   *
     *  tmp still has the original sign of x. Copy this into the answer.      */
    word64.w.bits.sign = tmp.bits.sign;
    return word64.w.r;
}
/*  End of tmpl_Double_Mod_2.                                                 */

#else
/*  Else for #if TMPL_HAS_64_BIT_INT == 1.                                    */

/*  This method does not require 64 bit integer types be available. It does   *
 *  require that IEEE-754 support for double is available. It is a little     *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  The mantissa is split into 4 components. The highest component has 4 bits *
 *  and the other three have 16 each. These three numbers are the cutoff      *
 *  values for the components.                                                */
#define A0 36U
#define A1 20U
#define A2 4U

/*  Function for computing the floor of a double (floor equivalent).          */
double tmpl_Double_Mod_2(double x)
{
    tmpl_IEEE754_Double w, tmp;
    w.r = x;
    tmp = w;

    /*  If the exponent is negative, or zero, then |x| < 2. Return x.         */
    if (w.bits.expo <= TMPL_DOUBLE_BIAS)
        return x;

    /*  If the exponent is greater than or equal to 52 all bits of the        *
     *  mantissa represent the integer part of x. That is, x is an integer    *
     *  to double precision. The answer is either -1, 0, or 1 depending on    *
     *  the sign of x and whether the last bit of the mantissa is 0 or 1.     */
    else if (w.bits.expo > TMPL_DOUBLE_BIAS + 51U)
    {
        /*  Special case, infinity or NaN. Return NaN.                        */
        if (w.bits.expo == TMPL_DOUBLE_NANINF_EXP)
            return TMPL_NAN;

        /*  Large number. One's place is not included in mantissa. Return 0.  */
        else if (w.bits.expo > TMPL_DOUBLE_BIAS + 52U)
        {
            w.r = 0.0;

            /*  Return a signed zero with the same sign as the input.         */
            w.bits.sign = tmp.bits.sign;
            return w.r;
        }

        /*  If the last bit of the mantissa is 1, the number is odd.          */
        if (w.bits.man3 & 0x01U)
        {
            /*  Odd integer, mod 2 is +/- 1.                                  */
            w.r = 1.0;

            /*  tmp still has the sign of x, copy this to the output.         */
            w.bits.sign = tmp.bits.sign;
            return w.r;
        }

        /*  Otherwise we have an even integer, return 0.                      */
        else
        {
            /*  Even integer, mod 2 is 0.                                     */
            w.r = 0.0;

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
    if (w.bits.expo < TMPL_DOUBLE_BIAS + A0)
        w.bits.man3 = 0x00U;
    else
    {
        w.bits.man3 &= ~(0xFFFF >> (w.bits.expo - TMPL_DOUBLE_BIAS - A0));
        goto TMPL_DOUBLE_MOD2_FINISH;
    }

    if (w.bits.expo < TMPL_DOUBLE_BIAS + A1)
        w.bits.man2 = 0x00U;
    else
    {
        w.bits.man2 &= ~(0xFFFF >> (w.bits.expo - TMPL_DOUBLE_BIAS - A1));
        goto TMPL_DOUBLE_MOD2_FINISH;
    }

    if (w.bits.expo < TMPL_DOUBLE_BIAS + A2)
        w.bits.man1 = 0x00U;
    else
    {
        w.bits.man1 &= ~(0xFFFF >> (w.bits.expo - TMPL_DOUBLE_BIAS - A2));
        goto TMPL_DOUBLE_MOD2_FINISH;
    }

    w.bits.man0 &= ~(0xF >> (w.bits.expo - TMPL_DOUBLE_BIAS));

TMPL_DOUBLE_MOD2_FINISH:

    /*  We want to compute 2 * floor(x/2). So far we have floor(x/2).         *
     *  Multiply by 2 by adjusting the exponent by 1.                         */
    w.bits.expo++;
    return x - w.r;
}
/*  End of tmpl_Double_Floor.                                                 */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2

#endif
/*  End of #if TMPL_HAS_64_BIT_INT == 1.                                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/*  Portable algorithm for mod 2 based on the floor function.                 */
double tmpl_Double_Mod_2(double x)
{
    /*  x mod 2 is odd. We can use this to reduce the argument to positive.   */
    if (x < 0.0)
        return x + 2.0 * tmpl_Double_Floor(-0.5 * x);
    else
        return x - 2.0 * tmpl_Double_Floor(0.5 * x);
}
/*  End of tmpl_Double_Mod_2.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
