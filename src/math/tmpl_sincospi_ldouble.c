#include <libtmpl/include/tmpl_math.h>

void
tmpl_LDouble_SinCosPi(long double t, long double *sinpi_t, long double *cospi_t)
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

    arg = tmpl_LDouble_Mod_2(abs_t);

    if (arg >= 1.0L)
    {
        sgn_sin *= -1.0L;
        sgn_cos = -1.0L;
        arg -= 1.0L;
    }
    else
        sgn_cos = 1.0L;

    ind = (unsigned int)(128.0L*arg);
    dx = arg - 0.0078125L*(long double)ind;

    sx = tmpl_ldouble_sinpi_table[ind];
    cx = tmpl_ldouble_cospi_table[ind];
    sdx = tmpl_LDouble_SinPi_Maclaurin(dx);
    cdx = tmpl_LDouble_CosPi_Maclaurin(dx);
    *sinpi_t = sgn_sin * (cdx*sx + cx*sdx);
    *cospi_t = sgn_cos * (cdx*cx - sx*sdx);
}
