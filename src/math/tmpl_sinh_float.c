#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Sinh(float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float sinh_x;

    /*  The definition of sinh(x) is [exp(x) - exp(-x)]/2, so return this.    */
    sinh_x = 0.5F*(tmpl_Float_Exp(x) - tmpl_Float_Exp(-x));
    return sinh_x;
}
