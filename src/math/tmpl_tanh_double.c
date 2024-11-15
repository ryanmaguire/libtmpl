#include <libtmpl/include/tmpl_math.h>

double tmpl_Double_Tanh(double x)
{
    if (x > 36.0)
        return 1.0;
    else if (x < -36.0)
        return -1.0;

    /*  The definition of than(x) is sinh(x)/cosh(x), so return this.         */
    return tmpl_Double_Sinh(x) / tmpl_Double_Cosh(x);
}
