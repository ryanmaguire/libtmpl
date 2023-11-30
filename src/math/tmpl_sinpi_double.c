#include <libtmpl/include/tmpl_math.h>

#include "auxiliary/tmpl_cospi_maclaurin_double.h"
#include "auxiliary/tmpl_sinpi_maclaurin_double.h"

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

    sx = tmpl_double_sinpi_table[ind];
    cx = tmpl_double_cospi_table[ind];
    sdx = tmpl_Double_SinPi_Maclaurin(dx);
    cdx = tmpl_Double_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}
