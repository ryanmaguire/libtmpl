#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_MATH_ALGORITHMS == 1

#include <libtmpl/include/tmpl_math.h>

#if TMPL_HAS_IEEE754_FLOAT == 1

float tmpl_Float_Sin(float x)
{
    const double in = (double)x;
    const double out = tmpl_Double_Sin(in);
    return (float)out;
}

#else

#include <libtmpl/include/math_inline/tmpl_math_sincos_data_float.h>

float tmpl_Float_Sin(float x)
{
    float arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx, dx_sq;
    unsigned int arg_128_int;

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

    arg = tmpl_Float_Mod_2(abs_x * tmpl_One_By_Pi_F);

    if (arg >= 1.0F)
    {
        sgn_x *= -1.0F;
        arg -= 1.0F;
    }

    arg_128_int = (unsigned int)(128.0F*arg);
    dx = arg - 0.0078125F*(float)arg_128_int;
    dx_sq = dx*dx;

    sx  = tmpl_Float_Sin_Lookup_Table[arg_128_int];
    cx  = tmpl_Float_Cos_Lookup_Table[arg_128_int];

    sdx = 2.550164039877345443856178F * dx_sq - 5.167712780049970029246053F;
    sdx = sdx * dx_sq + 3.141592653589793238462643F;
    sdx = sdx * dx;

    cdx = 4.058712126416768218185014F * dx_sq - 4.934802200544679309417245F;
    cdx = cdx * dx_sq + 1.0F;

    return sgn_x * (cdx*sx + cx*sdx);
}

#endif

#endif
