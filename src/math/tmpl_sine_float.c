#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Sin(float x)
{
    float arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx, dx_sq;
    unsigned int arg_100_int;

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

    arg = tmpl_Float_Mod_2(abs_x * 0.31830988618379067153776752674502872406F);

    if (arg >= 1.0F)
    {
        sgn_x *= -1.0F;
        arg -= 1.0F;
    }

    arg_100_int = (unsigned int)(100.0F*arg);
    dx = arg - 0.01F*(float)arg_100_int;
    dx_sq = dx*dx;

    sx  = tmpl_Float_Sin_Lookup_Table[arg_100_int];
    cx  = tmpl_Float_Cos_Lookup_Table[arg_100_int];

    sdx = 2.550164039877345443856178F * dx_sq - 5.167712780049970029246053F;
    sdx = sdx * dx_sq + 3.141592653589793238462643F;
    sdx = sdx * dx;

    cdx = 4.058712126416768218185014F * dx_sq - 4.934802200544679309417245F;
    cdx = cdx * dx_sq + 1.0F;

    return sgn_x * (cdx*sx + cx*sdx);
}

