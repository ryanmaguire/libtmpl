#ifndef TMPL_BESSEL_I0_REMEZ_FLOAT_H
#define TMPL_BESSEL_I0_REMEZ_FLOAT_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.0000000101768264596644949176701798625154736063433E+00F)
#define A01 (+2.4999996188096179966896407666550451827968845884198E-01F)
#define A02 (+1.5625023594801814838785360044976365412877526660974E-02F)
#define A03 (+4.3402208606083211544619903230676725391854302633740E-04F)
#define A04 (+6.7823872024199776276007071260815198092066179642135E-06F)
#define A05 (+6.7766273755484727573969380382882195148248475225689E-08F)
#define A06 (+4.7320922530282525252074561247109800622196646623472E-10F)
#define A07 (+2.3383767653714605649063769775364293656364190812023E-12F)
#define A08 (+1.0554317724276635892174473826139187630804284900294E-14F)
#define A09 (+1.6087975333054007060145708747915892665674486587076E-17F)
#define A10 (+1.4841134515142611287427505334041273350593724053887E-19F)

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
                                    A09 + z*A10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

TMPL_STATIC_INLINE
float tmpl_Float_Bessel_I0_Remez(float x)
{
    const float x2 = x*x;
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
#undef TMPL_POLY_EVAL

#endif
