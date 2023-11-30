#include <libtmpl/include/tmpl_math.h>

#include "auxiliary/tmpl_cospi_maclaurin_double.h"
#include "auxiliary/tmpl_sinpi_maclaurin_double.h"

void tmpl_Double_SinCosPi(double t, double *sinpi_t, double *cospi_t)
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

    arg = tmpl_Double_Mod_2(abs_t);

    if (arg >= 1.0)
    {
        sgn_sin *= -1.0;
        sgn_cos = -1.0;
        arg -= 1.0;
    }
    else
        sgn_cos = 1.0;

    ind = (unsigned int)(128.0*arg);
    dx = arg - 0.0078125*(double)ind;

    sx = tmpl_double_sinpi_table[ind];
    cx = tmpl_double_cospi_table[ind];
    sdx = tmpl_Double_SinPi_Maclaurin(dx);
    cdx = tmpl_Double_CosPi_Maclaurin(dx);
    *sinpi_t = sgn_sin * (cdx*sx + cx*sdx);
    *cospi_t = sgn_cos * (cdx*cx - sx*sdx);
}
