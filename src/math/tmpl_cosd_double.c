#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/math/tmpl_math_cosd_lookup_table_double.h>
#include <libtmpl/include/math/tmpl_math_sind_lookup_table_double.h>

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

    sx = tmpl_Double_Sind_Lookup_Table[ind];
    cx = tmpl_Double_Cosd_Lookup_Table[ind];
    sdx = tmpl_Double_Sind_Maclaurin(dx);
    cdx = tmpl_Double_Cosd_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
