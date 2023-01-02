#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_vec2.h>

double
tmpl_2DDouble_L2_Dist(const tmpl_TwoVectorDouble *P,
                      const tmpl_TwoVectorDouble *Q)
{
    return tmpl_Double_Hypot(P->dat[0] - Q->dat[0], P->dat[1] - Q->dat[1]);
}
