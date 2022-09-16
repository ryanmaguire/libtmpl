
/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if !defined(TMPL_USE_INLINE) || TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

#define A0  1.00000000000000000000
#define A1 -3.33333333333329318027E-01
#define A2  1.99999999998764832476E-01
#define A3 -1.42857142725034663711E-01
#define A4  1.11111104054623557880E-01
#define A5 -9.09088713343650656196E-02
#define A6  7.69187620504482999495E-02
#define A7 -6.66107313738753120669E-02
#define A8  5.83357013379057348645E-02

/*  Maclaurin series for arctan, double precision, to 9 terms.                */
double tmpl_Double_Arctan_Maclaurin(double x)
{
    /*  Declare necessary variables.                                          */
    const double x_sq = x*x;

    /*  Use Horner's method to compute the polynomial. The signs of the       *
     *  coefficients oscillate.                                               */
    return x * (
        A0 + x_sq * (
            A1 + x_sq * (
                A2 + x_sq * (
                    A3 + x_sq * (
                        A4 + x_sq * (
                            A5 + x_sq * (
                                A6 + x_sq * (
                                    A7 + x_sq * A8
                                )
                            )
                        )
                    )
                )
            )
        )
    );
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

#endif
