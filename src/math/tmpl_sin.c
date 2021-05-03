/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

#if __TMPL_USE_IEEE754_ALGORITHMS__ != 0

#include <libtmpl/include/tmpl_math_private.h>

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

    arg = fmod(abs_x, tmpl_Two_Pi);

    if (arg > tmpl_One_Pi)
    {
        sgn_x *= -1.0;
        arg -= tmpl_One_Pi;
    }

    arg_100_int = (unsigned int)(100.0*arg);
    dx = arg - 0.01*arg_100_int;

    sx  = tmpl_sin_lookup_table[arg_100_int];
    sdx = tmpl_do_sin(dx);

    cx  = tmpl_cos_lookup_table[arg_100_int];
    cdx = tmpl_do_cos(dx);

    if (arg < tmpl_Pi_By_Four)
        return sgn_x*(sx*cdx + cx*sdx);

    else if (arg < tmpl_Pi_By_Two)
        return sgn_x*(cx*cdx - sx*sdx);

    else if (arg < tmpl_Three_Pi_By_Four)
        return sgn_x*(cx*cdx - sx*sdx);

    else
        return sgn_x*(sx*cdx + cx*sdx);
}

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

    sx  = tmpl_sinl_lookup_table[arg_100_int];
    sdx = tmpl_do_sinl(dx);

    cx  = tmpl_cosl_lookup_table[arg_100_int];
    cdx = tmpl_do_cosl(dx);

    if (arg < tmpl_Pi_By_Four_L)
        return sgn_x*(sx*cdx + cx*sdx);

    else if (arg < tmpl_Pi_By_Two_L)
        return sgn_x*(cx*cdx - sx*sdx);

    else if (arg < tmpl_Three_Pi_By_Four_L)
        return sgn_x*(cx*cdx - sx*sdx);

    else
        return sgn_x*(sx*cdx + cx*sdx);
}

#else

/*  The "double" version of sin is defined in both C89 and C99 math.h so we   *
 *  only need to alias this function.                                         */

/*  Double precision sine function (sin equivalent).                          */
double tmpl_Double_Sin(double x)
{
    return sin(x);
}
/*  End of tmpl_Double_Sin.                                                   */


#if __TMPL_HAS_C99_MATH_H__ == 0

/*  Single precision sine function (sinf equivalent).                         */
float tmpl_Float_Sin(float x)
{
    return (float)sin((double)x);
}
/*  End of tmpl_Float_Sin.                                                    */

/*  Long double precision sine function (sinl equivalent).                    */
long double tmpl_LDouble_Sin(long double x)
{
    return (long double)sin((double)x);
}
/*  End of tmpl_LDouble_Sin.                                                  */

#else

/*  C99 provides float and long double support for their math functions, so   *
 *  simply use to these.                                                      */
float tmpl_Float_Sin(float x)
{
    return sinf(x);
}

long double tmpl_LDouble_Sin(long double x)
{
    return sinl(x);
}
#endif
/*  End of #if __TMPL_HAS_C99_MATH_H__ == 0                                   */

#endif
/*  End of #if __TMPL_USE_TRIG_ALGORITHMS__ != 0.                             */

