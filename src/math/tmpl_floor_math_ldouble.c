

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

/*  Function for computing the floor of a double (floorl equivalent).         */
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

/*  Function for computing the floor of a double (floorl equivalent).         */
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
        goto TMPL_LDOUBLE_FLOOR_FINISH;
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
        goto TMPL_LDOUBLE_FLOOR_FINISH;
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
        goto TMPL_LDOUBLE_FLOOR_FINISH;
    }

    /*  The lowest part of the mantissa is 4 bits, unlike the other 3 parts   *
     *  which are 16 bits each. Use a bit-mask to zero out the fractional     *
     *  part of the mantissa.                                                 */
    w.bits.man0 &= (0x000FU << (0x04U - (w.bits.expo - TMPL_DOUBLE_UBIAS)));

    /*  We need to handle positive and negative inputs carefully.             */
TMPL_LDOUBLE_FLOOR_FINISH:

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

/*  Function for computing the floor of a double (floorl equivalent).         */
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
        fractional_bits = 0x0000FFFFFFFFFFFFU >> exponent;

        /*  If none of the fractional bits of the input are 1, then the input *
         *  was already an integer. Return the input.                         */
        if (((word.words.hi & fractional_bits) | word.words.lo) == 0)
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

#else
/*  Else for #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                          */

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

    /*  For very large arguments, |x| >= 2^112, x is already an integer.      */
    if (w.bits.expo > TMPL_LDOUBLE_UBIAS + 111U)
        return x;

    /*  For |x| < 2^96, the floor function will zero out the last part of the *
     *  mantissa. man6 stores 16 bits, similar to all other parts.            */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x60U)
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
        goto TMPL_LDOUBLE_FLOOR_FINISH;
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
        goto TMPL_LDOUBLE_FLOOR_FINISH;
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
        goto TMPL_LDOUBLE_FLOOR_FINISH;
    }

    /*  If |x| < 2^64, the higher three parts of the mantissa all need to be  *
     *  zeroed out.                                                           */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x30U)
        w.bits.man3 = 0x00U;

    /*  Otherwise, for 2^64 <= |x| < 2^80, zero out the upper two parts and   *
     *  modify the second lowest part.                                        */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 32 bits *
         *  have been zeroed out, so we shift by 112 - 32 = 80 (0x50 in hex). */
        w.bits.man3 &= (0xFFFFU << (0x40U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FLOOR_FINISH;
    }

    /*  If |x| < 2^64, the higher three parts of the mantissa all need to be  *
     *  zeroed out.                                                           */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x20U)
        w.bits.man2 = 0x00U;

    /*  Otherwise, for 2^64 <= |x| < 2^80, zero out the upper two parts and   *
     *  modify the second lowest part.                                        */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 32 bits *
         *  have been zeroed out, so we shift by 112 - 32 = 80 (0x50 in hex). */
        w.bits.man2 &= (0xFFFFU << (0x30U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FLOOR_FINISH;
    }

    /*  If |x| < 2^64, the higher three parts of the mantissa all need to be  *
     *  zeroed out.                                                           */
    if (w.bits.expo < TMPL_LDOUBLE_UBIAS + 0x10U)
        w.bits.man1 = 0x00U;

    /*  Otherwise, for 2^64 <= |x| < 2^80, zero out the upper two parts and   *
     *  modify the second lowest part.                                        */
    else
    {
        /*  Use a bit-mask to zero out the fractional part. The upper 32 bits *
         *  have been zeroed out, so we shift by 112 - 32 = 80 (0x50 in hex). */
        w.bits.man1 &= (0xFFFFU << (0x20U - (w.bits.expo-TMPL_LDOUBLE_UBIAS)));
        goto TMPL_LDOUBLE_FLOOR_FINISH;
    }

    /*  Same bit-wise trick for the last part of the mantissa.                */
    w.bits.man0 &= (0xFFFFU << (0x10U - (w.bits.expo - TMPL_LDOUBLE_UBIAS)));

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

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/*  Powers of 2, 2^n, for n = 0 to n = 64.                                    */
static const long double tmpl_ldouble_pow_2_table[65] = {
    1.0L, 2.0L, 4.0L, 8.0L, 16.0L, 32.0L, 64.0L, 128.0L, 256.0L, 512.0L,
    1024.0L, 2048.0L, 4096.0L, 8192.0L, 16384.0L, 32768.0L, 65536.0L,
    131072.0L, 262144.0L, 524288.0L, 1048576.0L, 2097152.0L, 4194304.0L,
    8388608.0L, 16777216.0L, 33554432.0L, 67108864.0L, 134217728.0L,
    268435456.0L, 536870912.0L, 1073741824.0L,
    2147483648.0L, 4294967296.0L, 8589934592.0L,
    17179869184.0L, 34359738368.0L, 68719476736.0L,
    137438953472.0L, 274877906944.0L, 549755813888.0L,
    1099511627776.0L, 2199023255552.0L, 4398046511104.0L,
    8796093022208.0L, 17592186044416.0L, 35184372088832.0L,
    70368744177664.0L, 140737488355328.0L, 281474976710656.0L,
    562949953421312.0L, 1125899906842624.0L, 2251799813685248.0L,
    4503599627370496.0L, 9007199254740992.0L, 18014398509481984.0L,
    36028797018963968.0L, 72057594037927936.0L, 144115188075855872.0L,
    288230376151711744.0L, 576460752303423488.0L, 1152921504606846976.0L,
    2305843009213693952.0L, 4611686018427387904.0L, 9223372036854775808.0L,
    18446744073709551616.0L
};

/*  Function for computing the floor of a double (floorl equivalent).         */
long double tmpl_LDouble_Floor(long double x)
{
    long double abs_x, mant, y, out;
    signed int expo;

    /*  Special case, floor(0) = 0.                                           */
    if (x == 0.0L)
        return x;

    /*  Next special case, NaN or inf. Return the input.                      */
    if (tmpl_LDouble_Is_NaN_Or_Inf(x))
        return x;

    /*  Get the numbers mant and expo such that x = mant * 2^expo with        *
     *  1 <= |mant| < 2. That is, the base 2 scientific notation of x.        */
    tmpl_LDouble_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  If expo < 0 we have |x| < 1. floor(x) = 0 if x >= 0 and -1 otherwise. */
    if (expo < 0)
    {
        /*  For negative values, -1 < x < 0, we have floor(x) = -1.           */
        if (x < 0.0L)
            return -1.0L;

        /*  Otherwise, for 0 < x < 1, we have floor(x) = 0.                   */
        return 0.0L;
    }

    /*  This function is only accurate to 64 bits in the mantissa. For most   *
     *  machines the mantissa has 52 bits, so this is probably overkill.      */
    else if (expo > 64)
        return x;

    /*  Use the fact that floor(x) = -1 - floor(-x) for negative non-integer  *
     *  values to reduce the argument.                                        */
    abs_x = tmpl_LDouble_Abs(x);

    /*  We're going to "zero" the highest bit of the integer part of abs_x    *
     *  by substracting it off. Compute this from the lookup table.           */
    y = tmpl_ldouble_pow_2_table[expo];

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
        y = tmpl_ldouble_pow_2_table[expo];

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
    if (x < 0.0L)
    {
        /*  The formula does not work for integers. If the input was an       *
         *  integer to begin with, return it.                                 */
        if (x == -out)
            return x;

        /*  Otherwise, use the negation formula and return.                   */
        return -1.0L - out;
    }

    /*  For positive values, we are done with the computation.                */
    return out;
}
/*  End of tmpl_LDouble_Floor.                                                */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
