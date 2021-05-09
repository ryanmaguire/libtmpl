
/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

#if __TMPL_USE_IEEE754_ALGORITHMS__ != 0

#include <libtmpl/include/tmpl_ieee754.h>

float tmpl_Float_Log(float x)
{
	tmpl_IEEE754_Word32 w;
	float exponent, poly, A, A_sq;
	float mantissa, out;

	if (x < 0.0F)
		return tmpl_NaN_F;
	else if (x == 0.0F)
		return -tmpl_Infinity_F;
	else
		w.real = x;

	exponent = (float)tmpl_Get_Base_2_Exp32(w);
    mantissa = tmpl_Get_Mantissa32(w);

    if (mantissa > 1.5F)
    {
        mantissa *= 0.5F;
        exponent += 1.0F;
    }

    A = (mantissa - 1.0F)/(mantissa + 1.0F);
    A_sq = A*A;

    poly = 0.181818181F * A_sq + 0.222222222F;
    poly =         poly * A_sq + 0.285714285F;
    poly =         poly * A_sq + 0.400000000F;
    poly =         poly * A_sq + 0.666666667F;
    poly =         poly * A_sq + 2.000000000F;

	out = tmpl_Natural_Log_of_Two_F*exponent + A*poly;
	return out;
}

#elif __TMPL_HAS_C99_MATH_H__ == 1
#include <math.h>
/*  C99 provides float and long double support for their math functions, so   *
 *  simply use to these.                                                      */
float tmpl_Float_Log(float x)
{
    return logf(x);
}

#else

/*  C89 math.h does not have cosf or cosfl, so we'll need to provide these to  *
 *  make the code forward compatible. We'll do this in a very simple manner.  */
float tmpl_Float_Log(float x)
{
    unsigned long int exponent;
    float mant, A, A_sq, log_x;

    if (x < 0.0F)
        return tmpl_NaN_F;
    else if (x == 0.0F)
        return -tmpl_Infinity_F;

    if (x < 1.0F)
        mant = 1.0F/x;
    else
        mant = x;

    exponent = 0U;

    while (mant > 2.0F)
    {
        mant = 0.5F*mant;
        ++exponent;
    }

    A = (mant - 1.0F)/(mant + 1.0F);
    A_sq = A*A;

    log_x = 0.181818181F*A_sq + 0.222222222F;
    log_x = log_x*A_sq + 0.285714285F;
    log_x = log_x*A_sq + 0.400000000F;
    log_x = log_x*A_sq + 0.666666667F;
    log_x = log_x*A_sq + 2.000000000F;
    log_x = A*log_x;

    log_x = log_x + 0.69314718056F * (float)exponent;

    if (x < 1.0F)
        return -log_x;
    else
        return log_x;
}

#endif

