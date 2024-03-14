#ifndef TMPL_ERF_RAT_REMEZ_SMALL_DOUBLE_H
#define TMPL_ERF_RAT_REMEZ_SMALL_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P00 (+1.1283791670955124938475573609352049610120121044597E+00)
#define P01 (+8.8118554414781385974364141231775809003906275782836E-02)
#define P02 (+3.8174525622960428358232893166516989580842787239161E-02)
#define P03 (-1.6512134579920191241485886315165826201216377171439E-04)
#define P04 (+1.1890825688032048780331583748841205158854213615978E-04)
#define P05 (-3.0921059933069107266669293512244784260617430522963E-06)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q01 (+4.1142636888767124544652890922173692596611590341916E-01)
#define Q02 (+7.0973415436556028065448870524028079599831414989336E-02)
#define Q03 (+6.1783570761603794456940715597216373780221488456877E-03)
#define Q04 (+2.3372686280898360241350381808463274932397135122824E-04)

#define TMPL_NUM_EVAL(z) P00 + z*(P01 + z*(P02 + z*(P03 + z*(P04 + z*P05))))
#define TMPL_DEN_EVAL(z) Q00 + z*(Q01 + z*(Q02 + z*(Q03 + z*Q04)))

TMPL_STATIC_INLINE
double tmpl_Double_Erf_Rat_Remez_Small(double x)
{
    const double x2 = x*x;
    const double p = TMPL_NUM_EVAL(x2);
    const double q = TMPL_DEN_EVAL(x2);
    return x * p / q;
}

#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL
#undef P00
#undef P01
#undef P02
#undef P03
#undef P04
#undef P05
#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04

#endif