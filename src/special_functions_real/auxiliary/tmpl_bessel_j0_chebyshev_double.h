#ifndef TMPL_BESSEL_J0_CHEBYSHEV_ASYMPTOTIC_DOUBLE_H
#define TMPL_BESSEL_J0_CHEBYSHEV_ASYMPTOTIC_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Chebyshev approximation.                             */
#define P00 (+9.9993144187804131510580319948557116897074913879739E-01)
#define P01 (-1.3690443110805409270787347168146030738119870935930E-04)
#define P02 (-6.8030658623358484054517694525930363045487302575602E-05)
#define P03 (+4.1746081695655432712437917647019504627236028940773E-07)
#define P04 (+9.9326218492334728971515483240733790281711823176222E-08)
#define P05 (-2.9124467056588867001616255461501377268958869768294E-09)
#define P06 (-3.9685616455842865304555169013798630870497915508656E-10)
#define P07 (+3.4233676944272059827178120032279542098710573014070E-11)
#define P08 (+2.1870487543989042517262950387720959705864474784165E-12)
#define P09 (-5.2594309175739100486311409126559137952567476325568E-13)
#define P10 (+2.6072621356609433720858353356454817733374657559084E-15)

/*  Coefficients for the Chebyshev approximation.                             */
#define Q00 (-3.9040215445614254122763217611250709425188462194209E-03)
#define Q01 (-3.8995779732820268180518779557252279268712738194714E-03)
#define Q02 (+6.6388708910953804195615709266236849588926172212246E-06)
#define Q03 (+2.1691948290543971246620583372551839483148073438247E-06)
#define Q04 (-3.2164393417459916085796690119228353247172172342736E-08)
#define Q05 (-5.7932147206499853003936472773937291845037222981304E-09)
#define Q06 (+3.0009273578940991898992906656157821575914270776583E-10)
#define Q07 (+2.9668941499044044112763570727408133526954711946869E-11)
#define Q08 (-4.2278987847570968328926491643404177624306545591516E-12)
#define Q09 (-1.2948469356057148339905018463518849573741640867353E-13)
#define Q10 (+7.0671607396493980330271071524703976510117743489291E-14)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLYP_EVAL(z) \
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

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLYQ_EVAL(z) \
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

#define TMPL_SQRT_ONE_BY_PI (+5.6418958354775628694807945156077258584405062E-01)

extern double tmpl_Double_Sqrt(double x);
extern void tmpl_Double_SinCos(double x, double *sin_x, double *cos_x);

TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J0_Chebyshev(double x)
{
    double sin_x, cos_x;
    const double rcpr_x = 1.0 / x;
    const double arg = 32.0 * rcpr_x - 1.0;
    const double pzero = TMPL_POLYP_EVAL(arg);
    const double qzero = TMPL_POLYQ_EVAL(arg);
    const double scale = TMPL_SQRT_ONE_BY_PI * tmpl_Double_Sqrt(rcpr_x);

    tmpl_Double_SinCos(x, &sin_x, &cos_x);

    return scale * (pzero*(sin_x + cos_x) - qzero*(sin_x - cos_x));
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

#undef TMPL_SQRT_ONE_BY_PI
#undef TMPL_POLYP_EVAL
#undef TMPL_POLYQ_EVAL

#endif
