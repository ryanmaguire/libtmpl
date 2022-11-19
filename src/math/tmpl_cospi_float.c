#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_CosPi(float x)
{
    float arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_Float_Mod_2(tmpl_Float_Abs(x));

    if (arg >= 1.0F)
    {
        sgn_x = -1.0F;
        arg = arg - 1.0F;
    }
    else
        sgn_x = 1.0F;

    ind = (unsigned int)(128.0F*arg);
    dx = arg - 0.0078125F*(float)ind;

    sx = tmpl_float_sinpi_table[ind];
    cx = tmpl_float_cospi_table[ind];
    sdx = tmpl_Float_SinPi_Maclaurin(dx);
    cdx = tmpl_Float_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
