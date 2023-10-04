#ifndef TMPL_BESSEL_J0_FIRST_ZERO_DOUBLE_H
#define TMPL_BESSEL_J0_FIRST_ZERO_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P00 (-4.1583050354952012736624326964104686758531002439580E-01)
#define P01 (-1.2479115555192257943093512608932966652121869353682E-01)
#define P02 (+4.1908312440133932066831688403376090134251562897793E-02)
#define P03 (+6.2418120242361340274010996035583744196381111120867E-03)
#define P04 (-1.4513987346655457444813598283287701526097610098563E-03)
#define P05 (-6.0367571839147797738791987008008763447793564921662E-05)
#define P06 (+1.9869168624633035500246363814673010478436363297147E-05)
#define P07 (-8.1528778565544052726043204584359591372366262399468E-07)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q01 (-1.1573050369414486892586460726273976564789779381689E-01)
#define Q02 (+2.4429078205230795179088400167584898122594785970256E-02)
#define Q03 (-2.0385199842284070550068539989458753350269258274025E-03)
#define Q04 (+2.1842142195107667548306559482493214204121281999992E-04)
#define Q05 (-1.0647929010188373840571784778225431532787477709397E-05)
#define Q06 (+5.6852401729143066585018281335645898777565284311390E-07)

#define TMPL_NUM_EVAL(z) \
P00 + z*(P01 + z*(P02 + z*(P03 + z*(P04 + z*(P05 + z*(P06 + z*P07))))))

#define TMPL_DEN_EVAL(z) \
Q00 + z*(Q01 + z*(Q02 + z*(Q03 + z*(Q04 + z*(Q05 + z*Q06)))))

#define J0_ZERO_HI (+2.4048255576957728862907970324158668518066E+00)
#define J0_ZERO_LO (-1.1766916515308940362785587811429253257372E-16)

TMPL_INLINE_DECL
double tmpl_Double_Bessel_J0_First_Zero(double x)
{
    const double z = (x - J0_ZERO_HI) - J0_ZERO_LO;
    const double p = TMPL_NUM_EVAL(x);
    const double q = TMPL_DEN_EVAL(x);
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
