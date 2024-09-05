#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>
#include <libtmpl/include/tmpl_optics.h>

float tmpl_Float_Resolution_Inverse(float x)
{
    float P1, P2;

    if (x <= 1.0F)
        return TMPL_NANF;

    if (tmpl_Float_Is_Inf(x))
        return 0.0F;

    P1 = x / (1.0F - x);
    P2 = P1 * tmpl_Float_Exp(P1);
    return tmpl_Float_LambertW(P2) - P1;
}
