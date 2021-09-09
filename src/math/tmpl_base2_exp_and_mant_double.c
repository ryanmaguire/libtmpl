#include <libtmpl/include/tmpl_math.h>
#include <float.h>

#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1
void tmpl_Double_Base2_Exp_and_Mant(double x, double *mant, signed int *expo)
{
    tmpl_IEEE754_Double w;

    /*  If either of the input pointers are NULL, there's nothing to be done. */
    if (!mant || !expo)
        return;

    /*  Zero is a special value, and is represented as 0.0 * 2^0.             */
    if (x == 0.0)
    {
        *mant = 0.0;
        *expo = 0;
        return;
    }

    /*  Infinity is another special case. The mantissa will be set to         *
     *  infinity and the exponent will be set to zero.                        */
    else if (tmpl_Double_Is_Inf(x))
    {
        *mant = TMPL_INFINITY;
        *expo = 0;
        return;
    }

    /*  The last special case is NaN. expo will be zero, and mant will be nan.*/
    else if (tmpl_Double_Is_NaN(x))
    {
        *mant = TMPL_NAN;
        *expo = 0;
        return;
    }


    w.r = x;

    *expo = (signed int)w.bits.expo - 0x3FF;

    w.bits.expo = 0x3FFU;
    *mant = w.r;
}
#else

/*  This method does not assume IEEE-754 support, but instead of running in   *
 *  O(1) time, it runs in O(ln(m)), where m is the exponent of the input. So  *
 *  it roughly runs like O(ln(ln(max(|x|, |1/x|)))).                          */
void tmpl_Double_Base2_Exp_and_Mant(double x, double *mant, signed int *expo)
{
    /*  We'll compute the exponent using |x|, so compute this.                */
    double abs_x;

    /*  If either of the input pointers are NULL, there's nothing to be done. */
    if (!mant || !expo)
        return;

    /*  Zero is a special value, and is represented as 0.0 * 2^0.             */
    if (x == 0.0)
    {
        *mant = 0.0;
        *expo = 0;
        return;
    }

    /*  Infinity is another special case. The mantissa will be set to         *
     *  infinity and the exponent will be set to zero.                        */
    else if (tmpl_Double_Is_Inf(x))
    {
        *mant = TMPL_INFINITY;
        *expo = 0;
        return;
    }

    /*  The last special case is NaN. expo will be zero, and mant will be nan.*/
    else if (tmpl_Double_Is_NaN(x))
    {
        *mant = TMPL_NAN;
        *expo = 0;
        return;
    }

    /*  If we have a non-exceptional case, compute |x|.                       */
    abs_x = tmpl_Double_Abs((double)x);

    /*  If |x| < 1,0, compute with 1/|x|. We'll then negate the exponent at   *
     *  the end of the computation.                                           */
    if (abs_x < 1.0)
        *mant = 1.0 / abs_x;

    /*  If |x| >= 1.0, the exponent is non-negative. No need to invert.       */
    else
        *mant = abs_x;

    /*  Initialize the exponent to zero. The value will be computed by a sum. */
    *expo = 0;

    /*  The exponent is computed via it's binary representation. We find what *
     *  powers of 2 the value is greater than, and then divide by these,      *
     *  which amounts to zeroing out that particular value in the binary      *
     *  expansion of the exponent. Because of this, for values less than      *
     *  10^4932 (which is almost certainly beyond the bounds of float for     *
     *  your implementation), we can compute the mantissa and exponent in     *
     *  O(ln(ln(x))) time. To avoid compiler warnings about constants beyond  *
     *  the range of float, use the macro FLT_MAX_10_EXP to check the largest *
     *  power of 10 allowed.                                                  */
#if FLT_MAX_10_EXP > 4932

    /*  While it is likely not the case, if float has a range larger than     *
     *  10^4932, we should use a while loop to continuously decrease the      *
     *  the exponent until it is below this value. This is for the sake of    *
     *  portability. If float has a very large range, this part of the        *
     *  algorithm runs in O(ln(x)) time, instead of O(ln(ln(x))).             */
    while (*mant >= 1.1897314953572317650857593266280E4932)
    {
        *mant /= 1.1897314953572317650857593266280E4932;
        *expo += 16384;
    }
#endif
#if FLT_MAX_10_EXP > 2466
    while (*mant >= 1.0907481356194159294629842447338E2466)
    {
        *mant /= 1.0907481356194159294629842447338E2466;
        *expo += 8192;
    }
#endif
#if FLT_MAX_10_EXP > 1233
    while (*mant >= 1.0443888814131525066917527107166E1233)
    {
        *mant /= 1.0443888814131525066917527107166E1233;
        *expo += 4096;
    }
#endif
#if FLT_MAX_10_EXP > 616
    while (*mant >= 3.2317006071311007300714876688670E616)
    {
        *mant /= 3.2317006071311007300714876688670E616;
        *expo += 2048;
    }
#endif
#if FLT_MAX_10_EXP > 308
    while (*mant >= 1.7976931348623159077293051907890E308)
    {
        *mant /= 1.7976931348623159077293051907890E308;
        *expo += 1024;
    }
#endif
#if FLT_MAX_10_EXP > 154
    while (*mant >= 1.3407807929942597099574024998206E154)
    {
        *mant /= 1.3407807929942597099574024998206E154;
        *expo += 512;
    }
#endif
#if FLT_MAX_10_EXP > 77
    while (*mant >= 1.1579208923731619542357098500869E77)
    {
        *mant /= 1.1579208923731619542357098500869E77;
        *expo += 256;
    }
#endif
#if FLT_MAX_10_EXP > 38
    while (*mant >= 3.4028236692093846346337460743177E38)
    {
        *mant /= 3.4028236692093846346337460743177E38;
        *expo += 128;
    }
#endif
#if FLT_MAX_10_EXP > 19
    while (*mant >= 1.84467440737095516160E19)
    {
        *mant /= 1.84467440737095516160E19;
        *expo += 64;
    }
#endif
#if FLT_MAX_10_EXP > 9
    while (*mant >= 4.2949672960E9)
    {
        *mant /= 4.2949672960E9;
        *expo += 32;
    }
#endif

    if (*mant >= 65536.0)
    {
        *mant /= 65536.0;
        *expo += 16;
    }
    if (*mant >= 256.0)
    {
        *mant *= 0.003906250;
        *expo += 8;
    }
    if (*mant >= 16.0)
    {
        *mant *= 0.0625;
        *expo += 4;
    }
    if (*mant >= 4.0)
    {
        *mant *= 0.25;
        *expo += 2;
    }
    if (*mant >= 2.0)
    {
        *mant *= 0.5;
        *expo += 1;
    }

    /*  If |x| < 1, we need to negate the exponent since we computed the      *
     *  exponent of 1 / |x|. We also need to set mant to 1 / mant. This will  *
     *  result in mant < 1, so multiply by 2 and subtract 1 from the          *
     *  exponent. This will give us the correct value 1.m * 2^b.              */
    if (abs_x < 1.0)
    {
        *expo = -*expo - 1;
        *mant = 2.0 / *mant;
    }

    /*  If x was negative, negate mant so it has the proper sign.             */
    if (x < 0.0)
        *mant = -*mant;

}
/*  End of tmpl_Float_Base2_Exp_and_Mant.                                     */

#endif
/*  End #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1. */
