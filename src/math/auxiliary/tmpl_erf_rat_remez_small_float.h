#ifndef TMPL_ERF_RAT_REMEZ_SMALL_FLOAT_H
#define TMPL_ERF_RAT_REMEZ_SMALL_FLOAT_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P00 (+1.1283790574684878861216799875679133907033770017189E+00F)
#define P01 (+1.1827399481209657409919217013238265667649516777735E-01F)
#define P02 (+1.6282372258179479937180108311345578064577917591169E-02F)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define Q01 (+4.3814526297098596654375260669316253166090338311380E-01F)
#define Q02 (+6.0530507610345444974553903042771357179713831714362E-02F)

#define TMPL_NUM_EVAL(z) P00 + z*(P01 + z*P02)
#define TMPL_DEN_EVAL(z) Q00 + z*(Q01 + z*Q02)

TMPL_STATIC_INLINE
float tmpl_Float_Erf_Rat_Remez_Small(float x)
{
    const float x2 = x*x;
    const float p = TMPL_NUM_EVAL(x2);
    const float q = TMPL_DEN_EVAL(x2);
    return x * p / q;
}

#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL
#undef P00
#undef P01
#undef P02
#undef Q00
#undef Q01
#undef Q02

#endif
