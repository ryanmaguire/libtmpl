/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_LAMBERTW_NEGATIVE_LARGE_DOUBLE_H
#define TMPL_LAMBERTW_NEGATIVE_LARGE_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P0 (+7.5694510645758331990805541314357347260117638840764E-01)
#define P1 (+1.3674222053161808379786409536499564625489376956302E+00)
#define P2 (+6.0793538644975779887061715268037014009080750597585E-01)
#define P3 (+3.2033797726283713720029413366277862167564221333350E-02)
#define P4 (-1.8416871530068850478960572750788775316654102387411E-03)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q0 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q1 (+2.3985747517015594017723946440613592467809602192711E+00)
#define Q2 (+1.7356264337857780752790558770823403741444764813227E+00)
#define Q3 (+3.6072075131787542243546633890869981229091610718606E-01)

#define TMPL_NUM_EVAL(z) P0 + z*(P1 + z*(P2 + z*(P3 + z*P4)))
#define TMPL_DEN_EVAL(z) Q0 + z*(Q1 + z*(Q2 + z*Q3))

TMPL_STATIC_INLINE
double tmpl_Double_LambertW_Negative_Large(double x)
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
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
/*  End of include guard.                                                     */
