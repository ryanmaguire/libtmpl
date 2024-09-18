#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>
#include <libtmpl/include/tmpl_optics.h>

long double tmpl_LDouble_Resolution_Inverse(long double x)
{
    long double P1, P2;

    if (x <= 1.0L)
        return TMPL_NANL;

    if (tmpl_LDouble_Is_Inf(x))
        return 0.0L;

    P1 = x / (1.0L - x);
    P2 = P1 * tmpl_LDouble_Exp(P1);
    return tmpl_LDouble_LambertW(P2) - P1;
}
