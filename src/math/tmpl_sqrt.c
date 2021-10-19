/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>
#include <math.h>

/*  The "double" version of sin is defined in both C89 and C99 math.h so we   *
 *  only need to alias this function.                                         */
double tmpl_Double_Sqrt(double x)
{
    return sqrt(x);
}

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/*  C99 provides float and long double support for their math functions, so   *
 *  simply use to these.                                                      */
float tmpl_Float_Sqrt(float x)
{
    return sqrtf(x);
}

long double tmpl_LDouble_Sqrt(long double x)
{
    return sqrtl(x);
}

/*  Now have the functions declared in rss_ringoccs_math.h point to these.    */
#else

/*  C89 math.h does not have sinf or sinl, so we'll need to provide these to  *
 *  make the code forward compatible. We'll do this in a very simple manner.  */
float tmpl_Float_Sqrt(float x)
{
    return (float)sqrt((double)x);
}

long double tmpl_LDouble_Sqrt(long double x)
{
    return (long double)sqrt((double)x);
}

#endif
/*  End of #if __TMPL_HAS_C99_MATH_H__ == 0                                   */
