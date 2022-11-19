#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Sind(float x)
{
    float abs_x, arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    if (x >= 0.0F)
    {
        abs_x = x;
        sgn_x = 1.0F;
    }
    else
    {
        abs_x = -x;
        sgn_x = -1.0F;
    }

    arg = tmpl_Float_Mod_360(abs_x);

    if (arg >= 180.0F)
    {
        sgn_x *= -1.0F;
        arg -= 180.0F;
    }

    ind = (unsigned int)arg;
    dx = arg - (float)ind;

    sx = tmpl_float_sind_table[ind];
    cx = tmpl_float_cosd_table[ind];
    sdx = tmpl_Float_Sind_Maclaurin(dx);
    cdx = tmpl_Float_Cosd_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}
