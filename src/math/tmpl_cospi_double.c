#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/math/tmpl_math_cospi_lookup_table_double.h>
#include <libtmpl/include/math/tmpl_math_sinpi_lookup_table_double.h>

double tmpl_Double_CosPi(double x)
{
    double arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_Double_Mod_2(tmpl_Double_Abs(x));

    if (arg >= 1.0)
    {
        sgn_x = -1.0;
        arg = arg - 1.0;
    }
    else
        sgn_x = 1.0;

    ind = (unsigned int)(128.0*arg);
    dx = arg - 0.0078125*ind;

    sx = tmpl_Double_SinPi_Lookup_Table[ind];
    cx = tmpl_Double_CosPi_Lookup_Table[ind];
    sdx = tmpl_Double_SinPi_Maclaurin(dx);
    cdx = tmpl_Double_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
