#include <libtmpl/include/tmpl_math.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

#include "auxiliary/tmpl_cospi_maclaurin_ldouble.h"
#include "auxiliary/tmpl_sinpi_maclaurin_ldouble.h"

TMPL_CONST_FUNC
long double tmpl_LDouble_SinPi(const long double x) TMPL_UNSEQUENCED
{
    long double arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx;
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

    arg = tmpl_LDouble_Mod_2(abs_x);

    if (arg >= 1.0L)
    {
        sgn_x *= -1.0L;
        arg -= 1.0L;
    }

    ind = (unsigned int)(128.0L*arg);
    dx = arg - 0.0078125L*ind;

    sx = tmpl_ldouble_sinpi_table[ind];
    cx = tmpl_ldouble_cospi_table[ind];
    sdx = tmpl_LDouble_SinPi_Maclaurin(dx);
    cdx = tmpl_LDouble_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}
