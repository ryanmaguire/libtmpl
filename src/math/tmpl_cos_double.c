#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_MATH_ALGORITHMS == 1

#include <libtmpl/include/tmpl_math.h>

#if TMPL_HAS_IEEE754_DOUBLE == 1

#include <libtmpl/include/math/tmpl_sincos_sin_precise_eval.h>
#include <libtmpl/include/math/tmpl_sincos_cos_precise_eval.h>
#include <libtmpl/include/math/tmpl_sincos_reduction.h>
#include <libtmpl/include/math/tmpl_sincos_reduction_very_large.h>
#include <libtmpl/include/math/tmpl_sincos_data_double.h>

#define TMPL_PI_BY_TWO_LOW_HALF (6.123233995736766035868820147292E-17)

double tmpl_Double_Cos(double x)
{
    double a, da, out;
    tmpl_IEEE754_Double w;
    unsigned int n;

    w.r = x;
    w.bits.sign = 0x00U;

    if (w.bits.expo < TMPL_DOUBLE_BIAS - 27U)
        return 1.0;

    else if (w.r < 8.5546875E-01)
        return tmpl_Double_Cos_Precise_Eval(x, 0.0);

    else if (w.r < 2.426265)
    {
        w.r = tmpl_Pi_By_Two - w.r;
        a = w.r + TMPL_PI_BY_TWO_LOW_HALF;
        da = (w.r - a) + TMPL_PI_BY_TWO_LOW_HALF;
        return tmpl_Double_Sin_Precise_Eval(a, da);
    }
    else if (w.bits.expo < TMPL_DOUBLE_NANINF_EXP)
    {
        if (w.r < 1.05414336E+08)
            n = tmpl_Double_SinCos_Reduction(x, &a, &da) + 1;
        else
            n = tmpl_Double_SinCos_Reduction_Very_Large(x, &a, &da) + 1;

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

double tmpl_Double_Cos(double x)
{
    double arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_Double_Mod_2(tmpl_Double_Abs(x) * tmpl_One_By_Pi);

    if (arg >= 1.0)
    {
        sgn_x = -1.0;
        arg = arg - 1.0;
    }
    else
        sgn_x = 1.0;

    ind = (unsigned int)(128.0*arg);
    dx = arg - 0.0078125*ind;

    sx = tmpl_double_sinpi_table[ind];
    cx = tmpl_double_cospi_table[ind];
    sdx = tmpl_Double_SinPi_Maclaurin(dx);
    cdx = tmpl_Double_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}

#endif

#endif
