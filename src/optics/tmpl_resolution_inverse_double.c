#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>
#include <libtmpl/include/tmpl_optics.h>

double tmpl_Double_Resolution_Inverse(double x)
{
    double P1, P2;

    if (x <= 1.0)
        return TMPL_NAN;

    if (tmpl_Double_Is_Inf(x))
        return 0.0;

    P1 = x / (1.0 - x);
    P2 = P1 * tmpl_Double_Exp(P1);
    return tmpl_Double_LambertW(P2) - P1;
}
