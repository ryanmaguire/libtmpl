#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

#define A00 (+1.000000000000000000000000000000E+00)
#define A01 (+1.250000000000000000000000000000E-01)
#define A02 (+7.031250000000000000000000000000E-02)
#define A03 (+7.324218750000000000000000000000E-02)
#define A04 (+1.121520996093750000000000000000E-01)
#define A05 (+2.271080017089843750000000000000E-01)
#define A06 (+5.725014209747314453125000000000E-01)
#define A07 (+1.727727502584457397460937500000E+00)

#define TMPL_ASYMPTOTIC_EXPANSION(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*A07\
                    )\
                )\
            )\
        )\
    )\
)

double tmpl_Double_Bessel_I0_Large_Asymptotic(double x)
{
    const double rcpr_x = 1.0 / x;
    const double exp_x = tmpl_Double_Exp_Pos_Kernel(x);
    const double inv_sqrt_two_pi_x = 1.0 / tmpl_Double_Sqrt(tmpl_Two_Pi * x);
    const double arg = TMPL_ASYMPTOTIC_EXPANSION(rcpr_x);
    return exp_x * arg * inv_sqrt_two_pi_x;
}
