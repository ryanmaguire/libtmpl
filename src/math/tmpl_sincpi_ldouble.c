/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_SincPi(long double x)
{
    if (x == 0.0L)
        return 1.0L;

    return tmpl_LDouble_SinPi(x) / (tmpl_LDouble_Pi * x);
}
