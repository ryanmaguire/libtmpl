/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CREATE_DOUBLEDOUBLE_H
#define TMPL_CREATE_DOUBLEDOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_USE_INLINE.                 */
#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/inline/two_sum/tmpl_two_sum_double.h>
#else
extern void
tmpl_Double_Two_Sum(double x,
                    double y,
                    double * TMPL_RESTRICT const out,
                    double * TMPL_RESTRICT const err);
#endif

TMPL_INLINE_DECL
tmpl_DoubleDouble
tmpl_DoubleDouble_Create(double x, double y)
{
    tmpl_DoubleDouble out;
    tmpl_Double_Two_Sum(x, y, &out.dat[0], &out.dat[1]);
    return out;
}

#endif
