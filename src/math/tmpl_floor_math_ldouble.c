

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

/******************************************************************************
 *                                64-Bit Double                               *
 ******************************************************************************/

 /*  Check for 64-bit integer support.                                         */
#if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1

/*  tmpl_IEEE754_FloatIntLongDouble data type provided here.                  */
#include <libtmpl/include/tmpl_floatint.h>

/*  Function for computing the floor of a double (floor equivalent).          */
long double tmpl_LDouble_Floor(long double x)
{
    /*  Union of a 64-bit int and a double.                                   */
    tmpl_IEEE754_FloatIntLongDouble word;

    /*  The lower fractional bits (non-integral) will be stored here.         */
    tmpl_UInt64 fractional_bits;

    /*  Variable for the exponent, not offset by the bias.                    */
    unsigned int exponent;

    /*  Initialize the word to the input.                                     */
    word.f = x;

    /*  If |x| < 1, we have floor(x) = 0 or -1, depending on the sign.        */
    if (word.w.bits.expo < TMPL_DOUBLE_UBIAS)
    {
        /*  Regardless of the sign of x, zero should map to zero.             */
        if (x == 0.0)
            return x;

        /*  For negative, floor(x) = -1.                                      */
        if (word.w.bits.sign)
            return -1.0;

        /*  And for 0 < x < 1, floor(x) = 0.                                  */
        return 0.0;
    }

    /*  If the input is really big, there are no fractional bits. That is,    *
     *  the input is already an integer. Return the input.                    */
    if (word.w.bits.expo > TMPL_DOUBLE_UBIAS + 51U)
        return x;

    /*  We now have |x| >= 1, so the exponent in the word is greater than the *
     *  bias. The difference is hence a positive number, so we do not need to *
     *  cast to signed ints. Compute the exponent of the input.               */
    exponent = word.w.bits.expo - TMPL_DOUBLE_UBIAS;

    /*  There are 52-bits in the mantissa. The bit-mask 0x000FFFFFFFFFFFFF    *
     *  represents 52 1's in binary. By shifting down by the exponent, we     *
     *  get a bit-mask for the fractional bits of the input.                  */
    fractional_bits = 0x000FFFFFFFFFFFFFU >> exponent;

    /*  If none of the fractional bits of the input are 1, then the input was *
     *  already an integer. Return the input.                                 */
    if ((word.n & fractional_bits) == 0)
        return x;

    /*  For negative non-integer values, floor(x) = -floor(|x|+1). We can     *
     *  compute the +1 term by adding to the 1's bit in the word. Note that   *
     *  if this results in a carry, the sum will bleed over into the exponent *
     *  part. This is perfectly fine since a carry means the exponent must    *
     *  increase by 1, which is what the sum does.                            */
    if (word.w.bits.sign)
        word.n += 0x0010000000000000 >> exponent;

    /*  The floor function can be computed by zeroing out all of the          *
     *  fractional bits. This is achieved by using bit-wise and with the      *
     *  complement of the fractional bits.                                    */
    word.n &= ~fractional_bits;

    /*  word now has the floor of the input. Output the double part.          */
    return word.f;
}
/*  End of tmpl_Double_Floor.                                                 */

#else
/*  Else for #if TMPL_HAS_FLOATINT64 == 1.                                    */

/*  This method does not require 64 bit integer types be available. It does   *
 *  require that IEEE-754 support for double is available. It is a little     *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  Function for computing the floor of a double (floor equivalent).          */
