/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EXP_REMEZ_FLOAT_H
#define TMPL_EXP_REMEZ_FLOAT_H

/*  TMPL_STATIC_INLINE found here                                             */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez polynomial.                   */
#define A00 (+1.0000000106059821205497615923438225449617767337990E+00F)
#define A01 (+1.0000000088356670961167470006641503065999626762706E+00F)
#define A02 (+4.9999694504661831549639911146973242697185774891778E-01F)
#define A03 (+1.6666576713343118791091266331836085957467162462315E-01F)
#define A04 (+4.1796999994613185901060317501374654341068142737613E-02F)
#define A05 (+8.3578093664050040349255591933857725029991815492887E-03F)

/*  Helper macro for evaluating the polynomial via Horner's method.           */
#define TMPL_POLY_EVAL(z) A00 + x*(A01 + x*(A02 + x*(A03 + x*(A04 + x*A05))))

/*  Function for computing exp(x) for -1/4 < x < 1/4 using minimax polynomial.*/
TMPL_STATIC_INLINE
float tmpl_Float_Exp_Remez(float x)
{
    return TMPL_POLY_EVAL(x);
}
/*  End of tmpl_Float_Exp_Remez.                                              */

/*  Undefine everything in case someone wants to #include this file.          */
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
