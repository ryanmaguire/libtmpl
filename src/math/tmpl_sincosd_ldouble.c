#include <libtmpl/include/tmpl_math.h>

#include "auxiliary/tmpl_cosd_maclaurin_ldouble.h"
#include "auxiliary/tmpl_sind_maclaurin_ldouble.h"

void
tmpl_LDouble_SinCosd(long double t, long double *sind_t, long double *cosd_t)
{
    long double arg, abs_t, sgn_sin, sgn_cos, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    if (t >= 0.0L)
    {
        abs_t = t;
        sgn_sin = 1.0L;
    }
    else
    {
        abs_t = -t;
        sgn_sin = -1.0L;
    }

    arg = tmpl_LDouble_Mod_360(abs_t);

    if (arg >= 180.0L)
    {
        sgn_sin *= -1.0L;
        sgn_cos = -1.0L;
        arg -= 180.0L;
    }
    else
        sgn_cos = 1.0L;

    ind = (unsigned int)arg;
    dx = arg - (long double)ind;

    sx = tmpl_ldouble_sind_table[ind];
    cx = tmpl_ldouble_cosd_table[ind];
    sdx = tmpl_LDouble_Sind_Maclaurin(dx);
    cdx = tmpl_LDouble_Cosd_Maclaurin(dx);
    *sind_t = sgn_sin * (cdx*sx + cx*sdx);
    *cosd_t = sgn_cos * (cdx*cx - sx*sdx);
}
