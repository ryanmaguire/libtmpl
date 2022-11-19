#include <libtmpl/include/tmpl_math.h>

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

    sx = tmpl_double_sinpi_table[ind];
    cx = tmpl_double_cospi_table[ind];
    sdx = tmpl_Double_SinPi_Maclaurin(dx);
    cdx = tmpl_Double_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
