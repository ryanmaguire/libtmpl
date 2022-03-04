/*  The C Standard Library header for math functions and more found here.     */
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions.h>
#include <libtmpl/include/tmpl_optics.h>

float tmpl_Float_Resolution_Inverse(float x)
{
    float P1, P2, out;

    if (x <= 1.0F)
        out = TMPL_NANF;
    else if (x < TMPL_INFINITYF)
    {
        P1 = x/(1.0F-x);
        P2 = P1*tmpl_Float_Exp(P1);
        out = tmpl_Float_LambertW(P2)-P1;
    }
    else
        out = 0.0F;

    return out;
}

double tmpl_Double_Resolution_Inverse(double x)
{
    double P1, P2, out;

    if (x <= 1.0)
        out = TMPL_NAN;
    else if (x < TMPL_INFINITY)
    {
        P1 = x/(1.0-x);
        P2 = P1*tmpl_Double_Exp(P1);
        out = tmpl_Double_LambertW(P2)-P1;
    }
    else
        out = 0.0;

    return out;
}

long double tmpl_LDouble_Resolution_Inverse(long double x)
{
    long double P1, P2, out;

    if (x <= 1.0L)
        out = TMPL_NANL;
    else if (x < TMPL_INFINITYL)
    {
        P1 = x/(1.0L - x);
        P2 = P1*tmpl_LDouble_Exp(P1);
        out = tmpl_LDouble_LambertW(P2)-P1;
    }
    else
        out = 0.0L;

    return out;
}
