
#include <libtmpl/include/tmpl_math.h>
#include <math.h>

double tmpl_Double_Floor(double x)
{
    return floor(x);
}

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
float tmpl_Float_Floor(float x)
{
    return floorf(x);
}

long double tmpl_LDouble_Floor(long double x)
{
    return floorl(x);
}
#else
float tmpl_Float_Floor(float x)
{
    return (float)floor((double)x);
}

long double tmpl_LDouble_Floor(long double x)
{
    return (long double)floor((double)x);
}
#endif

