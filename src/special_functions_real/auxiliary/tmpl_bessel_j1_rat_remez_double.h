#ifndef TMPL_BESSEL_J1_RAT_REMEZ_DOUBLE_H
#define TMPL_BESSEL_J1_RAT_REMEZ_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+4.9999999999999999856727399687314520552046931150535E-01)
#define A01 (-5.3538811239122051559104600948656000584733117309745E-02)
#define A02 (+1.5623441071507204586636801920298568367119120872735E-03)
#define A03 (-1.6960565215531797605992337275270784902579816705783E-05)
#define A04 (+6.3564233810372191473813777371630538786100064553088E-08)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+1.7922377521755779182937161967316732663398465470592E-02)
#define B02 (+1.5665207118837479652489955256872383868722833403747E-04)
#define B03 (+8.2160665071721084875736316248977393384247616695966E-07)
#define B04 (+2.2987140557048378598854942159799194151725770005750E-09)

#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J1_Rat_Remez(double x)
{
    const double x2 = x * x;
    const double num = TMPL_NUM_EVAL(x2);
    const double den = TMPL_DEN_EVAL(x2);
    return x * num / den;
}

#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
