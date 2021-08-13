/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>
#include <math.h>

/*  The "double" version of cos is defined in both C89 and C99 math.h so we   *
 *  only need to alias this function.                                         */
double tmpl_Double_Exp(double x)
{
    return exp(x);
}

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/*  C99 provides float and long double support for their math functions, so   *
 *  simply use to these.                                                      */
float tmpl_Float_Exp(float x)
{
    return expf(x);
}

long double tmpl_LDouble_Exp(long double x)
{
    return expl(x);
}

#else

/*  C89 math.h does not have cosf or cosfl, so we'll need to provide these to  *
 *  make the code forward compatible. We'll do this in a very simple manner.  */
float tmpl_Float_Exp(float x)
{
    return (float)exp((double)x);
}

long double tmpl_LDouble_Exp(long double x)
{
    return (long double)exp((double)x);
}

#endif
/*  End of #if __TMPL_HAS_C99_MATH_H__ == 0                                   */

