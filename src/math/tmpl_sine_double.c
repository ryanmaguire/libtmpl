#include <libtmpl/include/tmpl_math.h>

double tmpl_Double_Sin(double x)
{
    double arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx, dx_sq;
    unsigned int arg_100_int;

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

    arg = tmpl_Double_Mod_2(abs_x * 0.31830988618379067153776752674502872406);

    if (arg >= 1.0)
    {
        sgn_x *= -1.0;
        arg -= 1.0;
    }

    arg_100_int = (unsigned int)(100.0*arg);
    dx = arg - 0.01*arg_100_int;
    dx_sq = dx*dx;

    sx  = tmpl_Double_Sin_Lookup_Table[arg_100_int];
    cx  = tmpl_Double_Cos_Lookup_Table[arg_100_int];

    sdx = 0.08214588661112822879880237 * dx_sq - 0.5992645293207920768877394;
    sdx = sdx * dx_sq + 2.550164039877345443856178;
    sdx = sdx * dx_sq - 5.167712780049970029246053;
    sdx = sdx * dx_sq + 3.141592653589793238462643;
    sdx = sdx * dx;

    cdx = 0.2353306303588932045418794 * dx_sq - 1.335262768854589495875305;
    cdx = cdx * dx_sq + 4.058712126416768218185014;
    cdx = cdx * dx_sq - 4.934802200544679309417245;
    cdx = cdx * dx_sq + 1.0;

    return sgn_x * (cdx*sx + cx*sdx);
}

