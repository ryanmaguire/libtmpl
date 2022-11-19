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

#include <libtmpl/include/math/tmpl_math_cospi_lookup_table_float.h>
#include <libtmpl/include/math/tmpl_math_sinpi_lookup_table_float.h>

float tmpl_Float_Sin(float x)
{
    float arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx;
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

    sx = tmpl_Float_SinPi_Lookup_Table[arg_128_int];
    cx = tmpl_Float_CosPi_Lookup_Table[arg_128_int];
    sdx = tmpl_Float_SinPi_Maclaurin(dx);
    cdx = tmpl_Float_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}

#endif

#endif
