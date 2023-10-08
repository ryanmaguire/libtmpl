/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_BESSEL_I0_LARGE_DOUBLE_H
#define TMPL_BESSEL_I0_LARGE_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A0 (+3.9913750620753016447986792679950258277993122636539E-01)
#define A1 (+1.9565733954026310985571062376709974122160813385314E-04)
#define A2 (+4.3330680966770010824893479910518743410285139271427E-07)
#define A3 (+1.7841217626337899251799487397538441388473045559869E-09)
#define A4 (+1.0842381199816909396678781356640565000827132658342E-11)
#define A5 (+8.8427352757751210798177080781599027317709074867024E-14)

#define TMPL_POLY_EVAL(z) A0 + z*(A1 + z*(A2 + z*(A3 + z*(A4 + z*A5))))

TMPL_STATIC_INLINE
double tmpl_Double_Bessel_I0_Large(double x)
{
    const double rcpr_x = 1.0 / x;
    const double z = -1.0 + 256.0 * rcpr_x;
    const double exp_x = tmpl_Double_Exp_Pos_Kernel(x);
    const double sqrt_rcpr_x = tmpl_Double_Sqrt(rcpr_x);
    const double poly = TMPL_POLY_EVAL(z);
    return poly * exp_x * sqrt_rcpr_x;
}

#endif
/*  End of include guard.                                                     */
