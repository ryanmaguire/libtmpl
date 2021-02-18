/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Erfc(float x)
{
    float erfc;
    erfc = tmpl_Float_Exp(x*x)*tmpl_Float_Erfcx(x);

    return erfc;
}

double tmpl_Double_Erfc(double x)
{
    double erfc;
    erfc = tmpl_Double_Exp(x*x)*tmpl_Double_Erfcx(x);

    return erfc;
}

long double tmpl_LDouble_Erfc(long double x)
{
    long double erfc;
    erfc = tmpl_LDouble_Exp(x*x)*tmpl_LDouble_Erfcx(x);

    return erfc;
}
