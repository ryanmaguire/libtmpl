#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_SinPi(float x)
{
    float arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx;
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

    arg = tmpl_Float_Mod_2(abs_x);

    if (arg >= 1.0F)
    {
        sgn_x *= -1.0F;
        arg -= 1.0F;
    }

    ind = (unsigned int)(128.0F*arg);
    dx = arg - 0.0078125F*(float)ind;

    sx = tmpl_float_sinpi_table[ind];
    cx = tmpl_float_cospi_table[ind];
    sdx = tmpl_Float_SinPi_Maclaurin(dx);
    cdx = tmpl_Float_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}
