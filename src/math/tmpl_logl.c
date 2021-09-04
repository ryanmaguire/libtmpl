

#include <libtmpl/include/tmpl_math.h>


#define TMPL_LOGL_A00 2.00000000000000000000000000000000L
#define TMPL_LOGL_A01 0.66666666666666666666666666666667L
#define TMPL_LOGL_A02 0.40000000000000000000000000000000L
#define TMPL_LOGL_A03 0.28571428571428571428571428571429L
#define TMPL_LOGL_A04 0.22222222222222222222222222222222L
#define TMPL_LOGL_A05 0.18181818181818181818181818181818L
#define TMPL_LOGL_A06 0.15384615384615384615384615384615L
#define TMPL_LOGL_A07 0.13333333333333333333333333333333L
#define TMPL_LOGL_A08 0.11764705882352941176470588235294L
#define TMPL_LOGL_A09 0.10526315789473684210526315789474L
#define TMPL_LOGL_A10 0.095238095238095238095238095238095L
#define TMPL_LOGL_A11 0.086956521739130434782608695652174L
#define TMPL_LOGL_A12 0.080000000000000000000000000000000L

/* 
 * Not needed.
 * #define TMPL_LOGL_A13 0.074074074074074074074074074074074L
 * #define TMPL_LOGL_A14 0.068965517241379310344827586206897L
 * #define TMPL_LOGL_A15 0.064516129032258064516129032258065L
 */

long double tmpl_LDouble_Log(long double x)
{
    long double mantissa, A, A_sq, poly;
    signed long int exponent;

    if (x < 0.0L)
        return tmpl_NaN_L;
    else if (x == 0.0L)
        return -tmpl_Infinity_L;

    tmpl_LDouble_Base2_Exp_and_Mant(x, &mantissa, &exponent);

    if (mantissa > 1.5L)
    {
        mantissa *= 0.5L;
        exponent += 1L;
    }

    A = (mantissa - 1.0L) / (mantissa + 1.0L);
    A_sq = A*A;

    poly = TMPL_LOGL_A12*A_sq + TMPL_LOGL_A11;
    poly = poly * A_sq + TMPL_LOGL_A10;
    poly = poly * A_sq + TMPL_LOGL_A09;
    poly = poly * A_sq + TMPL_LOGL_A08;
    poly = poly * A_sq + TMPL_LOGL_A07;
    poly = poly * A_sq + TMPL_LOGL_A06;
    poly = poly * A_sq + TMPL_LOGL_A05;
    poly = poly * A_sq + TMPL_LOGL_A04;
    poly = poly * A_sq + TMPL_LOGL_A03;
    poly = poly * A_sq + TMPL_LOGL_A02;
    poly = poly * A_sq + TMPL_LOGL_A01;
    poly = poly * A_sq + TMPL_LOGL_A00;

    return tmpl_Natural_Log_of_Two_L*(long double)exponent + A*poly;
}

#undef TMPL_LOGL_A00
#undef TMPL_LOGL_A01
#undef TMPL_LOGL_A02
#undef TMPL_LOGL_A03
#undef TMPL_LOGL_A04
#undef TMPL_LOGL_A05
#undef TMPL_LOGL_A06
#undef TMPL_LOGL_A07
#undef TMPL_LOGL_A08
#undef TMPL_LOGL_A09
#undef TMPL_LOGL_A10
#undef TMPL_LOGL_A11
#undef TMPL_LOGL_A12
