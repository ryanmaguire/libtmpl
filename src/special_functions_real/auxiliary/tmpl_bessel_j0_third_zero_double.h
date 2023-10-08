#ifndef TMPL_BESSEL_J0_THIRD_ZERO_DOUBLE_H
#define TMPL_BESSEL_J0_THIRD_ZERO_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P00 (-2.7145229992838188579805231045318659724623561368945E-01)
#define P01 (+9.0295777330183156467906264705727323810473308610778E-03)
#define P02 (+3.9879890996834601364372139834099219661467346172727E-02)
#define P03 (-1.2649839325465284362172228998748914969786616816565E-03)
#define P04 (-1.4140415965678673747854762860873022755664280125901E-03)
#define P05 (+3.7230885373242152065988480248416001973638822151305E-05)
#define P06 (+1.7659873587786774404848774685268940631841956456711E-05)
#define P07 (-2.7467310012465593777366325381949768006570543663630E-07)
#define P08 (-7.7766151668698018199503383476257501523633832365035E-08)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q01 (+2.4514609858495662336696568275879853010137090718320E-02)
#define Q02 (+1.6718864316723516611632716028420436238647408375557E-02)
#define Q03 (+3.5871229064486234864202905350334560597125069687305E-04)
#define Q04 (+1.2529889673582768764359378772811847706662386040095E-04)
#define Q05 (+1.8553771442508703819905864266025824627654833615641E-06)
#define Q06 (+4.3971138333374378822552180655801881190326659505923E-07)

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

#define J0_ZERO_HI (+8.653727912911012509766806033440E+00)
#define J0_ZERO_LO (-2.928126073207789799338157043633E-16)

TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J0_Third_Zero(double x)
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
