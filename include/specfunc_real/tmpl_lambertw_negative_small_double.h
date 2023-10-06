/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_LAMBERTW_NEGATIVE_SMALL_DOUBLE_H
#define TMPL_LAMBERTW_NEGATIVE_SMALL_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P0 (+1.0000000000662350603898305462478231956838511898053E+00)
#define P1 (+5.1019366434668652103034210074627800738106058815467E+00)
#define P2 (+8.0750327566743616940932644278135229255181808164004E+00)
#define P3 (+3.9749059501965756025154175712723075283824884539486E+00)
#define P4 (+2.1117892218746285629343375077265530565720621271029E-01)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q0 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q1 (+6.1019366372850970927095698287990232219341965187168E+00)
#define Q2 (+1.2676969144647954742119940781046503238030818617939E+01)
#define Q3 (+1.0165631154685075216031830495930686487865753570936E+01)
#define Q4 (+2.4247759917084921805584956079102670353407154025012E+00)

#define TMPL_NUM_EVAL(z) P0 + z*(P1 + z*(P2 + z*(P3 + z*P4)))
#define TMPL_DEN_EVAL(z) Q0 + z*(Q1 + z*(Q2 + z*(Q3 + z*Q4)))

TMPL_STATIC_INLINE
double tmpl_Double_LambertW_Negative_Small(double x)
{
    const double num = TMPL_NUM_EVAL(x);
    const double den = TMPL_DEN_EVAL(x);
    return x * num / den;
}

#undef P0
#undef P1
#undef P2
#undef P3
#undef P4
#undef Q0
#undef Q1
#undef Q2
#undef Q3
#undef Q4
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
/*  End of include guard.                                                     */
