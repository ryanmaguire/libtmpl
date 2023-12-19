
#include <libtmpl/include/tmpl_math.h>

double tmpl_Double_Unit_Clamp(double x)
{
    if (x < 0.0)
        return 0.0;

    else if (x > 1.0)
        return 1.0;

    return x;
}
