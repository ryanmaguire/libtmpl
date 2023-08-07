#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *      Implement an actual SinCos routine.
 */

void tmpl_LDouble_SinCos(long double t, long double *sin_t, long double *cos_t)
{
    *sin_t = tmpl_LDouble_Sin(t);
    *cos_t = tmpl_LDouble_Cos(t);
}
