#include <libtmpl/include/tmpl_math.h>

#if TMPL_HAS_IEEE754_FLOAT == 1
void tmpl_Float_Base2_Mant_and_Exp(float x, float *mant, signed int *expo)
{
    tmpl_IEEE754_Float w;

    /*  If either of the input pointers are NULL, there's nothing to be done. */
    if (!mant || !expo)
        return;

    w.r = x;
    w.bits.sign = 0x00U;

    /*  NaN or Inf. Set exponent to zero and mant to the input.               */
    if (w.bits.expo == TMPL_FLOAT_NANINF_EXP)
    {
        *mant = x;
        *expo = 0;
        return;
    }

    /*  Subnormal or zero.                                                    */
    else if (w.bits.expo == 0x00U)
    {
        /*  x = 0. Set mant to the input and expo to zero.                    */
        if (w.r == 0.0F)
        {
            *mant = x;
            *expo = 0;
            return;
        }

        /*  Non-zero subnormal number. Normalize by multiplying by 2^23,      *
         *  which is 8.388608 x 10^6.                                         */
        w.r *= 8.388608E6F;

        /*  Compute the exponent. Since we multiplied by 2^23, subtract 23    *
         *  from the value.                                                   */
        *expo = (signed int)(w.bits.expo - TMPL_FLOAT_BIAS - 23);
        w.bits.expo = TMPL_FLOAT_BIAS;
        *mant = w.r;
        return;
    }

    *expo = (signed int)w.bits.expo - TMPL_FLOAT_BIAS;
    w.bits.expo = TMPL_FLOAT_BIAS;
    *mant = w.r;
}
#else

#include <float.h>

/*  This method does not assume IEEE-754 support, but instead of running in   *
 *  O(1) time, it runs in O(ln(m)), where m is the exponent of the input. So  *
 *  it roughly runs like O(ln(ln(max(|x|, |1/x|)))).                          */
void tmpl_Float_Base2_Mant_and_Exp(float x, float *mant, signed int *expo)
{
    /*  We'll compute the exponent using |x|, so compute this.                */
    float abs_x;

    /*  If either of the input pointers are NULL, there's nothing to be done. */
    if (!mant || !expo)
        return;

    /*  Zero is a special value, and is represented as 0.0 * 2^0.             */
    if (x == 0.0F)
    {
        *mant = 0.0F;
        *expo = 0;
        return;
    }

    /*  Infinity is another special case. The mantissa will be set to         *
     *  infinity and the exponent will be set to zero.                        */
    else if (tmpl_Float_Is_Inf(x))
    {
        *mant = TMPL_INFINITYF;
        *expo = 0;
        return;
    }

    /*  The last special case is NaN. expo will be zero, and mant will be nan.*/
    else if (tmpl_Float_Is_NaN(x))
    {
        *mant = TMPL_NANF;
        *expo = 0;
        return;
    }

    /*  If we have a non-exceptional case, compute |x|.                       */
    abs_x = tmpl_Float_Abs(x);

    /*  If |x| < 1,0, compute with 1/|x|. We'll then negate the exponent at   *
     *  the end of the computation.                                           */
    if (abs_x < 1.0F)
        *mant = 1.0F / abs_x;

    /*  If |x| >= 1.0, the exponent is non-negative. No need to invert.       */
    else
        *mant = abs_x;

    /*  Initialize the exponent to zero. The value will be computed by a sum. */
    *expo = 0;

    /*  The exponent is computed via it's binary representation. We find what *
     *  powers of 2 the value is greater than, and then divide by these,      *
     *  which amounts to zeroing out that particular value in the binary      *
     *  expansion of the exponent. Because of this, for values less than      *
     *  10^308 (which is almost certainly beyond the bounds of float for      *
     *  your implementation), we can compute the mantissa and exponent in     *
     *  O(ln(ln(x))) time. To avoid compiler warnings about constants beyond  *
     *  the range of float, use the macro DBL_MAX_10_EXP to check the         *
     *  largest power of 10 allowed.                                          */
#if FLT_MAX_10_EXP > 154
    while (*mant >= 1.34078079299425971E154F)
    {
        *mant /= 1.34078079299425971E154F;
        *expo += 512;
    }
#endif
#if FLT_MAX_10_EXP > 77
    while (*mant >= 1.15792089237316195E77F)
    {
        *mant /= 1.15792089237316195E77F;
        *expo += 256;
    }
#endif
#if FLT_MAX_10_EXP > 38
    while (*mant >= 3.40282366920938463E38F)
    {
        *mant /= 3.40282366920938463E38F;
        *expo += 128;
    }
#endif
#if FLT_MAX_10_EXP > 19
    while (*mant >= 1.84467440737095516E19F)
    {
        *mant /= 1.84467440737095516E19F;
        *expo += 64;
    }
#endif
#if FLT_MAX_10_EXP > 9
    while (*mant >= 4.29496729600000000E09F)
    {
        *mant /= 4.29496729600000000E09F;
        *expo += 32;
    }
#endif

    while (*mant >= 65536.0F)
    {
        *mant /= 65536.0F;
        *expo += 16;
    }
    if (*mant >= 256.0F)
    {
        *mant /= 256.0F;
        *expo += 8;
    }
    if (*mant >= 16.0F)
    {
        *mant /= 16.0F;
        *expo += 4;
    }
    if (*mant >= 4.0F)
    {
        *mant *= 0.25F;
        *expo += 2;
    }
    if (*mant >= 2.0F)
    {
        *mant *= 0.5F;
        *expo += 1;
    }

    /*  If |x| < 1, we need to negate the exponent since we computed the      *
     *  exponent of 1 / |x|. We also need to set mant to 1 / mant. This will  *
     *  result in mant < 1, so multiply by 2 and subtract 1 from the          *
     *  exponent. This will give us the correct value 1.m * 2^b.              */
    if (abs_x < 1.0F)
    {
        /*  Special case, if mant = 1, no need to subtract 1 or compute       *
         *  the reciprocal of mant. Just negate the exponent.                 */
        if (*mant == 1.0F)
            *expo = -*expo;
        else
        {
            *expo = -*expo - 1;
            *mant = 2.0F / *mant;
        }
    }

    /*  If x was negative, negate mant so it has the proper sign.             */
    if (x < 0.0F)
        *mant = -*mant;

}
/*  End of tmpl_Float_Base2_Mant_And_Exp.                                     */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */
