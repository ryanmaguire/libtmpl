/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EXP_REMEZ_DOUBLE_H
#define TMPL_EXP_REMEZ_DOUBLE_H

/*  TMPL_STATIC_INLINE found here                                             */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez polynomial.                   */
#define A00 (+9.9999999999999999988430264938382617864875775206464E-01)
#define A01 (+1.0000000000000002567155499064945764299110332942888E+00)
#define A02 (+5.0000000000000011303128565037818364883412745825979E-01)
#define A03 (+1.6666666666658450641538834111096804338714833792536E-01)
#define A04 (+4.1666666666648208299845851261960139340509395965848E-02)
#define A05 (+8.3333333406957231917106078391264123789847252849529E-03)
#define A06 (+1.3888888900173203766146657738825963558824828302470E-03)
#define A07 (+1.9841242914202268899999786488562084101590255844480E-04)
#define A08 (+2.4801555544629532354737090416957032661760944182686E-05)
#define A09 (+2.7600400233476040774827464572558357184830459675937E-06)
#define A10 (+2.7599120100813904758992842016718714757809673113599E-07)

/*  Helper macro for evaluating the polynomial via Horner's method.           */
#define TMPL_POLY_EVAL(z) \
A00 + x*(\
    A01 + x*(\
        A02 + x*(\
            A03 + x*(\
                A04 + x*(\
                    A05 + x*(\
                        A06 + x*(\
                            A07 + x*(\
                                A08 + x*(\
                                    A09 + x*A10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Function for computing exp(x) for -1/4 < x < 1/4 using minimax polynomial.*/
TMPL_STATIC_INLINE
double tmpl_Double_Exp_Remez(double x)
{
    return TMPL_POLY_EVAL(x);
}
/*  End of tmpl_Double_Exp_Remez.                                             */

/*  Undefine everything in case someone wants to #include this file.          */
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
