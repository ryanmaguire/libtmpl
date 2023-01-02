#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_vec2.h>

float
tmpl_2DFloat_L2_Dist(const tmpl_TwoVectorFloat *P,
                     const tmpl_TwoVectorFloat *Q)
{
    return tmpl_Float_Hypot(P->dat[0] - Q->dat[0], P->dat[1] - Q->dat[1]);
}
