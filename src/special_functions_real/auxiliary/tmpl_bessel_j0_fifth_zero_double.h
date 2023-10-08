#ifndef TMPL_BESSEL_J0_FIFTH_ZERO_DOUBLE_H
#define TMPL_BESSEL_J0_FIFTH_ZERO_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P00 (-2.0654643307799602280518339450791913906267286826364E-01)
#define P01 (+2.6295785287472840480100947422750039197084587841893E-03)
#define P02 (+3.0786036910354364118796503020044043283743623045673E-02)
#define P03 (-3.7488927043775871424672393170836297730222033969323E-04)
#define P04 (-1.1420553548449182801004624004204548509168649668272E-03)
#define P05 (+1.1903500901291362388342066156941813164237908678663E-05)
#define P06 (+1.5370900868019172066892620502666026543999649076484E-05)
#define P07 (-1.0459903225538959253733405088629231902288709433751E-07)
#define P08 (-7.2300735319996657745233225176879799487335485713896E-08)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q01 (+2.0756386065996311538509050566316865516141378874499E-02)
#define Q02 (+1.6815115994403020754928499408029430676306723702816E-02)
#define Q03 (+3.0034279964087039294424996575064986839899983241659E-04)
#define Q04 (+1.2674432535675719137601166239935753121057464983557E-04)
#define Q05 (+1.5304647379482345066951284688343724665531091701811E-06)
#define Q06 (+4.4703564614221762111210897067816749328956342470889E-07)

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
#define J0_ZERO_HI (1.493091770848778665481404459570E+01)
#define J0_ZERO_LO (-7.070514505983073692408400987041E-16)

TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J0_Fifth_Zero(double x)
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
