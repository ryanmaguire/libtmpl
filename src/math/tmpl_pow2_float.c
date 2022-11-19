
#include <libtmpl/include/tmpl_math.h>

#if TMPL_HAS_IEEE754_FLOAT == 1

float tmpl_Float_Pow2(signed int expo)
{
    tmpl_IEEE754_Float w;
    w.r = 1.0F;

    if (expo <= -TMPL_FLOAT_BIAS)
    {
        if (expo < -TMPL_FLOAT_BIAS - TMPL_FLOAT_MANTISSA_LENGTH)
            return 0.0F;

        expo += TMPL_FLOAT_MANTISSA_LENGTH;
        w.bits.expo =
            (unsigned int)(TMPL_FLOAT_BIAS + expo) & TMPL_FLOAT_NANINF_EXP;
        w.r /= TMPL_FLOAT_NORMALIZE;
        return w.r;
    }
    else if (expo > TMPL_FLOAT_BIAS)
    {
        w.bits.expo = TMPL_FLOAT_NANINF_EXP;
        return w.r;
    }

    w.bits.expo =
        (unsigned int)(TMPL_FLOAT_BIAS + expo) & TMPL_FLOAT_NANINF_EXP;
    return w.r;
}

#else

#include <libtmpl/include/tmpl_integer.h>
#include <float.h>

float tmpl_Float_Pow2(signed int expo)
{
    signed int n;
    float x = 1.0F;

    if (expo == 0)
        return x;

    n = tmpl_Int_Abs(expo);

#if FLT_MAX_10_EXP > 154
#define TWO_TO_THE_512 \
(1.3407807929942597099574024998205846127479365820592393377723561443\
721764030073546976801874298166903427690031858186486050853753882811\
946569946433649006084096E+154F)
    while (n >= 512)
    {
        x *= TWO_TO_THE_512;
        n -= 512;
    }
#undef TWO_TO_THE_512
#endif
/*  End of #if FLT_MAX_10_EXP > 154.                                          */

#if FLT_MAX_10_EXP > 77
#define \
TWO_TO_THE_256 \
(1.1579208923731619542357098500868\
7907853269984665640564039457584007913129639936E+77F)
    while (n >= 256)
    {
        x *= TWO_TO_THE_256;
        n -= 256;
    }
#undef TWO_TO_THE_256
#endif
/*  End of #if FLT_MAX_10_EXP > 77.                                           */

#if FLT_MAX_10_EXP > 38
#define TWO_TO_THE_128 (3.40282366920938463463374607431768211456E+38F)
    while (n >= 128)
    {
        x *= TWO_TO_THE_128;
        n -= 128;
    }
#undef TWO_TO_THE_128
#endif
/*  End of #if FLT_MAX_10_EXP > 38.                                           */

#if FLT_MAX_10_EXP > 19
#define TWO_TO_THE_64 (1.8446744073709551616E+19F)
    while (n >= 64)
    {
        x *= TWO_TO_THE_64;
        n -= 64;
    }
#undef TWO_TO_THE_64
#endif
/*  End of #if FLT_MAX_10_EXP > 19.                                           */

#if FLT_MAX_10_EXP > 9
#define TWO_TO_THE_32 (4.294967296E+09F)
    while (n >= 32)
    {
        x *= TWO_TO_THE_32;
        n -= 32;
    }
#undef TWO_TO_THE_32
#endif
/*  End of #if FLT_MAX_10_EXP > 9.                                            */

    while (n >= 16)
    {
        x *= 65536.0F;
        n -= 16;
    }

    if (n >= 8)
    {
        x *= 256.0F;
        n -= 8;
    }

    if (n >= 4)
    {
        x *= 16.0F;
        n -= 4;
    }

    if (n >= 2)
    {
        x *= 4.0F;
        n -= 2;
    }

    if (n >= 1)
    {
        x *= 2.0F;
        n -= 1;
    }

    if (expo < 0)
        return 1.0F / x;
    else
        return x;
}

#endif
