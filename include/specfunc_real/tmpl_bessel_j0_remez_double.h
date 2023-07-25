#ifndef TMPL_BESSEL_J0_REMEZ_DOUBLE_H
#define TMPL_BESSEL_J0_REMEZ_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P0 (+9.9999999999999995771700020588715163846673623878599E-01)
#define P1 (-2.2935307523767776887012198499178077227653270733280E-01)
#define P2 (+1.0674964065060814443871836218217881229275361308894E-02)
#define P3 (-1.6300989997909695125042495621287098320764273259568E-04)
#define P4 (+7.9934363468300740064140287740515715132945470135958E-07)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q0 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q1 (+2.0646924762320490967572036726696038846857803068408E-02)
#define Q2 (+2.1169525565270902107858419063511091891931326708412E-04)
#define Q3 (+1.3334922699526880124663201568969554584360683577588E-06)
#define Q4 (+4.6332173542255143439321629275868247916900831976308E-09)

TMPL_INLINE_DECL
double tmpl_Double_Bessel_J0_Remez(double x)
{
    const double x2 = x*x;
    const double p = P0 + x2*(P1 + x2*(P2 + x2*(P3 + x2*P4)));
    const double q = Q0 + x2*(Q1 + x2*(Q2 + x2*(Q3 + x2*Q4)));
    return p / q;
}
/*  End of tmpl_Double_Bessel_J0_Remez.                                       */

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
