#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Tanh(float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float tanh_x;

    /*  The definition of than(x) is sinh(x)/cosh(x), so return this.         */
    tanh_x = tmpl_Float_Sinh(x) / tmpl_Float_Cosh(-x);
    return tanh_x;
}
