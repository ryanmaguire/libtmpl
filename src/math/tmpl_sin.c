/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

#if __TMPL_USE_IEEE754_ALGORITHMS__ != 0

double tmpl_Double_Sin(double x)
{
    double arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx;
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

    arg = tmpl_Double_Mod_2(abs_x);

    if (arg > tmpl_One_Pi)
    {
        sgn_x *= -1.0;
        arg -= tmpl_One_Pi;
    }

    arg_100_int = (unsigned int)(100.0*arg);
    dx = arg - 0.01*arg_100_int;

    sx  = tmpl_Double_Sin_Lookup_Table[arg_100_int];
    sdx = tmpl_Double_Sin_Taylor(dx);

    cx  = tmpl_Double_Cos_Lookup_Table[arg_100_int];
    cdx = tmpl_Double_Cos_Taylor(dx);

    if (arg < tmpl_Pi_By_Four)
        return sgn_x*(sx*cdx + cx*sdx);

    else if (arg < tmpl_Pi_By_Two)
        return sgn_x*(cx*cdx - sx*sdx);

    else if (arg < tmpl_Three_Pi_By_Four)
        return sgn_x*(cx*cdx - sx*sdx);

    else
        return sgn_x*(sx*cdx + cx*sdx);
}
#else
double tmpl_Double_Sin(double x)
{
    return sin(x);
}
#endif

