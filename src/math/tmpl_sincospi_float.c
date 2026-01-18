#include <libtmpl/include/tmpl_math.h>

#include "auxiliary/tmpl_cospi_maclaurin_float.h"
#include "auxiliary/tmpl_sinpi_maclaurin_float.h"

void
tmpl_Float_SinCosPi(const float t,
                    float * TMPL_RESTRICT const sinpi_t,
                    float * TMPL_RESTRICT const cospi_t)
{
    float arg, abs_t, sgn_sin, sgn_cos, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    if (t >= 0.0F)
    {
        abs_t = t;
        sgn_sin = 1.0F;
    }
    else
    {
        abs_t = -t;
        sgn_sin = -1.0F;
    }

    arg = tmpl_Float_Mod_2(abs_t);

    if (arg >= 1.0F)
    {
        sgn_sin *= -1.0F;
        sgn_cos = -1.0F;
        arg -= 1.0F;
    }
    else
        sgn_cos = 1.0F;

    ind = (unsigned int)(128.0F*arg);
    dx = arg - 0.0078125F*(float)ind;

    sx = tmpl_float_sinpi_table[ind];
    cx = tmpl_float_cospi_table[ind];
    sdx = tmpl_Float_SinPi_Maclaurin(dx);
    cdx = tmpl_Float_CosPi_Maclaurin(dx);
    *sinpi_t = sgn_sin * (cdx*sx + cx*sdx);
    *cospi_t = sgn_cos * (cdx*cx - sx*sdx);
}
