/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

#if __TMPL_USE_IEEE754_ALGORITHMS__ != 0
#include <libtmpl/include/tmpl_ieee754.h>

double tmpl_Double_Log(double x)
{
	tmpl_IEEE754_Word64 w;
	double exponent, mantissa, poly, A, A_sq;
	double out;

	if (x < 0.0)
		return tmpl_NaN;
	else if (x == 0.0)
		return -tmpl_Infinity;
	else
		w.real = x;

	exponent = (double)tmpl_Get_Base_2_Exp64(w);
    mantissa = tmpl_Get_Mantissa64(w);

    if (mantissa > 1.5)
    {
        mantissa *= 0.5;
        exponent += 1.0;
    }

    A = (mantissa - 1.0) / (mantissa + 1);
    A_sq = A*A;

    poly = 0.095238095238095238 * A_sq + 0.10526315789473684;
    poly =                 poly * A_sq + 0.11764705882352941;
    poly =                 poly * A_sq + 0.13333333333333333;
    poly =                 poly * A_sq + 0.15384615384615385;
    poly =                 poly * A_sq + 0.18181818181818182;
    poly =                 poly * A_sq + 0.22222222222222222;
    poly =                 poly * A_sq + 0.28571428571428571;
    poly =                 poly * A_sq + 0.40000000000000000;
    poly =                 poly * A_sq + 0.66666666666666667;
    poly =                 poly * A_sq + 2.0000000000000000;

	out = tmpl_Natural_Log_of_Two*exponent + A*poly;
	return out;
}

#else
#include <math.h>
/*  The "double" version of cos is defined in both C89 and C99 math.h so we   *
 *  only need to alias this function.                                         */
double tmpl_Double_Log(double x)
{
    return log(x);
}

#endif

