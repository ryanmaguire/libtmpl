/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_SincPi(float x)
{
    if (x == 0.0F)
        return 1.0F;

    return tmpl_Float_SinPi(x) / (tmpl_Float_Pi * x);
}
