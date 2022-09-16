/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_ARCTAN_ASYMPTOTIC_INLINE_H
#define TMPL_MATH_ARCTAN_ASYMPTOTIC_INLINE_H

/*  IEEE-754 data types and macros found here.                                */
#include <libtmpl/include/tmpl_math.h>

#define A0  1.00000000000000000000
#define A1 -3.33333333333329318027E-01
#define A2  1.99999999998764832476E-01
#define A3 -1.42857142725034663711E-01
#define A4  1.11111104054623557880E-01
#define A5 -9.09088713343650656196E-02

static inline double tmpl_Double_Arctan_Asymptotic(double x)
{
    /*  Declare necessary variables.                                          */
    const double arg = 1.0 / x;
    const double arg_sq = arg*arg;

    /*  Use Horner's method to compute the polynomial. The signs of the       *
     *  coefficients oscillate.                                               */
    return tmpl_Pi_By_Two -
        arg * (
            A0 + arg_sq * (
                A1 + arg_sq * (
                    A2 + arg_sq * (
                        A3 + arg_sq * (
                            A4 + arg_sq * A5
                        )
                    )
                )
            )
        );
}


#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#endif
