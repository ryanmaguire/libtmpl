/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_ieee754.h>

#if __TMPL_USE_LOG_ALGORITHM__ != 0

static float __log_coeffs_f[6] = {
    2.000000000F,
    0.666666667F,
    0.400000000F,
    0.285714285F,
    0.222222222F,
    0.181818181F
};

static double __log_coeffs[11] = {
    2.0000000000000000,
    0.66666666666666667,
    0.40000000000000000,
    0.28571428571428571,
    0.22222222222222222,
    0.18181818181818182,
    0.15384615384615385,
    0.13333333333333333,
    0.11764705882352941,
    0.10526315789473684,
    0.095238095238095238
};

float tmpl_Float_Log(float x)
{
	tmpl_IEE754_Word32 w, frac;
	tmpl_uint32 low, high;
	float exponent, poly, A, A_sq;
	float out;

	if (x < 0.0F)
		return tmpl_NaN_F;
	else if (x == 0.0F)
		return -tmpl_Infinity_F;
	else
		w.real = x;

	low  = tmpl_Get_Low_Word32(w);
	high = tmpl_Get_High_Word32(w);

	exponent = (float)high - 127.0F;
	frac.integer = 0x3F800000 + low;
    A = (frac.real - 1.0F)/(frac.real + 1.0F);
    A_sq = A*A;
    poly = tmpl_Real_Poly_Float_Coeffs(__log_coeffs_f, 5U, A_sq);

	out = tmpl_Natural_Log_of_2_F*exponent + A*poly;
	return out;
}

double tmpl_Double_Log(double x)
{
	tmpl_IEE754_Word64 w, frac;
	tmpl_uint64 low, high;
	double exponent, poly, A, A_sq;
	double out;

	if (x < 0.0)
		return tmpl_NaN;
	else if (x == 0.0)
		return -tmpl_Infinity;
	else
		w.real = x;

	low  = tmpl_Get_Low_Word64(w);
	high = tmpl_Get_High_Word64(w);

	exponent = (double)high - 1023.0;
	frac.integer = (0x3FFUL << 52) + low;
    A = (frac.real-1.0)/(frac.real+1);
    A_sq = A*A;
    poly = tmpl_Real_Poly_Double_Coeffs(__log_coeffs, 10U, A_sq);

	out = tmpl_Natural_Log_of_2*exponent + A*poly;
	return out;
}

long double tmpl_LDouble_Log(long double x)
{
    return (long double)tmpl_Double_Log((double) x);
}

#else

/*  The "double" version of cos is defined in both C89 and C99 math.h so we   *
 *  only need to alias this function.                                         */
double tmpl_Double_Log(double x)
{
    return log(x);
}

#if __TMPL_HAS_C99_MATH_H__ == 0

/*  C89 math.h does not have cosf or cosfl, so we'll need to provide these to  *
 *  make the code forward compatible. We'll do this in a very simple manner.  */
float tmpl_Float_Log(float x)
{
    return (float)log((double)x);
}

long double tmpl_LDouble_Log(long double x)
{
    return (long double)log((double)x);
}

/*  Now have the functions declared in rss_ringoccs_math.h point to these.    */
#else

/*  C99 provides float and long double support for their math functions, so   *
 *  simply use to these.                                                      */
float tmpl_Float_Log(float x)
{
    return logf(x);
}

long double tmpl_LDouble_Log(long double x)
{
    return logl(x);
}
#endif
/*  End of #if __HAS_C99_MATH_H__ == 0                                        */

#endif
/*  End of #if __TMPL_USE_LOG_ALGORITHM__ != 0.                               */
