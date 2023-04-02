#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *      Implement an actual SinCos routine.
 */

void tmpl_Float_SinCos(float t, float *sin_t, float *cos_t)
{
    *sin_t = tmpl_Float_Sin(t);
    *cos_t = tmpl_Float_Cos(t);
}
