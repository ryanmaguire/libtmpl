#ifndef TMPL_BESSEL_J0_REMEZ_DOUBLE_H
#define TMPL_BESSEL_J0_REMEZ_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P0 (+9.9999999999999995775919789671915077698944113514107E-01)
#define P1 (-2.2935309375922022018662486712921068976672405783428E-01)
#define P2 (+1.0674968196232732303638796286486512313779943352689E-02)
#define P3 (-1.6301007114708953350928987406335611650549845612515E-04)
#define P4 (+7.9934546986926403078239679054334517655841532070045E-07)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q0 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q1 (+2.0646906240778041198422464565870547539716764559801E-02)
#define Q2 (+2.1169475643900525676807534066979625027602732260085E-04)
#define Q3 (+1.3334856976554961919708889450743721311386808495172E-06)
#define Q4 (+4.6331707939410291336985505369761924163674372414265E-09)

TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J0_Rat_Remez(double x)
{
    const double x2 = x*x;
    const double p = P0 + x2*(P1 + x2*(P2 + x2*(P3 + x2*P4)));
    const double q = Q0 + x2*(Q1 + x2*(Q2 + x2*(Q3 + x2*Q4)));
    return p / q;
}
/*  End of tmpl_Double_Bessel_J0_Rat_Remez.                                   */

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

#endif
