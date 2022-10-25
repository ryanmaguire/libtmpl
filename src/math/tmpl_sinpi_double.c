#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/math/tmpl_math_cospi_lookup_table_double.h>
#include <libtmpl/include/math/tmpl_math_sinpi_lookup_table_double.h>

double tmpl_Double_SinPi(double x)
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

    arg = tmpl_Double_Mod_2(abs_x);

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
