/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ADDTO_H
#define TMPL_COMPLEX_ADDTO_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

#include <libtmpl/include/tmpl_complex.h>

static inline void
tmpl_CFloat_AddTo(tmpl_ComplexDouble *z, const tmpl_ComplexDouble *w)
{
    /*  Complex addition is done component-wise.                              */
    z->dat[0] += w->dat[0];
    z->dat[1] += w->dat[1];
}

static inline void
tmpl_CDouble_AddTo(tmpl_ComplexDouble *z, const tmpl_ComplexDouble *w)
{
    /*  Complex addition is done component-wise.                              */
    z->dat[0] += w->dat[0];
    z->dat[1] += w->dat[1];
}

static inline void
tmpl_CLDouble_AddTo(tmpl_ComplexLongDouble *z, const tmpl_ComplexLongDouble *w)
{
    /*  Complex addition is done component-wise.                              */
    z->dat[0] += w->dat[0];
    z->dat[1] += w->dat[1];
}

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
