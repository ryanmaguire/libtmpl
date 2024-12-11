#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Tanh(float x)
{
    if (x > 16.0F)
        return 1.0F;
    else if (x < -16.0F)
        return -1.0F;

    /*  The definition of than(x) is sinh(x)/cosh(x), so return this.         */
    return tmpl_Float_Sinh(x) / tmpl_Float_Cosh(x);
}