double tmpl_Double_Floor(double x)
{
    tmpl_IEEE754_Double w;
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

    /*  Otherwise, for 2^16 <= |x| < 2^20, zero out the upper two parts and   *
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
/*  End of #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                            */

/*  Extended precision. Similar to 64-bit double but with different bit-masks.*/
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT

/******************************************************************************
 *                               80-Bit Extended                              *
 ******************************************************************************/

/*  Check for 64-bit integer support.                                         */
#if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1

/*  tmpl_IEEE754_FloatIntLongDouble data type provided here.                  */
#include <libtmpl/include/tmpl_floatint.h>

/*  Function for computing the floor of a double (floor equivalent).          */
long double tmpl_LDouble_Floor(long double x)
{
    /*  Union of a long double with integers for type-punning.                */
    tmpl_IEEE754_FloatIntLongDouble word;

    /*  The lower fractional bits (non-integral) will be stored here.         */
    tmpl_UInt64 fractional_bits;

    /*  Variable for the exponent, not offset by the bias.                    */
    unsigned int exponent;

    /*  Initialize the word to the input.                                     */
    word.f = x;

    /*  For |x| < 1, we have floor(x) = 0 or -1, depending on the sign.       */
    if (word.w.bits.expo < TMPL_LDOUBLE_BIAS)
    {
        /*  Regardless of the sign of x, zero should map to zero.             */
        if (x == 0.0L)
            return x;

        /*  For negative values, floor(x) = -1.                               */
        if (word.w.bits.sign)
            return -1.0L;

        /*  Otherwise, for 0 <= x < 1, floor(x) = 0.                          */
        return 0.0L;
    }

    /*  For very large inputs, there are no fractional bits. The input is     *
     *  already an integer. Return the input.                                 */
    if (word.w.bits.expo > TMPL_LDOUBLE_BIAS + 62U)
        return x;

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
        return x;

    /*  For negative non-integer values, floor(x) = -floor(|x|+1). We can     *
     *  compute the +1 term by adding to the 1's bit in the word. Note that   *
     *  this may result in a carry, and we need to handle this carefully.     */
    if (word.w.bits.sign)
    {
        /*  Add one to the 1's bit in the mantissa.                           */
        word.words.lo += 0x8000000000000000U >> exponent;

        /*  If a carry occurred, the integer part will be flipped to zero.    *
         *  All of the mantissa bits are zero, and we need to increment the   *
         *  exponent to reflect this.                                         */
        if (!word.w.bits.intr)
        {
            /*  Increment the exponent. The output is a power of 2.           */
            ++word.w.bits.expo;

            /*  Restore the integer part back to 1. This shouldn't have been  *
             *  flipped by the carry.                                         */
            word.w.bits.intr = 0x01U;
        }
    }

    /*  The floor function can be computed by zeroing out all of the          *
     *  fractional bits. This is achieved by using bit-wise and with the      *
     *  complement of the fractional bits.                                    */
    word.words.lo &= ~fractional_bits;

    /*  word now has the floor of the input. Output the long double part.     */
    return word.f;
}
/*  End of tmpl_LDouble_Floor.                                                */

#else
/*  Else for #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                          */

/*  This method does not require 64 bit integer types be available. It does   *
 *  require that IEEE-754 support for double is available. It is a little     *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  Function for computing the floor of a long double (floorl equivalent).    */
long double tmpl_LDouble_Floor(long double x)
{
    tmpl_IEEE754_LDouble w;
    w.r = x;

    /*  For arguments |x| < 1, either floor(x) = 0 or floor(x) = -1.          */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS)
    {
        /*  Regardless of the sign of x, zero should map to zero.             */
        if (x == 0.0L)
            return x;

        /*  For -1 < x < 0, we have floor(x) = -1.                            */
        if (w.bits.sign)
            return -1.0L;

        /*  And for 0 < x < 1, we get floor(x) = 0.                           */
        return 0.0L;
    }

    /*  For very large arguments, |x| >= 2^63, x is already an integer.       */
    if (w.bits.expo > TMPL_LDOUBLE_UBIAS + 62U)
        return x;

    /*  For |x| < 2^47, the floor function will zero out the last part of the *
     *  mantissa. man3 stores 16 bits, similar to man1 and man2.              */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x2FU)
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
        goto TMPL_LDOUBLE_FLOOR_FINISH;
    }

    /*  If |x| < 2^31, the second part of the mantissa is zeroed out as well. */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x1FU)
        w.bits.man2 = 0x00U;

    /*  Otherwise, if 2^31 <= |x| < 2^47, the highest part of the mantissa    *
     *  needs to be zeroed out, and the second high part must be modified.    */
    else
    {
        /*  Similar to before, create a bit-mask to zero out the fractional   *
         *  parts of the input. Since the upper 16 bits have already been     *
         *  zeroed out, we shift by 63 - 16 = 47, which is 0x2F in hex.       */
        w.bits.man2 &= (0xFFFFU << (0x2FU - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FLOOR_FINISH;
    }

    /*  If |x| < 2^15, the higher three parts of the mantissa all need to be  *
     *  zeroed out.                                                           */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x0FU)
        w.bits.man1 = 0x00U;

    /*  Otherwise, for 2^16 <= |x| < 2^20, zero out the upper two parts and   *
     *  modify the second lowest part.                                        */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 32 bits *
         *  have been zeroed out, so we shift by 52 - 32 = 20 (0x14 in hex).  */
        w.bits.man1 &= (0xFFFFU << (0x1FU - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FLOOR_FINISH;
    }

    /*  The lowest part of the mantissa is 15 bits, unlike the other 3 parts  *
     *  which are 16 bits each. Use a bit-mask to zero out the fractional     *
     *  part of the mantissa.                                                 */
    w.bits.man0 &= (0x7FFFU << (0x0FU - (w.bits.expo - TMPL_LDOUBLE_UBIAS)));

    /*  We need to handle positive and negative inputs carefully.             */
TMPL_LDOUBLE_FLOOR_FINISH:

    /*  For negative inputs, use floor(x) = -floor(-x) - 1. This is true      *
     *  unless the input was already an integer. Check for this.              */
    if (TMPL_LDOUBLE_IS_NEGATIVE(w) && w.r != x)
        return w.r - 1.0;

    /*  Otherwise w is now correctly set to the floor of the input.           */
    return w.r;
}
/*  End of tmpl_LDouble_Floor.                                                */

#endif
/*  End of #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                            */

/*  Double double, different from the rest. Uses two calls to double-floor.   */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                            128-Bit Double-Double                           *
 ******************************************************************************/

/*  Function for computing the floor of a long double (floorl equivalent).    */
long double tmpl_LDouble_Floor(long double x)
{
    unsigned int expo_diff;
    double floor_hi;
    tmpl_IEEE754_LDouble w;
    w.r = x;

    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
        return x;

    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS)
    {
        if (x == 0.0L)
            return x;

        if (TMPL_LDOUBLE_IS_NEGATIVE(w))
            return -1.0L;

        return 0.0L;
    }

    floor_hi = tmpl_Double_Floor(w.d[0]);

    if (w.d[0] != floor_hi)
        w.d[1] = 0.0;

    else
        w.d[1] = tmpl_Double_Floor(w.d[1]);

    w.d[0] = floor_hi;

    expo_diff = w.bits.expo - w.bits.expol;
    if ((expo_diff == 53U) && ((w.bits.man3 & 0x01U) != 0))
    {
        w.d[0] += 2.0*w.d[1];
        w.d[1] = -w.d[1];
    }

    else if (expo_diff < 53U)
    {
        w.d[0] += w.d[1];
        w.d[1] = 0.0;
    }

    return w.r;
}
/*  End of tmpl_LDouble_Floor.                                                */

