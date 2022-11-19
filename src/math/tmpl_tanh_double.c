#include <libtmpl/include/tmpl_math.h>

double tmpl_Double_Tanh(double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double tanh_x;

    /*  The definition of than(x) is sinh(x)/cosh(x), so return this.         */
    tanh_x = tmpl_Double_Sinh(x) / tmpl_Double_Cosh(-x);
    return tanh_x;
}
