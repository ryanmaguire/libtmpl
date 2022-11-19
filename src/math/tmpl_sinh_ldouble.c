#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_Sinh(long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double sinh_x;

    /*  The definition of sinh(x) is [exp(x) - exp(-x)]/2, so return this.    */
    sinh_x = 0.5L*(tmpl_LDouble_Exp(x)-tmpl_LDouble_Exp(-x));
    return sinh_x;
}
