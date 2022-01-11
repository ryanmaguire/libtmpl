
/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Log(float x)
{
    float poly, A, A_sq, mantissa;
    signed int exponent;
    tmpl_IEEE754_Float w;

    if (x < 0.0F)
        return TMPL_NANF;
    else if (x == 0.0F)
        return -TMPL_INFINITYF;
    else if (tmpl_Float_Is_Inf(x))
        return x;
    else if (tmpl_Float_Is_NaN(x))
        return x;

    w.r = x;
    exponent = w.bits.expo - TMPL_FLOAT_BIAS;
    w.bits.expo = TMPL_FLOAT_BIAS;
    mantissa = w.r;

    if (mantissa > 1.5F)
    {
        mantissa *= 0.5F;
        exponent += 1;
    }

    A = (mantissa - 1.0F)/(mantissa + 1.0F);
    A_sq = A*A;

    poly = 0.181818181F * A_sq + 0.222222222F;
    poly =         poly * A_sq + 0.285714285F;
    poly =         poly * A_sq + 0.400000000F;
    poly =         poly * A_sq + 0.666666667F;
    poly =         poly * A_sq + 2.000000000F;

    return tmpl_Natural_Log_of_Two_F*(float)exponent + A*poly;
}
