#include <libtmpl/include/tmpl_math.h>

void tmpl_Float_SinCosd(float t, float *sind_t, float *cosd_t)
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

    arg = tmpl_Float_Mod_360(abs_t);

    if (arg >= 180.0F)
    {
        sgn_sin *= -1.0F;
        sgn_cos = -1.0F;
        arg -= 180.0F;
    }
    else
        sgn_cos = 1.0F;

    ind = (unsigned int)arg;
    dx = arg - (float)ind;

    sx = tmpl_float_sind_table[ind];
    cx = tmpl_float_cosd_table[ind];
    sdx = tmpl_Float_Sind_Maclaurin(dx);
    cdx = tmpl_Float_Cosd_Maclaurin(dx);
    *sind_t = sgn_sin * (cdx*sx + cx*sdx);
    *cosd_t = sgn_cos * (cdx*cx - sx*sdx);
}
