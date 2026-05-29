/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CREATE_LDOUBLEDOUBLE_H
#define TMPL_CREATE_LDOUBLEDOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_USE_INLINE.                 */
#include <libtmpl/include/tmpl_config.h>

/*  2Sum is needed to create a long-double-double.                            */
#include <libtmpl/include/two_sum/tmpl_two_sum_ldouble.h>

TMPL_INLINE_DECL
tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Create(long double x, long double y)
{
    tmpl_LongDoubleDouble out;
    tmpl_LDouble_Two_Sum(x, y, &out.dat[0], &out.dat[1]);
    return out;
}

#endif
