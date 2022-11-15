/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_SincPi(float x)
{
    float y;

    if (x == 0.0F)
        y = 1.0F;
    else
        y = tmpl_Float_SinPi(x)/(tmpl_One_Pi_F*x);

    return y;
}
