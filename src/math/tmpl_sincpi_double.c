/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

double tmpl_Double_SincPi(double x)
{
    double y;

    if (x == 0.0)
        y = 1.0;
    else
        y = tmpl_Double_SinPi(x)/(tmpl_One_Pi*x);

    return y;
}
