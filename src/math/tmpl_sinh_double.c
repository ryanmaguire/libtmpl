#include <libtmpl/include/tmpl_math.h>

double tmpl_Double_Sinh(double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double sinh_x;

    /*  The definition of sinh(x) is [exp(x) - exp(-x)]/2, so return this.    */
    sinh_x = 0.5*(tmpl_Double_Exp(x) - tmpl_Double_Exp(-x));
    return sinh_x;
}

