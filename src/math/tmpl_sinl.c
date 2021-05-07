#include <libtmpl/include/tmpl_math.h>

#if __TMPL_USE_IEEE754_ALGORITHMS__ != 0

long double tmpl_LDouble_Sin(long double x)
{
    long double arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int arg_100_int;

    if (x >= 0.0L)
    {
        abs_x = x;
        sgn_x = 1.0L;
    }
    else
    {
        abs_x = -x;
        sgn_x = -1.0L;
    }

    if (abs_x > tmpl_Two_Pi_L)
        arg = (long double)fmod((double)abs_x, tmpl_Two_Pi);
    else
        arg = abs_x;

    if (arg > tmpl_One_Pi_L)
    {
        sgn_x *= -1.0L;
        arg -= tmpl_One_Pi_L;
    }

    arg_100_int = (unsigned int)(100.0L*arg);
    dx = arg - 0.01L*arg_100_int;

    sx  = tmpl_LDouble_Sin_Lookup_Table[arg_100_int];
    sdx = tmpl_LDouble_Sin_Taylor(dx);

    cx  = tmpl_LDouble_Cos_Lookup_Table[arg_100_int];
    cdx = tmpl_LDouble_Cos_Taylor(dx);

    if (arg < tmpl_Pi_By_Four_L)
        return sgn_x*(sx*cdx + cx*sdx);

    else if (arg < tmpl_Pi_By_Two_L)
        return sgn_x*(cx*cdx - sx*sdx);

    else if (arg < tmpl_Three_Pi_By_Four_L)
        return sgn_x*(cx*cdx - sx*sdx);

    else
        return sgn_x*(sx*cdx + cx*sdx);
}


#elif __TMPL_HAS_C99_MATH_H__ == 0

long double tmpl_LDouble_Sin(long double x)
{
    return (long double)sin((double)x);
}

#else

long double tmpl_LDouble_Sin(long double x)
{
    return sinl(x);
}

#endif

