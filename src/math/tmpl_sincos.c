/*  Header file where the prototypes for these functions are defined.         */
#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_math.h>

/*  Only compile if the user requested these algorithms.                      */
#if __TMPL_USE_IEEE754_ALGORITHMS__ != 0

float tmpl_Float_Sin_Taylor(float x)
{
    float x2, sin_x;
    x2 = x*x;

    sin_x = tmpl_Float_Sin_Taylor_Coeffs[1]*x2 +
            tmpl_Float_Sin_Taylor_Coeffs[0];
    sin_x = x*sin_x;
    return sin_x;
}

double tmpl_Double_Sin_Taylor(double x)
{
    double x2, sin_x;

    x2 = x*x;

    sin_x = tmpl_Double_Sin_Taylor_Coeffs[3]*x2 +
            tmpl_Double_Sin_Taylor_Coeffs[2];
    sin_x = x2*sin_x + tmpl_Double_Sin_Taylor_Coeffs[1];
    sin_x = x2*sin_x + tmpl_Double_Sin_Taylor_Coeffs[0];

    sin_x = x*sin_x;
    return sin_x;
}

long double tmpl_LDouble_Sin_Taylor(long double x)
{
    long double x2, sin_x;

    x2 = x*x;

    sin_x = tmpl_LDouble_Sin_Taylor_Coeffs[4]*x2 +
            tmpl_LDouble_Sin_Taylor_Coeffs[3];
    sin_x = x2*sin_x + tmpl_LDouble_Sin_Taylor_Coeffs[2];
    sin_x = x2*sin_x + tmpl_LDouble_Sin_Taylor_Coeffs[1];
    sin_x = x2*sin_x + tmpl_LDouble_Sin_Taylor_Coeffs[0];

    sin_x = x*sin_x;
    return sin_x;
}

float tmpl_Float_Cos_Taylor(float x)
{
    float x2, cos_x;
    x2 = x*x;

    cos_x = tmpl_Float_Cos_Taylor_Coeffs[1]*x2 +
            tmpl_Float_Cos_Taylor_Coeffs[0];
    return cos_x;
}

double tmpl_Double_Cos_Taylor(double x)
{
    double x2, cos_x;

    x2 = x*x;

    cos_x = tmpl_Double_Cos_Taylor_Coeffs[3]*x2 +
            tmpl_Double_Cos_Taylor_Coeffs[2];
    cos_x = x2*cos_x + tmpl_Double_Cos_Taylor_Coeffs[1];
    cos_x = x2*cos_x + tmpl_Double_Cos_Taylor_Coeffs[0];

    return cos_x;
}

long double tmpl_LDouble_Cos_Taylor(long double x)
{
    long double x2, cos_x;

    x2 = x*x;

    cos_x = tmpl_LDouble_Cos_Taylor_Coeffs[4]*x2 +
            tmpl_LDouble_Cos_Taylor_Coeffs[3];
    cos_x = x2*cos_x + tmpl_LDouble_Cos_Taylor_Coeffs[2];
    cos_x = x2*cos_x + tmpl_LDouble_Cos_Taylor_Coeffs[1];
    cos_x = x2*cos_x + tmpl_LDouble_Cos_Taylor_Coeffs[0];

    return cos_x;
}

#endif
/*  End of #if __TMPL_USE_TRIG_ALGORITHMS__ != 0.                             */

