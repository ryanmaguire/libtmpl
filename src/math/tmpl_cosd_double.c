#include <libtmpl/include/tmpl_math.h>

double tmpl_Double_Cosd(double x)
{
    double arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_Double_Mod_360(tmpl_Double_Abs(x));

    if (arg >= 180.0)
    {
        sgn_x = -1.0;
        arg = arg - 180.0;
    }
    else
        sgn_x = 1.0;

    ind = (unsigned int)arg;
    dx = arg - (double)ind;

    sx = tmpl_double_sind_table[ind];
    cx = tmpl_double_cosd_table[ind];
    sdx = tmpl_Double_Sind_Maclaurin(dx);
    cdx = tmpl_Double_Cosd_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
