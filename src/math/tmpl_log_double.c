/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

double tmpl_Double_Log(double x)
{
    double mantissa, poly, A, A_sq;
    signed int exponent;

    if (x < 0.0)
        return TMPL_NAN;
    else if (x == 0.0)
        return -TMPL_INFINITY;

    tmpl_Double_Base2_Exp_and_Mant(x, &mantissa, &exponent);

    if (mantissa > 1.5)
    {
        mantissa *= 0.5;
        exponent += 1;
    }

    A = (mantissa - 1.0) / (mantissa + 1.0);
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

    return tmpl_Natural_Log_of_Two*exponent + A*poly;
}

#else 

#include <math.h>

double tmpl_Double_Log(double x)
{
    return log(x);
}

#endif
