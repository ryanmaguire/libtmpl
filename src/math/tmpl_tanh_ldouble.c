#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_Tanh(long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double tanh_x;

    /*  The definition of than(x) is sinh(x)/cosh(x), so return this.         */
    tanh_x = tmpl_LDouble_Sinh(x) / tmpl_LDouble_Cosh(-x);
    return tanh_x;
}
