#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_Tanh(long double x)
{
    if (x > 78.0L)
        return 1.0L;
    else if (x < -78.0L)
        return -1.0L;

    /*  The definition of than(x) is sinh(x)/cosh(x), so return this.         */
    return tmpl_LDouble_Sinh(x) / tmpl_LDouble_Cosh(-x);
}
