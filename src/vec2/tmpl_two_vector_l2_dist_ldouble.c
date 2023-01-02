#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_vec2.h>

long double
tmpl_2DLDouble_L2_Dist(const tmpl_TwoVectorLongDouble *P,
                       const tmpl_TwoVectorLongDouble *Q)
{
    return tmpl_LDouble_Hypot(P->dat[0] - Q->dat[0], P->dat[1] - Q->dat[1]);
}
