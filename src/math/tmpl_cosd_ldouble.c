#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_Cosd(long double x)
{
    long double arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_LDouble_Mod_360(tmpl_LDouble_Abs(x));

    if (arg >= 180.0L)
    {
        sgn_x = -1.0L;
        arg = arg - 180.0L;
    }
    else
        sgn_x = 1.0L;

    ind = (unsigned int)arg;
    dx = arg - (long double)ind;

    sx = tmpl_ldouble_sind_table[ind];
    cx = tmpl_ldouble_cosd_table[ind];
    sdx = tmpl_LDouble_Sind_Maclaurin(dx);
    cdx = tmpl_LDouble_Cosd_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
