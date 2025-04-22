/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_BESSEL_I0_MEDIUM_DOUBLE_H
#define TMPL_BESSEL_I0_MEDIUM_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+4.0217650944500821213345877056034485040688754842144E-01)
#define A01 (+3.3605519836687503444921512798262155305664707154015E-03)
#define A02 (+1.3621607436057247811178430428537589905272378270075E-04)
#define A03 (+1.1143033723692216373903967975055762705738602173174E-05)
#define A04 (+1.4838487751516477417475870815223956182172415824192E-06)
#define A05 (+2.9736128490724146322042193915404024381175671719835E-07)
#define A06 (+8.8703921257689180342286231964971016175309393549443E-08)
#define A07 (+3.9312740107546420726617316695320898349947141752668E-08)
#define A08 (+2.1690761230569577182832485056484915912864388737705E-08)
#define A09 (+7.6158260255230473899240524942118708060272631867668E-09)
#define A10 (-7.3983215428612049939353971073921175651262229580667E-09)
#define A11 (-1.3557888142393474044003260114514514210844322190270E-08)
#define A12 (-3.5390902233358243141728848606692973307063392361701E-09)
#define A13 (+7.7090474315045658539209606623311410416056334952000E-09)
#define A14 (+3.9620201338993306424369263815514767766268586772780E-09)
#define A15 (-3.4406779108622786947785400688952357923812178033895E-09)
#define A16 (-1.7369154558572737356610960542731364328096810831639E-09)
#define A17 (+1.1681794695958406898307726799105396828552845141118E-09)
#define A18 (+3.2750103808578907805661516999266407104082408494744E-10)
#define A19 (-2.0933068756278751865718637495743618573853827701942E-10)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
  A01 + z*(\
    A02 + z*(\
      A03 + z*(\
        A04 + z*(\
          A05 + z*(\
            A06 + z*(\
              A07 + z*(\
                A08 + z*(\
                  A09 + z*(\
                    A10 + z*(\
                      A11 + z*(\
                        A12 + z*(\
                          A13 + z*(\
                            A14 + z*(\
                              A15 + z*(\
                                A16 + z*(\
                                  A17 + z*(\
                                    A18 + z*A19\
                                  )\
                                )\
                              )\
                            )\
                          )\
                        )\
                      )\
                    )\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

TMPL_STATIC_INLINE
double tmpl_Double_Bessel_I0_Medium(double x)
{
    const double rcpr_x = 1.0 / x;
    const double z = -1.0 + 16.0 * rcpr_x;
    const double exp_x = tmpl_Double_Exp_Pos_Kernel(x);
    const double sqrt_rcpr_x = tmpl_Double_Sqrt(rcpr_x);
    const double rat = TMPL_POLY_EVAL(z);
    return rat * exp_x * sqrt_rcpr_x;
}

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
#undef A11
#undef A12
#undef A13
#undef A14
#undef A15
#undef A16
#undef A17
#undef A18
#undef A19
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
