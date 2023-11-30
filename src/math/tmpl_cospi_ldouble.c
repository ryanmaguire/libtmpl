#include <libtmpl/include/tmpl_math.h>

#include "auxiliary/tmpl_cospi_maclaurin_ldouble.h"
#include "auxiliary/tmpl_sinpi_maclaurin_ldouble.h"

long double tmpl_LDouble_CosPi(long double x)
{
    long double arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_LDouble_Mod_2(tmpl_LDouble_Abs(x));

    if (arg >= 1.0L)
    {
        sgn_x = -1.0L;
        arg = arg - 1.0L;
    }
    else
        sgn_x = 1.0L;

    ind = (unsigned int)(128.0L*arg);
    dx = arg - 0.0078125L*ind;

    sx = tmpl_ldouble_sinpi_table[ind];
    cx = tmpl_ldouble_cospi_table[ind];
    sdx = tmpl_LDouble_SinPi_Maclaurin(dx);
    cdx = tmpl_LDouble_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
