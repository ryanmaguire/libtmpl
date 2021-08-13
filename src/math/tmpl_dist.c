#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Dist(float x, float y)
{
    if (x < y)
        return y - x;
    else
        return x - y;
}

double tmpl_Double_Dist(double x, double y)
{
    if (x < y)
        return y - x;
    else
        return x - y;
}

long double tmpl_LDouble_Dist(long double x, long double y)
{
    if (x < y)
        return y - x;
    else
        return x - y;
}