/*  Quadruple, similar to 80-bit extended, but with more parts.               */
#else

/******************************************************************************
 *                            128-Bit Double-Double                           *
 ******************************************************************************/

/*  Check for 64-bit integer support.                                         */
#if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1

/*  tmpl_IEEE754_FloatIntLongDouble data type provided here.                  */
#include <libtmpl/include/tmpl_floatint.h>

/*  Function for computing the floor of a long double (floorl equivalent).    */
long double tmpl_LDouble_Floor(long double x)
{
    /*  Union of a long double with integers for type-punning.                */
    tmpl_IEEE754_FloatIntLongDouble word;

    /*  The lower fractional bits (non-integral) will be stored here.         */
    tmpl_UInt64 fractional_bits;

    /*  Variable for the exponent, not offset by the bias.                    */
    unsigned int exponent;

    /*  Initialize the word to the input.                                     */
    word.f = x;

    /*  For |x| < 1, we have floor(x) = 0 or -1, depending on the sign.       */
    if (word.w.bits.expo < TMPL_LDOUBLE_BIAS)
    {
        /*  Regardless of the sign of x, zero should map to zero.             */
        if (x == 0.0L)
            return x;

        /*  For negative values, floor(x) = -1.                               */
        if (word.w.bits.sign)
            return -1.0L;

        /*  Otherwise, for 0 <= x < 1, floor(x) = 0.                          */
        return 0.0L;
    }

    /*  For very large inputs, there are no fractional bits. The input is     *
     *  already an integer. Return the input.                                 */
    if (word.w.bits.expo > TMPL_LDOUBLE_BIAS + 111U)
        return x;

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
        word.words.lo = 0;
        fractional_bits = 0x0000FFFFFFFFFFFFU >> exponent;

        /*  If none of the fractional bits of the input are 1, then the input *
         *  was already an integer. Return the input.                         */
        if ((word.words.hi & fractional_bits) == 0)
            return x;

        /*  For negative non-integer values, floor(x) = -floor(|x|+1). We can *
         *  compute the +1 term by adding to the 1's bit in the word. Note    *
         *  that if this results in a carry, the sum will bleed over into the *
         *  exponent part. This is perfectly fine since a carry means the     *
         *  exponent must increase by 1, which is what the sum does.          */
        if (word.w.bits.sign)
            word.words.hi += 0x1000000000000U >> exponent;

        /*  The floor function can be computed by zeroing out all of the      *
         *  fractional bits. This is achieved by using bit-wise and with the  *
         *  complement of the fractional bits.                                */
        word.words.hi &= ~fractional_bits;
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
            return x;

        /*  Same trick as before with negative numbers, but we must handle    *
         *  the carry more carefully.                                         */
        if (word.w.bits.sign)
        {
            /*  We can compute |x| + 1 by adding 1 to the 1's bit of the word.*
             *  There are 112 bits in the mantissa, and "exponent" of them    *
             *  represent the integral part. Shifting 1 up by the difference  *
             *  will allow us to add to the correct part.                     */
            const tmpl_UInt64 tmp = word.words.lo + (0x01U << (112U-exponent));

            /*  Check if there was a carry. If the previous sum overflowed,   *
             *  tmp will now be smaller than the low word, since sums are     *
             *  computed mod 2^64. If this is the case, give the carry to the *
             *  high word.                                                    */
            if (tmp < word.words.lo)
                ++word.words.hi;

            /*  tmp now has the correct value for the low word.               */
            word.words.lo = tmp;
        }

        /*  Same trick as before, zero out the fractional bits.               */
        word.words.lo &= ~fractional_bits;
    }

    /*  word now has the floor of the input. Output the long double part.     */
    return word.f;
}
/*  End of tmpl_LDouble_Floor.                                                */

#endif
/*  End of #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                            */

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
