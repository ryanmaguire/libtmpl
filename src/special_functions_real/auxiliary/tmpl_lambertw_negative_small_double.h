#ifndef TMPL_LAMBERTW_NEGATIVE_SMALL_DOUBLE_H
#define TMPL_LAMBERTW_NEGATIVE_SMALL_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P00 (+1.0000000000000004008012690819779505170535551769495E+00)
#define P01 (+6.4203407783527281964778775107789000403007730527082E+00)
#define P02 (+1.4351263023352941475532969317065780760590218294394E+01)
#define P03 (+1.2943189133128132568987111035079417945193620120667E+01)
#define P04 (+3.9218992876284397853773368874087251806815762240084E+00)
#define P05 (+1.2089607208273063957912750681690740348387143281999E-01)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q01 (+7.4203407783525988934188455163145408173169499755744E+00)
#define Q02 (+2.0271603801689061496419999034375541902064674287750E+01)
#define Q03 (+2.4750948432851487055569309556590820684573575860138E+01)
#define Q04 (+1.2844684050035604480465784346258559039164522498269E+01)
#define Q05 (+2.0491583242474398200714652895487616977144210317658E+00)

#define TMPL_NUM_EVAL(z) P00 + z*(P01 + z*(P02 + z*(P03 + z*(P04 + z*P05))))
#define TMPL_DEN_EVAL(z) Q00 + z*(Q01 + z*(Q02 + z*(Q03 + z*(Q04 + z*Q05))))

TMPL_STATIC_INLINE
double tmpl_Double_LambertW_Negative_Small(double x)
{
    const double p = TMPL_NUM_EVAL(x);
    const double q = TMPL_DEN_EVAL(x);
    return x * p / q;
}

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
#undef Q05
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
