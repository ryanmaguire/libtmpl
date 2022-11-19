/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_Sinc(long double x)
{
    long double y;

    if (x == 0.0L)
        y = 1.0L;
    else
        y = tmpl_LDouble_Sin(x)/x;

    return y;
}
