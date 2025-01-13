/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CREATE_LDOUBLEDOUBLE_H
#define TMPL_CREATE_LDOUBLEDOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_USE_INLINE.                 */
#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/two_sum/tmpl_two_sum_ldouble.h>
#else
extern void
tmpl_LDouble_Two_Sum(long double x,
                     long double y,
                     long double * TMPL_RESTRICT const out,
                     long double * TMPL_RESTRICT const err);
#endif

TMPL_INLINE_DECL
tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Create(long double x, long double y)
{
    tmpl_LongDoubleDouble out;
    tmpl_LDouble_Two_Sum(x, y, &out.dat[0], &out.dat[1]);
    return out;
}

#endif
