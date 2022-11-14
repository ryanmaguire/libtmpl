#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Cosd(float x)
{
    float arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_Float_Mod_360(tmpl_Float_Abs(x));

    if (arg >= 180.0F)
    {
        sgn_x = -1.0F;
        arg = arg - 180.0F;
    }
    else
        sgn_x = 1.0F;

    ind = (unsigned int)arg;
    dx = arg - (float)ind;

    sx = tmpl_float_sind_table[ind];
    cx = tmpl_float_cosd_table[ind];
    sdx = tmpl_Float_Sind_Maclaurin(dx);
    cdx = tmpl_Float_Cosd_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
