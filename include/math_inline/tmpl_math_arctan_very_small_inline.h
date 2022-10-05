#ifndef TMPL_MATH_ARCTAN_VERY_SMALL_INLINE_H
#define TMPL_MATH_ARCTAN_VERY_SMALL_INLINE_H

#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE == 1

#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the computation of the polynomial approximation. The     *
 *  coefficients for the Taylor series are 1 / (1 + 2n).                      */
#define A0 (1.0F)
#define A1 (-3.33333333333329318027E-01F)
#define A2 (1.99999999998764832476E-01F)
#define A3 (-1.42857142725034663711E-01F)

static inline float tmpl_Float_Arctan_Very_Small(float x)
{
    const float x2 = x*x;
    return x*(A0 + x2*(A1 + x2*(A2 + x2*A3)));
}

#undef A0
#undef A1
#undef A2
#undef A3

#define A0 (1.0)
#define A1 (-3.33333333333329318027E-01)
#define A2 (1.99999999998764832476E-01)
#define A3 (-1.42857142725034663711E-01)
#define A4 (1.11111104054623557880E-01)
#define A5 (-9.09088713343650656196E-02)

static inline double tmpl_Double_Arctan_Very_Small(double x)
{
      const double x2 = x*x;
      return x*(A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*(A4 + x2*A5)))));
}

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

#define A0 (1.0L)
#define A1 (-3.33333333333329318027E-01L)
#define A2 (1.99999999998764832476E-01L)
#define A3 (-1.42857142725034663711E-01L)
#define A4 (1.11111104054623557880E-01L)
#define A5 (-9.09088713343650656196E-02L)

static inline long double tmpl_LDouble_Arctan_Very_Small(long double x)
{
      const long double x2 = x*x;
      return x*(A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*(A4 + x2*A5)))));
}

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#else

/*  For very small values we need fewer terms to get with 1 ULP.              */
static inline long double tmpl_LDouble_Arctan_Very_Small(long double x)
{
    /*  The Taylor series for atan(x) is in terms of x^{2n+1}. Compute the    *
     *  square of x and use this for the series.                              */
    const long double x_sq = x*x;

    /*  Use Horner's method to efficiently evaluate the polynomial.           */
    long double out = -0.0666666666666666666666666666666666667L * x_sq
                    + 0.0769230769230769230769230769230769231L;
    out = out*x_sq - 0.0909090909090909090909090909090909091L;
    out = out*x_sq + 0.111111111111111111111111111111111111L;
    out = out*x_sq - 0.142857142857142857142857142857142857L;
    out = out*x_sq + 0.200000000000000000000000000000000000L;
    out = out*x_sq - 0.333333333333333333333333333333333333L;
    out = out*x_sq + 1.000000000000000000000000000000000000L;

    /*  The Taylor series is in terms of x^{2n+1}, not x^{2n}. Multiplying    *
     *  by the input gives us the correct result.                             */
    return x*out;
}
/*  End of tmpl_LDouble_Arctan_Very_Small.                                    */

#endif
#endif
#endif
