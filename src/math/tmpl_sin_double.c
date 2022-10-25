#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_MATH_ALGORITHMS == 1

#include <libtmpl/include/tmpl_math.h>

#if TMPL_HAS_IEEE754_DOUBLE == 1

#include <libtmpl/include/math/tmpl_math_sincos_sin_precise_eval.h>
#include <libtmpl/include/math/tmpl_math_sincos_cos_precise_eval.h>
#include <libtmpl/include/math/tmpl_math_sincos_reduction.h>
#include <libtmpl/include/math/tmpl_math_sincos_reduction_very_large.h>

#define TMPL_PI_BY_TWO_LOW_HALF (6.123233995736766035868820147292E-17)

double tmpl_Double_Sin (double x)
{
    double a, da, out;
    tmpl_IEEE754_Double w;
    unsigned int n;

    w.r = x;
    w.bits.sign = 0x00U;

    if (w.bits.expo < TMPL_DOUBLE_BIAS - 26U)
        return x;

    else if (w.r < 8.5546875E-01)
        return tmpl_Double_Sin_Precise_Eval(x, 0.0);

    else if (w.r < 2.426265)
    {
        w.r = tmpl_Pi_By_Two - w.r;
        da = TMPL_PI_BY_TWO_LOW_HALF;
        return tmpl_Double_Copysign(tmpl_Double_Cos_Precise_Eval(w.r, da), x);
    }
    else if (w.bits.expo < TMPL_DOUBLE_NANINF_EXP)
    {
        if (w.r < 1.05414336E+08)
            n = tmpl_Double_SinCos_Reduction(x, &a, &da);
        else
            n = tmpl_Double_SinCos_Reduction_Very_Large(x, &a, &da);

        if (n & 1)
            out = tmpl_Double_Cos_Precise_Eval(a, da);
        else
            out = tmpl_Double_Sin_Precise_Eval(a, da);

        return (n & 2 ? -out : out);
    }
    else
        return TMPL_NAN;
}

#undef TMPL_PI_BY_TWO_LOW_HALF

#else

#include <libtmpl/include/math/tmpl_math_cospi_lookup_table_double.h>
#include <libtmpl/include/math/tmpl_math_sinpi_lookup_table_double.h>

double tmpl_Double_Sin(double x)
{
    double arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int arg_128_int;

    if (x >= 0.0)
    {
        abs_x = x;
        sgn_x = 1.0;
    }
    else
    {
        abs_x = -x;
        sgn_x = -1.0;
    }

    arg = tmpl_Double_Mod_2(abs_x * tmpl_One_By_Pi);

    if (arg >= 1.0)
    {
        sgn_x *= -1.0;
        arg -= 1.0;
    }

    arg_128_int = (unsigned int)(128.0*arg);
    dx = arg - 0.0078125*arg_128_int;

    sx = tmpl_Double_SinPi_Lookup_Table[arg_128_int];
    cx = tmpl_Double_CosPi_Lookup_Table[arg_128_int];
    sdx = tmpl_Double_SinPi_Maclaurin(dx);
    cdx = tmpl_Double_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}

#endif

#endif
