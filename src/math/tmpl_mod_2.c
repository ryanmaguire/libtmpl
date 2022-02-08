
#include <libtmpl/include/tmpl_math.h>

double tmpl_Double_Mod_2(double x)
{
    if (x < 0.0)
        return x + 2.0 * tmpl_Double_Floor(-0.5 * x);
    else
        return x - 2.0 * tmpl_Double_Floor(0.5 * x);
}

