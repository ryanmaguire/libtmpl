#include <libtmpl/include/tmpl_math.h>

#include "auxiliary/tmpl_cosd_maclaurin_double.h"
#include "auxiliary/tmpl_sind_maclaurin_double.h"

void tmpl_Double_SinCosd(double t, double *sind_t, double *cosd_t)
{
    double arg, abs_t, sgn_sin, sgn_cos, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    if (t >= 0.0)
    {
        abs_t = t;
        sgn_sin = 1.0;
    }
    else
    {
        abs_t = -t;
        sgn_sin = -1.0;
    }

    arg = tmpl_Double_Mod_360(abs_t);

    if (arg >= 180.0)
    {
        sgn_sin *= -1.0;
        sgn_cos = -1.0;
        arg -= 180.0;
    }
    else
        sgn_cos = 1.0;

    ind = (unsigned int)arg;
    dx = arg - (double)ind;

    sx = tmpl_double_sind_table[ind];
    cx = tmpl_double_cosd_table[ind];
    sdx = tmpl_Double_Sind_Maclaurin(dx);
    cdx = tmpl_Double_Cosd_Maclaurin(dx);
    *sind_t = sgn_sin * (cdx*sx + cx*sdx);
    *cosd_t = sgn_cos * (cdx*cx - sx*sdx);
}
