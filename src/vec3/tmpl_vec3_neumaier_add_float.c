#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_two_sum.h>
#include <libtmpl/include/tmpl_vec3.h>

TMPL_ALWAYS_INLINE
void
tmpl_3DFloat_Neumaier_Two_Sum(const tmpl_ThreeVectorFloat * const summand,
                              tmpl_ThreeVectorFloat * TMPL_RESTRICT const sum,
                              tmpl_ThreeVectorFloat * TMPL_RESTRICT const err)
{
    tmpl_Float_Neumaier_Two_Sum(summand->dat[0], &sum->dat[0], &err->dat[0]);
    tmpl_Float_Neumaier_Two_Sum(summand->dat[1], &sum->dat[1], &err->dat[1]);
    tmpl_Float_Neumaier_Two_Sum(summand->dat[2], &sum->dat[2], &err->dat[2]);
}
