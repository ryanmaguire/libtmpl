#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/math/tmpl_math_cospi_lookup_table_double.h>
#include <libtmpl/include/math/tmpl_math_sinpi_lookup_table_double.h>

double tmpl_Double_SinPi(double x)
{
    double arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    if (x >= 0.0)
    {
        abs_x = x;
        sgn_x = 1.0;
    }
    else
    {
        abs_x = -x;
        sgn_x = -1.0;
    }

    arg = tmpl_Double_Mod_2(abs_x);

    if (arg >= 1.0)
    {
        sgn_x *= -1.0;
        arg -= 1.0;
    }

    ind = (unsigned int)(128.0*arg);
    dx = arg - 0.0078125*ind;

    sx = tmpl_Double_SinPi_Lookup_Table[ind];
    cx = tmpl_Double_CosPi_Lookup_Table[ind];
    sdx = tmpl_Double_SinPi_Maclaurin(dx);
    cdx = tmpl_Double_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}
