#ifndef TMPL_BESSEL_I0_REMEZ_DOUBLE_H
#define TMPL_BESSEL_I0_REMEZ_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Theoretical maximum absolute error bounded by 10^-17. Actual relative     *
 *  error for 64-bit double bounded by 3.019E-16, slightly more than 1 ULP.   */

/*  Coefficients for the polynomial.                                          */
#define A00 (+9.9999999999999996867520649760101826440062421943658E-01)
#define A01 (+2.5000000000000024976290193997188203604012103074144E-01)
#define A02 (+1.5624999999999669402300720221360759121540486257367E-02)
#define A03 (+4.3402777777795073583392417498668851586560927671300E-04)
#define A04 (+6.7816840277302746678987697603174285978089329242382E-06)
#define A05 (+6.7816840285663268392689297084122033755766290331710E-08)
#define A06 (+4.7095027884814482152480180605115125918291289406478E-10)
#define A07 (+2.4028076140670071109951807233512403026230308839684E-12)
#define A08 (+9.3859635316046665439868965205559725584598382621164E-15)
#define A09 (+2.8969168594459311304907745023263489867297739164371E-17)
#define A10 (+7.2418742755818504518621052914388690000941949124483E-20)
#define A11 (+1.4971359198473901976008427891185449471629983881524E-22)
#define A12 (+2.5857434659005046300984352813293315997275254175125E-25)
#define A13 (+3.9697761753250577056758415269405240727299690576661E-28)
#define A14 (+4.0236295332756825708076954481222215669283072062882E-31)
#define A15 (+8.9488914654932245853032425704555198823178348924600E-34)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*(\
                                A08 + z*(\
                                    A09 + z*(\
                                        A10 + z*(\
                                            A11 + z*(\
                                                A12 + z*(\
                                                    A13 + z*(\
                                                        A14 + z*A15\
                                                    )\
                                                )\
                                            )\
                                        )\
                                    )\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

TMPL_INLINE_DECL
double tmpl_Double_Bessel_I0_Remez(double x)
{
    const double x2 = x*x;
    return TMPL_POLY_EVAL(x2);
}

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
#undef A12
#undef A13
#undef A14
#undef A15
#undef TMPL_POLY_EVAL

#endif
