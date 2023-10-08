#ifndef TMPL_BESSEL_J0_FOURTH_ZERO_DOUBLE_H
#define TMPL_BESSEL_J0_FOURTH_ZERO_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P00 (+2.3245983136472477001714233584081576402575476783273E-01)
#define P01 (-4.4201220392351772577544733075447849584197945682303E-03)
#define P02 (-3.4538151675190866074184366313279103813899341996170E-02)
#define P03 (+6.2879775275667515355840027734417958480534978887723E-04)
#define P04 (+1.2681152706183877413651009445386024132977819026634E-03)
#define P05 (-1.9709153890925081262028164419283319889558067901512E-05)
#define P06 (-1.6755659397777493591810478395157376440048938471011E-05)
#define P07 (+1.6822666676773226366481946235608871830732377994477E-07)
#define P08 (+7.6981464228679566483738145941024654164581428081917E-08)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q01 (+2.3388739648787003060499355755705359300008667287360E-02)
#define Q02 (+1.6684180356139800469378293960941928161533632191947E-02)
#define Q03 (+3.3975817531305432080553128192708351684747773268154E-04)
#define Q04 (+1.2444393579798829574132133282251014774838112111041E-04)
#define Q05 (+1.7375612278944418461887489470792971841250231837672E-06)
#define Q06 (+4.3192435590823188587924175389812883643107638728845E-07)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_NUM_EVAL(z) \
P00 + z*(\
    P01 + z*(\
        P02 + z*(\
            P03 + z*(\
                P04 + z*(\
                    P05 + z*(\
                        P06 + z*(\
                            P07 + z*P08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_DEN_EVAL(z) \
Q00 + z*(\
    Q01 + z*(\
        Q02 + z*(\
            Q03 + z*(\
                Q04 + z*(\
                    Q05 + z*Q06\
                )\
            )\
        )\
    )\
)
#define J0_ZERO_HI (+1.179153443901428133244735363405E+01)
#define J0_ZERO_LO (+2.812956912778735049200856560176E-16)

TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J0_Fourth_Zero(double x)
{
    const double z = (x - J0_ZERO_HI) - J0_ZERO_LO;
    const double p = TMPL_NUM_EVAL(z);
    const double q = TMPL_DEN_EVAL(z);
    return z * p / q;
}

#undef P00
#undef P01
#undef P02
#undef P03
#undef P04
#undef P05
#undef P06
#undef P07
#undef P08
#undef P09
#undef P10
#undef P11

#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04
#undef Q05
#undef Q06
#undef Q07
#undef Q08

#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#undef J0_ZERO_HI
#undef J0_ZERO_LO

#endif
