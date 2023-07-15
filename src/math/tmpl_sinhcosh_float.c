#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *      Implement an actual SinhCosh routine.
 */

void tmpl_Float_SinhCosh(float t, float *sinh_t, float *cosh_t)
{
    *sinh_t = tmpl_Float_Sinh(t);
    *cosh_t = tmpl_Float_Cosh(t);
}
