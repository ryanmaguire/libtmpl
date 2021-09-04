
/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Log(float x)
{
    float poly, A, A_sq, mantissa;
    signed int exponent;

    if (x < 0.0F)
        return tmpl_NaN_F;
    else if (x == 0.0F)
        return -tmpl_Infinity_F;

    tmpl_Float_Base2_Exp_and_Mant(x, &mantissa, &exponent);

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
