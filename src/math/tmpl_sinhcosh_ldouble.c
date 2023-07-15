#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *      Implement an actual SinhCosh routine.
 */

void
tmpl_LDouble_SinhCosh(long double t, long double *sinh_t, long double *cosh_t)
{
    *sinh_t = tmpl_LDouble_Sinh(t);
    *cosh_t = tmpl_LDouble_Cosh(t);
}
