#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/math/tmpl_math_cospi_lookup_table_float.h>
#include <libtmpl/include/math/tmpl_math_sinpi_lookup_table_float.h>

float tmpl_Float_CosPi(float x)
{
    float arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int arg_128_int;

    arg = tmpl_Float_Mod_2(tmpl_Float_Abs(x));

    if (arg >= 1.0F)
    {
        sgn_x = -1.0F;
        arg = arg - 1.0F;
    }
    else
        sgn_x = 1.0F;

    arg_128_int = (unsigned int)(128.0F*arg);
    dx = arg - 0.0078125F*(float)arg_128_int;

    sx = tmpl_Float_SinPi_Lookup_Table[arg_128_int];
    cx = tmpl_Float_CosPi_Lookup_Table[arg_128_int];
    sdx = tmpl_Float_SinPi_Maclaurin(dx);
    cdx = tmpl_Float_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
