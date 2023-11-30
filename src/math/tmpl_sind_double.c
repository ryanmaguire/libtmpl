#include <libtmpl/include/tmpl_math.h>

#include "auxiliary/tmpl_cosd_maclaurin_double.h"
#include "auxiliary/tmpl_sind_maclaurin_double.h"

double tmpl_Double_Sind(double x)
{
    double abs_x, arg, sgn_x, cx, cdx, sx, sdx, dx;
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

    arg = tmpl_Double_Mod_360(abs_x);

    if (arg >= 180.0)
    {
        sgn_x *= -1.0;
        arg -= 180.0;
    }

    ind = (unsigned int)arg;
    dx = arg - (double)ind;

    sx = tmpl_double_sind_table[ind];
    cx = tmpl_double_cosd_table[ind];
    sdx = tmpl_Double_Sind_Maclaurin(dx);
    cdx = tmpl_Double_Cosd_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}
