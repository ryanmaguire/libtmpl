/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_SincPi(long double x)
{
    long double y;

    if (x == 0.0L)
        y = 1.0L;
    else
        y = tmpl_LDouble_SinPi(x)/(tmpl_One_Pi_L*x);

    return y;
}
