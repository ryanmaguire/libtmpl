#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_Sind(long double x)
{
    long double abs_x, arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    if (x >= 0.0L)
    {
        abs_x = x;
        sgn_x = 1.0L;
    }
    else
    {
        abs_x = -x;
        sgn_x = -1.0L;
    }

    arg = tmpl_LDouble_Mod_360(abs_x);

    if (arg >= 180.0L)
    {
        sgn_x *= -1.0L;
        arg -= 180.0L;
    }

    ind = (unsigned int)arg;
    dx = arg - (long double)ind;

    sx = tmpl_ldouble_sind_table[ind];
    cx = tmpl_ldouble_cosd_table[ind];
    sdx = tmpl_LDouble_Sind_Maclaurin(dx);
    cdx = tmpl_LDouble_Cosd_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}
