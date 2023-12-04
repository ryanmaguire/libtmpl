#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *  Implement actual algorithm.
 */

float tmpl_Float_Tan(float x)
{
    float cos_x, sin_x;
    tmpl_Float_SinCos(x, &sin_x, &cos_x);
    return sin_x / cos_x;
}
