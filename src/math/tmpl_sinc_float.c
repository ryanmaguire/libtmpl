/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Sinc(float x)
{
    float y;

    if (x == 0.0F)
        y = 1.0F;
    else
        y = tmpl_Float_Sin(x)/x;

    return y;
}
