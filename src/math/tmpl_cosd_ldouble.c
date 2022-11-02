#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/math/tmpl_math_cosd_lookup_table_ldouble.h>
#include <libtmpl/include/math/tmpl_math_sind_lookup_table_ldouble.h>

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

    sx = tmpl_LDouble_Sind_Lookup_Table[ind];
    cx = tmpl_LDouble_Cosd_Lookup_Table[ind];
    sdx = tmpl_LDouble_Sind_Maclaurin(dx);
    cdx = tmpl_LDouble_Cosd_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
