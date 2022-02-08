
#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Mod_2(float x)
{
    if (x < 0.0F)
        return x + 2.0F * tmpl_Float_Floor(-0.5F * x);
    else
        return x - 2.0F * tmpl_Float_Floor(0.5F * x);
}

double tmpl_Double_Mod_2(double x)
{
    if (x < 0.0)
        return x + 2.0 * tmpl_Double_Floor(-0.5 * x);
    else
        return x - 2.0 * tmpl_Double_Floor(0.5 * x);
}

long double tmpl_LDouble_Mod_2(long double x)
{
    if (x < 0.0L)
        return x + 2.0L * tmpl_LDouble_Floor(-0.5L * x);
    else
        return x - 2.0L * tmpl_LDouble_Floor(0.5L * x);
}

