#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

void
tmpl_3DLDouble_AddTo(tmpl_ThreeVectorLongDouble *target,
                     tmpl_ThreeVectorLongDouble *source)
{
    target->dat[0] += source->dat[0];
    target->dat[1] += source->dat[1];
    target->dat[2] += source->dat[2];
}
