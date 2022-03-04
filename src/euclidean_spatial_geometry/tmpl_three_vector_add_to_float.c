#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

void
tmpl_3DFloat_AddTo(tmpl_ThreeVectorFloat *target, tmpl_ThreeVectorFloat *source)
{
    target->dat[0] += source->dat[0];
    target->dat[1] += source->dat[1];
    target->dat[2] += source->dat[2];
}
