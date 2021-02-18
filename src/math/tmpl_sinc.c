/*  The C Standard Library header for math functions and more found here.     */
#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Sinc(float x)
{
    float y;

    if (x == 0.0F)
        y = 1.0F;
    else
        y = tmpl_Float_Sin(x)/x;

    return y;
}

double tmpl_Double_Sinc(double x)
{
    double y;

    if (x == 0.0)
        y = 1.0;
    else
        y = tmpl_Double_Sin(x)/x;

    return y;
}

long double tmpl_LDouble_Sinc(long double x)
{
    long double y;

    if (x == 0.0L)
        y = 1.0L;
    else
        y = tmpl_LDouble_Sin(x)/x;

    return y;
}

