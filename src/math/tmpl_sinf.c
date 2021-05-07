/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

#if __TMPL_USE_IEEE754_ALGORITHMS__ != 0

float tmpl_Float_Sin(float x)
{
    float arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx;
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

    arg = (float)fmod((double)abs_x, tmpl_Two_Pi);

    if (arg > tmpl_One_Pi_F)
    {
        sgn_x *= -1.0F;
        arg -= tmpl_One_Pi_F;
    }

    arg_100_int = (unsigned int)(100.0F*arg);
    dx = arg - 0.01F * (float)arg_100_int;

    sx  = tmpl_Float_Sin_Lookup_Table[arg_100_int];
    sdx = tmpl_Float_Sin_Taylor(dx);

    cx  = tmpl_Float_Cos_Lookup_Table[arg_100_int];
    cdx = tmpl_Float_Cos_Taylor(dx);

    if (arg < tmpl_Pi_By_Four_F)
        return sgn_x*(sx*cdx + cx*sdx);

    else if (arg < tmpl_Pi_By_Two_F)
        return sgn_x*(cx*cdx - sx*sdx);

    else if (arg < tmpl_Three_Pi_By_Four_F)
        return sgn_x*(cx*cdx - sx*sdx);

    else
        return sgn_x*(sx*cdx + cx*sdx);
}

#elif __TMPL_HAS_C99_MATH_H__ == 0

/*  Single precision sine function (sinf equivalent).                         */
float tmpl_Float_Sin(float x)
{
    return (float)sin((double)x);
}
/*  End of tmpl_Float_Sin.                                                    */

#else
float tmpl_Float_Sin(float x)
{
    return sinf(x);
}
#endif

