#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *      Implement an actual SinhCosh routine.
 */

void tmpl_Double_SinhCosh(double t, double *sinh_t, double *cosh_t)
{
    *sinh_t = tmpl_Double_Sinh(t);
    *cosh_t = tmpl_Double_Cosh(t);
}
