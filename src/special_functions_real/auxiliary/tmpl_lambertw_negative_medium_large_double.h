#ifndef TMPL_LAMBERTW_NEGATIVE_MEDIUM_LARGE_DOUBLE_H
#define TMPL_LAMBERTW_NEGATIVE_MEDIUM_LARGE_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

#define P00 (-3.49729841718749014E-01)
#define P01 (-6.28207407760709028E+01)
#define P02 (-2.57226178029669171E+03)
#define P03 (-2.50271008623093747E+04)
#define P04 (+1.11949239154711388E+05)
#define P05 (+1.85684566607844318E+06)
#define P06 (+4.80802490427638643E+06)
#define P07 (+2.76624752134636406E+06)

#define Q00 (+1.00000000000000000E+00)
#define Q01 (+1.82717661215113000E+02)
#define Q02 (+8.00121119810280100E+03)
#define Q03 (+1.06073266717010129E+05)
#define Q04 (+3.22848993926057721E+05)
#define Q05 (-8.05684814514171256E+05)
#define Q06 (-2.59223192927265737E+06)
#define Q07 (-5.61719645211570871E+05)
#define Q08 (+6.27765369292636844E+04)

#define TMPL_OFFSET (+3.49680423736572266E-01)

#define TMPL_NUM_EVAL(x) \
P00+x*(P01+x*(P02+x*(P03+x*(P04+x*(P05+x*(P06+x*P07))))))

#define TMPL_DEN_EVAL(x) \
Q00+x*(Q01+x*(Q02+x*(Q03+x*(Q04+x*(Q05+x*(Q06+x*(Q07+x*Q08)))))))

TMPL_STATIC_INLINE
double tmpl_Double_LambertW_Negative_Medium_Large(double z)
{
    const double p = TMPL_NUM_EVAL(z);
    const double q = TMPL_DEN_EVAL(z);
    return -z / (TMPL_OFFSET + p/q);
}

/*  Undefine everything in case someone wants to #include this file.          */
#undef P00
#undef P01
#undef P02
#undef P03
#undef P04
#undef P05
#undef P06
#undef P07
#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04
#undef Q05
#undef Q06
#undef Q07
#undef Q08
#undef TMPL_OFFSET
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
