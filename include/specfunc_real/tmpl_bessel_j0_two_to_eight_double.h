#ifndef TMPL_BESSEL_J0_TWO_TO_EIGHT_DOUBLE_H
#define TMPL_BESSEL_J0_TWO_TO_EIGHT_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P00 (+9.9999992072107286680930054882393709358796763050348E-01)
#define P01 (-1.9368802834208445457503366946462755974436508352146E-01)
#define P02 (-2.1243959090113064306108711415527554538786148724431E-01)
#define P03 (+4.3652328278505775816609002230383910913520283687826E-02)
#define P04 (+6.7865790228733718788271993451001784708710592711195E-03)
#define P05 (-1.8828369082557934836597067005391522671639496694223E-03)
#define P06 (+1.7859250176417650315759606047834415122143717937032E-05)
#define P07 (+2.2162622286274641458206483557260976951584524769626E-05)
#define P08 (-1.9679048376481846927257076262122915157477897763374E-06)
#define P09 (+6.1799048993514110199544175474683011285848130466389E-08)
#define P10 (-5.7851478455173321129137002524165836549660915711954E-10)

#define TMPL_NUM_EVAL(z) \
P00 + z*(\
    P01 + z*(\
        P02 + z*(\
            P03 + z*(\
                P04 + z*(\
                    P05 + z*(\
                        P06 + z*(\
                            P07 + z*(\
                                P08 + z*(\
                                    P09 + z*P10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q01 (-1.9368843240555924320312407782982817803905133379325E-01)
#define Q02 (+3.7561372723855203430112457802081989506776196175626E-02)
#define Q03 (-4.7712083067023374860845053449116400203030656935969E-03)
#define Q04 (+5.5339665619043028761051728500090858252743158679959E-04)
#define Q05 (-5.0381723493060507332653171192953236887566488352438E-05)
#define Q06 (+3.9956182901718734572431289332358104758713508831970E-06)
#define Q07 (-2.4733793619514398918760932547238894911927874975824E-07)
#define Q08 (+1.2230430073834960163505653150601146231192878167190E-08)
#define Q09 (-4.0420882311045112422042714720795081198886110852910E-10)
#define Q10 (+8.0874447695100882899580492416968671049217633384782E-12)

#define TMPL_DEN_EVAL(z) \
Q00 + z*(\
    Q01 + z*(\
        Q02 + z*(\
            Q03 + z*(\
                Q04 + z*(\
                    Q05 + z*(\
                        Q06 + z*(\
                            Q07 + z*(\
                                Q08 + z*(\
                                    Q09 + z*Q10\
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
double tmpl_Double_Bessel_J0_Two_To_Eight(double x)
{
    const double p = TMPL_NUM_EVAL(x);
    const double q = TMPL_DEN_EVAL(x);
    return p / q;
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

#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04
#undef Q05
#undef Q06
#undef Q07
#undef Q08
#undef Q09
#undef Q10

#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
