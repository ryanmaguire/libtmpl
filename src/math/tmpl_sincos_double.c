#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *      Implement an actual SinCos routine.
 */

void tmpl_Double_SinCos(double t, double *sin_t, double *cos_t)
{
    *sin_t = tmpl_Double_Sin(t);
    *cos_t = tmpl_Double_Cos(t);
}
