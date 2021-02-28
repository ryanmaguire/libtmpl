/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

#if __TMPL_USE_IEEE754_ALGORITHMS__ != 0
#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_ieee754.h>

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

double tmpl_Double_Log(double x)
{
	tmpl_IEEE754_Word64 w, frac;
	tmpl_uint64 low;
    tmpl_uint32 high;
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

#else

/*  The "double" version of cos is defined in both C89 and C99 math.h so we   *
 *  only need to alias this function.                                         */
double tmpl_Double_Log(double x)
{
    return log(x);
}

#endif

