
#include <libtmpl/include/tmpl_math.h>
#include <math.h>

double tmpl_Double_Mod_2(double x)

{
    double abs_x, sgn_x, factor;

    if (x < 0.0)
    {
        sgn_x = -1.0;
        abs_x = -x;
    }
    else
    {
        sgn_x = 1.0;
        abs_x = x;
    }

    factor = floor(abs_x * 0.5);
    abs_x -= factor * 2.0;

    return sgn_x * abs_x;
}

