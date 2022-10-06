#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_MATH_ALGORITHMS == 1

#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/math/tmpl_math_sincos_data_double.h>

#if TMPL_HAS_IEEE754_DOUBLE == 1

#include <libtmpl/include/math/tmpl_math_sincos_sin_precise_eval.h>
#include <libtmpl/include/math/tmpl_math_sincos_cos_precise_eval.h>
#include <libtmpl/include/math/tmpl_math_sincos_reduction.h>
#include <libtmpl/include/math/tmpl_math_sincos_reduction_very_large.h>

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
    double arg, sgn_x, cx, cdx, sx, sdx, dx, dx_sq;
    unsigned int arg_128_int;

    arg = tmpl_Double_Mod_2(tmpl_Double_Abs(x) * tmpl_One_By_Pi);

    if (arg >= 1.0)
    {
        sgn_x = -1.0;
        arg = arg - 1.0;
    }
    else
        sgn_x = 1.0;

    arg_128_int = (unsigned int)(128.0*arg);
    dx = arg - 0.0078125*arg_128_int;
    dx_sq = dx*dx;

    sx  = tmpl_Double_Sin_Lookup_Table[arg_128_int];
    cx  = tmpl_Double_Cos_Lookup_Table[arg_128_int];

    sdx = 0.08214588661112822879880237 * dx_sq - 0.5992645293207920768877394;
    sdx = sdx * dx_sq + 2.550164039877345443856178;
    sdx = sdx * dx_sq - 5.167712780049970029246053;
    sdx = sdx * dx_sq + 3.141592653589793238462643;
    sdx = sdx * dx;

    cdx = 0.2353306303588932045418794 * dx_sq - 1.335262768854589495875305;
    cdx = cdx * dx_sq + 4.058712126416768218185014;
    cdx = cdx * dx_sq - 4.934802200544679309417245;
    cdx = cdx * dx_sq + 1.0;

    return sgn_x * (cdx*cx - sx*sdx);
}

#endif

#endif
