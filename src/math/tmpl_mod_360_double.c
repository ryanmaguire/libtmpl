#include <libtmpl/include/tmpl_math.h>

double tmpl_Double_Mod_360(double x)
{
    if (x < 0.0)
        return x + 360.0*tmpl_Double_Floor(-x/360.0);
    else
        return x - 360.0*tmpl_Double_Floor(x/360.0);
}
