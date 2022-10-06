/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_ARCTAN_MACLAURIN_INLINE_H
#define TMPL_MATH_ARCTAN_MACLAURIN_INLINE_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

/*  IEEE-754 data types and macros found here.                                */
#include <libtmpl/include/tmpl_math.h>

#define A0 (1.00000000000000000000F)
#define A1 (-3.33333333333329318027E-01F)
#define A2 (1.99999999998764832476E-01F)
#define A3 (-1.42857142725034663711E-01F)
#define A4 (1.11111104054623557880E-01F)

/*  This function computes arctan(x) via a MacLaurin series for small |x|.    */
static inline float tmpl_Float_Arctan_Maclaurin(float x)
{
    /*  Declare necessary variables.                                          */
    const float x2 = x*x;
    return x*(A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*A4))));
}
/*  End of tmpl_Float_Arctan_Maclaurin.                                       */

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4

#define A0 (1.00000000000000000000000000000E+00)
#define A1 (-3.33333333333333333333333333333E-01)
#define A2 (2.00000000000000000000000000000E-01)
#define A3 (-1.42857142857142857142857142857E-01)
#define A4 (1.11111111111111111111111111111E-01)
#define A5 (-9.09090909090909090909090909090E-02)
#define A6 (7.69230769230769230769230769231E-02)
#define A7 (-6.66666666666666666666666666667E-02)
#define A8 (5.88235294117647058823529411765E-02)

/*  Maclaurin series for arctan, double precision, to 9 terms.                */
static inline double tmpl_Double_Arctan_Maclaurin(double x)
{
    /*  Declare necessary variables.                                          */
    const double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0+x2*(A1+x2*(A2+x2*(A3+x2*(A4+x2*(A5+x2*(A6+x2*(A7+x2*A8))))))));
}
/*  End of tmpl_Double_Arctan_Maclaurin.                                      */

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7
#undef A8

#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

#define A0 (1.00000000000000000000)
#define A1 (-3.33333333333329318027E-01)
#define A2 (1.99999999998764832476E-01)
#define A3 (-1.42857142725034663711E-01)
#define A4 (1.11111104054623557880E-01)
#define A5 (-9.09088713343650656196E-02)
#define A6 (7.69187620504482999495E-02)
#define A7 (-6.66107313738753120669E-02)
#define A8 (5.83357013379057348645E-02)

/*  Maclaurin series for arctan, double precision, to 9 terms.                */
static inline long double tmpl_LDouble_Arctan_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0+x2*(A1+x2*(A2+x2*(A3+x2*(A4+x2*(A5+x2*(A6+x2*(A7+x2*A8))))))));
}
/*  End of tmpl_Double_Arctan_Maclaurin.                                      */

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7
#undef A8

#else

#define A00 (1.00000000000000000000000000000000000E00L)
#define A01 (-3.33333333333333333333333333333333333E-01L)
#define A02 (2.00000000000000000000000000000000000E-01L)
#define A03 (-1.42857142857142857142857142857142857E-01L)
#define A04 (1.11111111111111111111111111111111111E-01L)
#define A05 (-9.09090909090909090909090909090909091E-02L)
#define A06 (7.69230769230769230769230769230769231E-02L)
#define A07 (-6.66666666666666666666666666666666667E-02L)
#define A08 (5.88235294117647058823529411764705882E-02L)
#define A09 (-5.26315789473684210526315789473684211E-02L)
#define A10 (4.7619047619047619047619047619047619E-02L)
#define A11 (-4.34782608695652173913043478260869565E-02L)

/*  Taylor series centered at x0 = 0 for atan(x).                             */
static inline long double tmpl_LDouble_Arctan_Maclaurin(long double x)
{
    /*  The Taylor series for atan(x) is in terms of x^{2n+1}. Compute the    *
     *  square of x and use this for the series.                              */
    const long double x2 = x*x;

    /*  Use Horner's method to efficiently evaluate the polynomial.           */
    return x*(
        A00 + x2*(
            A01 + x2*(
                A02 + x2*(
                    A03 + x2*(
                        A04 + x2*(
                            A05 + x2*(
                                A06 + x2*(
                                    A07 + x2*(
                                        A08 + x2*(
                                            A09 + x2*(
                                                A10 + x2*A11
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
}
/*  End of tmpl_LDouble_Arctan_Maclaurin.                                     */

#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef A11

#endif
/*  End difference between 64-bit long double and higher precisions.          */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
